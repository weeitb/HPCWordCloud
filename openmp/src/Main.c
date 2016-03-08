/**
 * Main file for the sequential build of the word counter
 * prints out the top 10 most used words.
 */
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
// openmp header
#include <openmp.h>
#include "HashMap.h"
#include "MapUtil.h"
#include "FileParser.h"
#include "OpenMPUtil.h"

int main(int argc, char** argv) {
  double start, stop;
  start = openmp_get_wtime();

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
    printf("Couldn't open directory %s\n", argv[1]);
    return 0;
  }
  closedir(dp);

  HashMap** maps;
  /** Start OpenMP parallel region **/
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    // We have to do this here because we don't know the number of threads
    // before we enter a parallel region.
    if (tid == 0) {
      int nThreads = openmp_get_num_threads();
      maps = (HashMap**) malloc(sizeof(HashMap*));
    }
    // Wait for thread 1 to finish allocating space for all maps.
    #pragma omp barrier
    // Each thread creates it's own map.
    if (strcmp(argv[2], "bad")) {
      map[tid] = newMap(atoi(argv[3]), &badStringHasher, &stringComparator, &stringCopy);
    } else {
      map[tid] = newMap(atoi(argv[3]), &stringHasher, &stringComparator, &stringCopy);
    }
    // only one thread can access the stack at a time to prevent multiple stacks
    // from accidentally reading the same file.
    #pragma omp critical
    char* filename = pop(stack);
    while(filename != NULL) {
      // most of the time spent should be here, so collisions should in theory
      // not cause a large performance impact.
      readFile(filename, 0, map[tid]);
      free(filename);
      // only one thread can access stack at a time.
      #pragma omp critical
      filename = pop(stack);
    }
    // wait until all threads get here to map reduce
    #pragma omp barrier
    
  }
  /** End OpenMP Parallel region **/
  
  /* MapElement* elements = map2Array(map); */
  /* sortArray(elements, map->nElements); */
  
  /* deleteMapArray(elements, map->nElements); */
  /* printf("nElements is %d\n", map->nElements); */
  /* deleteMap(map); */
  stop = openmp_get_wtime();
  double time_spent = (double)(stop - start);
  printf("Time spent executing is %.5e\n", time_spent);
  return 0;
}
