#ifndef HASH_MAP__H
#define HASH_MAP__H
/**
 * Incremental HashMap data structure. void* data type allows usage of any
 * data type for map. Map is limited to using ints as the value. The map
 * is optimized towards incrementing values of key value pairs for word
 * clouds.
 * As long as the comparator, hasher, and key copy operate on the same data type
 * (casted to void*), any key should work.
 * Because the data type is optimized for performance, there is no error checking.
 * DO NOT MODIFY INTERNAL CONTENTS DIRECTLY. Use helper functions!
 * @Author Wyatt Bertorelli <wyattbertorelli@gmail.com>
 */

#include <stdint.h>

typedef uint32_t Hash;
typedef void* Key;
typedef uint32_t Value;

/**
 * Maps an arbitrary key into a numeric value. If the function returns a result
 * that is greater than the bucket array width, the result is modulo'd with the
 * length of the array.
 */
typedef Hash (*Hasher)(const Key k);

/**
 * Compares two key's to determine equality for insertion and lookup in map.
 * Equality follows Java's Object.Compare, and is defined as follows:
 * [1, 2^31 - 1] : kA > kB
 * [-2^31, -1]   : kA < kB
 * 0             : kA == kB
 */
typedef int32_t (*Comparator)(const Key kA, const Key kB);

/**
 * Key copy function so we can own a copy to store in map.
 */
typedef Key (*KeyCopy)(const Key k);

/**
 * Node datastructure. Contains a pointer to the next element
 * for keys with the same hash.
 */
typedef struct MapNodes {
  Key k;
  Value v;
  struct MapNodes* nextNode;
} MapNode;

/**
 * HashMap data structure. 
 * DO NOT MODIFY INTERNAL CONTENTS DIRECTLY.
 */
typedef struct HashMaps {
  MapNode** buckets;
  uint32_t nBuckets;
  uint32_t nElements;
  Hasher hasher;
  Comparator comparator;
  KeyCopy keyCopy;
} HashMap;

/**
 * Creates a new hashmap.
 * @param nBuckets Number of buckets to initialize map with.
 * @param hasher hash function to use for keys.
 * @param comparator comparator function to use for keys.
 * @param KeyCopy key copying function so map contains it's own copy.
 * @param Pointer to hashmap.
 */
HashMap* newMap(uint32_t nBuckets, Hasher hasher, Comparator comparator, KeyCopy keyCopy);

/**
 * Returns the value for the specified key. Returns 0 if no key-value pair exists.
 * @param map map to lookup value in
 * @param Key to lookup value.
 */
Value get(HashMap* map, Key k);

/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k key of value to increment. 
 * @param v Value to increment by. Defaults to 1.
 */
void incrementKeyValue(HashMap* map, Key k, Value v = 1);

/**
 * Deletes the map and frees memory allocated for it's contents.
 * @param map map to delete
 */
void deleteMap(HashMap* map);
#endif /* HASH_MAP__H */
