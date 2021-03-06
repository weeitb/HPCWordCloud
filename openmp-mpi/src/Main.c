/**
 * Main file for the sequential build of the word counter
 * prints out the top 10 most used words.
 */
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
// mpi header
#include <mpi.h>
// openmp header
#include <omp.h>
#include "HashMap.h"
#include "MapUtil.h"
#include "FileParser.h"
#include "mpiUtil.h"
#include "OpenMPUtil.h"

// our input arguments are being redirected to
// mpi. Define directory to read.
#define READ_DIR_PATH "../resources/bibleChapters/"

int main(int argc, char** argv) {
  double start, stop;
  double stop_read;
  double stop_reduce1;
  double stop_reduce2;
  int numprocs, rank;
  MPI_Init(&argc, &argv);
  start = MPI_Wtime();
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  //printf("got to start\n");
  DIR* dp;
  dp = opendir(READ_DIR_PATH);
  struct dirent* ep;
  char* filepath;
  /* Build stack for splitting up files across threads in mpi */
  FilenameStack* stack = newStack();
  int i = 0;
  if (dp != NULL) {
    while (ep = readdir(dp)) {
      // equally divide files among processes.
      if ((i % numprocs) - rank == 0) {
	filepath = (char*) malloc(1 + strlen(ep->d_name) + strlen(READ_DIR_PATH));
	strcpy(filepath, READ_DIR_PATH);
	strcat(filepath, ep->d_name);
	push(stack, filepath);
      }
      i++;
    }
  } else {
    printf("Couldn't open input directory\n");
    return 0;
  }
  closedir(dp);
  HashMap** maps;
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int nThreads = omp_get_num_threads();
    if (tid == 0) {
      maps = (HashMap**) malloc(sizeof(HashMap*) * nThreads);
    }
    #pragma omp barrier
    maps[tid] = newMap(2000, &stringHasher, &stringComparator, &stringCopy);
    char* filename;
    // distribute work across threads in openmp dynamically
    filename = OpenMPPop(stack);
    while(filename != NULL) {
      // most of the time spent should be here, so collisions should in theory
      // not cause a large performance impact.
      readFile(filename, 0, maps[tid]);
      free(filename);
      // crticial section in pop to prevent race conditions
      filename = OpenMPPop(stack);
    }
   #pragma omp barrier
    if (tid == 0) {
      //printf("got past reading\n");
      stop_read = MPI_Wtime();
    }
    // openmp map reduce. aggregate map is stored in maps[0]
    OpenMPMapReduce(maps, tid, nThreads);
    #pragma omp barrier
    if (tid == 0) {
      stop_reduce1 = MPI_Wtime();
    } else {
      // these maps are all unused now. delete them.
      deleteMap(maps[tid]);
    }
  } // end openmp parallel region.
  //  int elementCount = 0;
  //for (i = 0; i < 2000; i++) {
  //MapNode* bucket = maps[0]->buckets[i];
  //while(bucket != NULL) {
  //elementCount++;
  //bucket = bucket->nextNode;
  //}
  //}
  //printf("elements tallied: %d, elements book-kept: %d\n", elementCount, maps[0]->nElements);

  //printf("reached end of openmp reduction\n");
  // mpi map reduce. Combine all agregate maps.
  // resulting map is stored in maps[0] at rank 0.
  mpiMapReduce(maps[0], rank, numprocs);
  stop_reduce2 = MPI_Wtime();
  ///printf("finished mpi reduction\n");
  // We could possibly parallelize this transformation and sort.
  if (rank == 0) {
    MapElement* elements = map2Array(maps[0]);
    sortArray(elements, maps[0]->nElements);
    //printf("Top 10 words:\n");
    //for(i = 0; i < 10; i++) {
    //printf("%d\t%s\t%d\n", i, (char*)elements[i].k, elements[i].v);
    //}
  
    deleteMapArray(elements, maps[0]->nElements);
    //printf("There are %d unique words.\n", maps[0]->nElements);
    deleteMap(maps[0]);
    free(maps);
    stop = MPI_Wtime();
    printf("%.5e\n", stop_read - start);
    printf("%.5e\n", stop_reduce1 - stop_read);
    printf("%.5e\n", stop_reduce2 - stop_reduce1);
    printf("%.5e\n", stop - start);
  } else {
    deleteMap(maps[0]);
    free(maps);
  }
  
  MPI_Finalize();
  /** End mpi Parallel region **/
  return 0;
}
