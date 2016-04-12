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
MapElement* map2Array(const HashMap* map);

/**
 * Sorts array of elements in descending order
 * by comparing value. Uses underlying qsort in stdlib.h
 * @param elements Array to sort
 */
void sortArray(MapElement* elements, uint32_t nElements);

/**
 * Compares two mapElements
 * @return Result of comparison
 */
int compareElements(const void* a, const void* b);

/**
 * Frees memory of an MapElement array
 * @param elements array to free
 */
void deleteMapArray(MapElement* elements, uint32_t nElements);

/**
 * djb2 hashing function invented/reported by Dan Bernstein.
 * Mysteriously good at generating hashes for character arrays
 * using the magic number 33.
 * @param k String key (casted as void*) to hash
 * @return Hash hash of key
 */
Hash stringHasher(const Key strK);

/**
 * Very bad hasing function. 
 * Sums result of each character of key
 * @param k String key (casted as void*) to hash
 * @return Hash hash of key
 */
Hash badStringHasher(const Key k);

/**
 * Wrapper function for standard c library string comparator. 
 * @param strKA String A to compare (casted as void*)
 * @param strKB string B to compare (casted as void*)
 * @return comparison result.
 */
int32_t stringComparator(const Key strKA, const Key strKB);

/**
 * Create a new copy of input string.
 * @param strK String to copy (casted as void*)
 * @param strLen length of string copied.
 * @return pointer to new copy (casted as void*)
 */
Key stringCopy(const Key strK, int* strLen);

/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k Key of value to increment. 
 * @param v Value to increment by.
 * @return 1 if value added, 0 if merged with an existing.
 */
unsigned int addToBucket(HashMap* map, Key k, Value v, unsigned int hash);

#endif /* MAP_UTIL__H */
