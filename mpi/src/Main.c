/**
 * Main file for the sequential build of the word counter
 * prints out the top 10 most used words.
 */
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
// mpi header
#include <mpi.h>
#include "HashMap.h"
#include "MapUtil.h"
#include "FileParser.h"
#include "mpiUtil.h"
#define READ_DIR_PATH "../resources/bibleChapters/"

int main(int argc, char** argv) {
  double start, stop;
  double stop_read;
  double stop_reduce;
  int numprocs, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  DIR* dp;
  dp = opendir(READ_DIR_PATH);
  struct dirent* ep;
  char* filepath;
  /* Build stack for splitting up files across threads in OpenMP */
  FilenameStack* stack = newStack();
  int i = 0;
  if (dp != NULL) {
    while (ep = readdir(dp)) {
      // equally divide files among processes.
      if (i % numprocs - rank == 0) {
	filepath = (char*) malloc(1 + strlen(ep->d_name) + strlen(argv[1]));
	strcpy(filepath, argv[1]);
	strcat(filepath, ep->d_name);
	push(stack, filepath);
      }
      i++;
    }
  } else {
    return 0;
  }
  closedir(dp);
  HashMap* map = newMap(2000, &stringHasher, &stringComparator, &stringCopy);

  char* filename;
  filename = pop(stack);
  while(filename != NULL) {
      // most of the time spent should be here, so collisions should in theory
      // not cause a large performance impact.
      readFile(filename, 0, maps[tid]);
      free(filename);
      filename = pop(stack);
    }
  // TODO: Implement mapReduce in mpi.
  //mapReduce(maps, tid, nThreads);

      // TODO: We could possibly parallelize this transformation and sort.
      MapElement* elements = map2Array(maps[0]);
      sortArray(elements, maps[0]->nElements);
      //printf("Top 10 words:\n");
      //int i;
      //for(i = 0; i < 10; i++) {
      //printf("%d\t%s\t%d\n", i, (char*)elements[i].k, elements[i].v);
      //}
  
      deleteMapArray(elements, maps[0]->nElements);
      //printf("There are %d unique words.\n", maps[0]->nElements);
      deleteMap(maps[0]);
      stop = omp_get_wtime();
      free(maps);
      double time_spent = (double)(stop - start);
      printf("%.5e,", stop_read - start);
      printf("%.5e,", stop_reduce - stop_read);
      printf("%.5e\n", time_spent);
    }
  }
  /** End OpenMP Parallel region **/
  return 0;
}
