/**
 * Main file for the sequential build of the word counter
 * prints out the top 10 most used words.
 */
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
#include "HashMap.h"
#include "MapUtil.h"
#include "FileParser.h"


int main(int argc, char** argv) {
  clock_t start, stop;
  start = clock();
  HashMap* map;
  if (argc < 4) {
    printf("Insufficient arguments provided to function. Please specify:\n <directory of files to parse> ((good) | (bad)) <number of hashmap bins>\n");
    return 0;
  }
  if (strcmp(argv[2], "bad")) {
    map = newMap(atoi(argv[3]), &badStringHasher, &stringComparator, &stringCopy);
  } else {
    map = newMap(atoi(argv[3]), &stringHasher, &stringComparator, &stringCopy);
  }
  // Get input file from stdin
  DIR* dp;
  dp = opendir(argv[1]);
  struct dirent* ep;
  char* filepath;
  
  if (dp != NULL) {
    while (ep = readdir(dp)) {
      filepath = (char*) malloc(1 + strlen(ep->d_name) + strlen(argv[1]));
      strcpy(filepath, argv[1]);
      strcat(filepath, ep->d_name);
      readFile(filepath, 0, map);
      free(filepath);
    }
  } else {
    printf("Couldn't open directory %s\n", argv[1]);
    return 0;
  }

  closedir(dp);
  MapElement* elements = map2Array(map);
  sortArray(elements, map->nElements);
  
  int i;
  for (i = 0; i < 10; i++) {
    printf("%s\t%d\n", (char*) elements[i].k, elements[i].v);
  }
  deleteMapArray(elements, map->nElements);
  //  printf("nElements is %d\n", map->nElements);
  deleteMap(map);
  stop = clock();
  double time_spent = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("%.5e\n", time_spent);
  return 0;
}
