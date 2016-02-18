#ifndef MAP_UTIL__H
#define MAP_UTIL__H
/**
 * Utility functions to use Strings as keys for HashMap.
 * @author Wyatt Bertorelli <wyattbertorelli@gmail.com>
 */
#include <stdio.h>
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

/**
 * djb2 hashing function invented/reported by Dan Bernstein.
 * Mysteriously good at generating hashes for character arrays
 * using the magic number 33.
 * @param k String key (casted as void*) to hash
 * @return Hash hash of key
 */
Hash StringHasher(Key strK);

/**
 * Wrapper function for standard c library string comparator. 
 * @param strKA String A to compare (casted as void*)
 * @param strKB string B to compare (casted as void*)
 * @return comparison result.
 */
int32_t StringComparator(Key strKA, Key strKB);

/**
 * Create a new copy of input string.
 * @param strK String to copy (casted as void*)
 * @return pointer to new copy (casted as void*)
 */
Key StringCopy(Key strK);

#endif /* MAP_UTIL__H */
