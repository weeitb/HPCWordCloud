/**
 * Main file for the sequential build of the word counter
 * prints out the top 10 most used words.
 */
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
// openmp header
#include <omp.h>
#include "HashMap.h"
#include "MapUtil.h"
#include "FileParser.h"
#include "OpenMPUtil.h"
#include "stack.h"

int main(int argc, char** argv) {
  double start, stop;
  double stop_read;
  double stop_reduce;
  start = omp_get_wtime();
  if (argc < 4) {
    printf("Insufficient arguments provided to function. Please specify:\n <directory of files to parse> ((good) | (bad)) <number of hashmap bins>\n");
    return 0;
  }
  
  // Get input files from directory provided from stdin
  DIR* dp;
  dp = opendir(argv[1]);
  struct dirent* ep;
  char* filepath;
  /* Build stack for splitting up files across threads in OpenMP */
  FilenameStack* stack = newStack();
  if (dp != NULL) {
    while (ep = readdir(dp)) {
      filepath = (char*) malloc(1 + strlen(ep->d_name) + strlen(argv[1]));
      strcpy(filepath, argv[1]);
      strcat(filepath, ep->d_name);
      push(stack, filepath);
    }
  } else {
    return 0;
  }
  closedir(dp);
  HashMap** maps;
  /* Start OpenMP parallel region */
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int nThreads = omp_get_num_threads();
    // We have to do this here because we don't know the number of threads
    // before we enter a parallel region.
    if (tid == 0) {
      maps = (HashMap**) malloc(sizeof(HashMap*) * nThreads);
    }
    // Wait for thread 1 to finish allocating space for all maps.
    #pragma omp barrier
    // Each thread creates it's own map.
    if (strcmp(argv[2], "bad") == 0) {
      maps[tid] = newMap(atoi(argv[3]), &badStringHasher, &stringComparator, &stringCopy);
    } else {
      maps[tid] = newMap(atoi(argv[3]), &stringHasher, &stringComparator, &stringCopy);
    }
    // only one thread can access the stack at a time to prevent multiple stacks
    // from accidentally reading the same file.
    char* filename;
    filename = OpenMPPop(stack);
    while(filename != NULL) {
      // most of the time spent should be here, so collisions should in theory
      // not cause a large performance impact.
      readFile(filename, 0, maps[tid]);
      free(filename);
      filename = OpenMPPop(stack);
    }
    // wait until all threads get here to map reduce
    #pragma omp barrier
    if (tid == 0) {
      stop_read = omp_get_wtime();
    }
    OpenMPMapReduce(maps, tid, nThreads);
    #pragma omp barrier
    if (tid == 0) {
      stop_reduce = omp_get_wtime();
    }
    // free all maps that were allocated for other threads.
    // result is in map[0]
    if (tid != 0) {
      deleteMap(maps[tid]);
    } else {
      // TODO: We could possibly parallelize this transformation and sort.
      MapElement* elements = map2Array(maps[0]);
      sortArray(elements, maps[0]->nElements);
      printf("Top 10 words:\n");
      int i;
      for(i = 0; i < 10; i++) {
	printf("%d\t%s\t%d\n", i, (char*)elements[i].k, elements[i].v);
      }
  
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
