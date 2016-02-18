#ifndef MAP_UTIL__H
#define MAP_UTIL__H
#include "HashMap.h"

typedef struct MapElements {
  Key k;
  Value v;
} MapElement;

/**
 * Copies each element in the map to an array
 * @param map input map.
 */
mapElements* map2Array(HashMap* map);

/**
 * Sorts array of elements in descending order
 * by comparing value. Uses underlying qsort in stdlib.h
 * @param elements Array to sort
 */
void sortArray(mapElements* elements);

/**
 * Compares two mapElements
 * @return Result of comparison
 */
int compareElements(const void* a, const void* b);

/**
 * Frees memory of an MapElement array
 * @param elements array to free
 */
void deleteMapArray(MapElements* elements uint32_t nElements);

#endif /* MAP_UTIL__H */
