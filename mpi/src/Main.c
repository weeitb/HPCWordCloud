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

// our input arguments are being redirected to
// mpi. Define directory to read.
#define READ_DIR_PATH "../resources/bibleChapters/"

int main(int argc, char** argv) {
  double start, stop;
  double stop_read;
  double stop_reduce;
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
  /* Build stack for splitting up files across threads in OpenMP */
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
  //printf("got past dividing work\n");
  HashMap* map = newMap(2000, &stringHasher, &stringComparator, &stringCopy);

  char* filename;
  filename = pop(stack);
  while(filename != NULL) {
    // most of the time spent should be here, so collisions should in theory
    // not cause a large performance impact.
    readFile(filename, 0, map);
    free(filename);
    filename = pop(stack);
  }
  //printf("got past reading\n");
  stop_read = MPI_Wtime();
  mapReduce(map, rank, numprocs);
  stop_reduce = MPI_Wtime();

  // We could possibly parallelize this transformation and sort.
  if (rank == 0) {
    MapElement* elements = map2Array(map);
    sortArray(elements, map->nElements);
    printf("Top 10 words:\n");
    for(i = 0; i < 10; i++) {
      printf("%d\t%s\t%d\n", i, (char*)elements[i].k, elements[i].v);
    }
  
    deleteMapArray(elements, map->nElements);
    //printf("There are %d unique words.\n", maps[0]->nElements);
    deleteMap(map);
    stop = MPI_Wtime();
    printf("%.5e,", stop_read - start);
    printf("%.5e,", stop_reduce - stop_read);
    printf("%.5e\n", stop - start);
  } else {
    deleteMap(map);
  }
  
  MPI_Finalize();
  /** End mpi Parallel region **/
  return 0;
}
