/**
 * Main file for the sequential build of the word counter
 * prints out the first 10 elements
 */
#include <time.h>
#include "HashMap.h"
#include "MapUtil.h"
#include "FileParser.h"


int main(int argc, char** argv) {
  clock_t start, stop;
  start = clock();
  HashMap* map = newMap(1000, &stringHasher, &stringComparator, &stringCopy);
  // Get input file from stdin
  readFile(argv[1], 0, map);
  MapElement* elements = map2Array(map);
  sortArray(elements, map->nElements);
  
  int i;
  for (i = 0; i < 10; i++) {
    printf("%s\t%d\n", (char*) elements[i].k, elements[i].v);
  }
  deleteMapArray(elements, map->nElements);
  deleteMap(map);
  stop = clock();
  double time_spent = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("Time spent executing is %.5e\n", time_spent);
  return 0;
}
