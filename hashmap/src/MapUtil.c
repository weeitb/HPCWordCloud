/**
 * Utility functions to use for HashMap.
 * String functions, as well as conversion of
 * map to array.
 * @author Wyatt Bertorelli <wyattbertorelli@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"
#include "MapUtil.h"

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
      elements[j].v = node->v;
      elements[j].k = (*map->keyCopy)(node->k);
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
void sortArray(MapElement* elements, uint32_t nElements) {
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
  return elemB->v - elemA->v;
}

/**
 * Frees memory of an MapElement array
 * @param elements array to free
 */
void deleteMapArray(MapElement* elements, uint32_t nElements) {
  int i;
  for (i = 0; i < nElements; i++) {
    free(elements[i].k);
  }
  free(elements);
}


/**
 * djb2 hashing function invented/reported by Dan Bernstein.
 * Mysteriously good at generating hashes for character arrays
 * using the magic number 33.
 * @param k String key (casted as void*) to hash
 * @return Hash hash of key
 */
Hash stringHasher(const Key k) {
  Hash hash = 5381;
  int c;
  char* str = k;
  while (c = *str++) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

/**
 * Very bad hasing function. 
 * Sums result of each character of key
 * @param k String key (casted as void*) to hash
 * @return Hash hash of key
 */
Hash badStringHasher(const Key k) {
  Hash hash = 0;
  int c;
  char* str = k;
  while (c = *str++) {
    hash += c;
  }
  return hash;
}

/**
 * Wrapper function for standard c library string comparator. 
 * @param strKA String A to compare (casted as void*)
 * @param strKB string B to compare (casted as void*)
 * @return comparison result.
 */
int32_t stringComparator(const Key kA, const Key kB) {
  return strcmp((char*) kA, (char*) kB);
}

/**
 * Create a new copy of input string.
 * @param strK String to copy (casted as void*)
 * @return pointer to new copy (casted as void*)
 */
Key stringCopy(const Key strK) {
  char* newCopy = malloc(sizeof(char) * strlen((char*) strK));
  strcpy(newCopy, (char*) strK);
  return (Key) newCopy;
}
