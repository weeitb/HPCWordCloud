#include "stdlib.h"
#include "HashMap.h"

/**
 * Copies each element in the map to an array
 * @param map input map.
 */
MapElement* map2Array(const HashMap* map) {
  int i;
  MapElement* elements = (MapElement*) malloc(map->nElements * sizeof(MapElement));
  MapNode* node;
  int j = 0;
  for (i = 0; i < map->nBuckets; i++) {
    node = map->buckets[i];
    while(node != NULL) {
      elements[j]->v = node->v;
      elements[j]->k = (*map->keyCopy)(node->k);
      j++;
      node = node->nextNode;
    }
  }
  return elements;
}

/**
 * Sorts array of elements in descending order
 * by comparing value. Uses underlying qsort in stdlib.h
 * @param elements Array to sort
 */
void sortArray(mapElements* elements, uint32_t nElements) {
  qsort((void*) elements, nElements, sizeof(MapElement), &compareElements);
}

/**
 * Compares two mapElements by value.
 * Returns inverse of normal so resulting array is in ascending order.
 * @return Result of comparison
 */
int compareElements(const void* a, const void* b) {
  const MapElement* elemA = (const MapElement*) a;
  const MapElement* elemB = (const MapElement*) b;
  return elembB->v - elemA->v;
}

/**
 * Frees memory of an MapElement array
 * @param elements array to free
 */
void deleteMapArray(MapElements* elements uint32_t nElements) {
  int i;
  for (i = 0; i < nElements i++) {
    free(elements[i]->k);
  }
  free(elements);
}
