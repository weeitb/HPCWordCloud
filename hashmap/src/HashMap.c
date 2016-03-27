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
#include <stdlib.h>
#include <stdio.h>

#include "HashMap.h"

/**
 * Creates a new hashmap.
 * @param nBuckets Number of buckets to initialize map with.
 * @param hasher hash function to use for keys.
 * @param comparator comparator function to use for keys.
 * @param KeyCopy key copying function so map contains it's own copy.
 * @param Pointer to hashmap.
 */
HashMap* newMap(uint32_t nBuckets, Hasher hasher, Comparator comparator, KeyCopy keyCopy) {
  HashMap* map = (HashMap*) malloc(sizeof(HashMap));
  map->hasher = hasher;
  map->comparator = comparator;
  map->keyCopy = keyCopy;
  map->buckets = (MapNode**) malloc(nBuckets * sizeof(MapNode*));
  uint32_t i;
  for (i = 0; i < nBuckets; ++i) {
    map->buckets[i] = NULL;
  }
  map->nBuckets = nBuckets;
  map->nElements = 0;
  map->nBytes = 0;
  return map;
}

/**
 * Returns the value for the specified key. Returns 0 if no key-value pair exists.
 * @param map map to lookup value in
 * @param Key to lookup value.
 */
Value get(HashMap* map, Key k) {
  Hash hash = (*map->hasher)(k) % map->nBuckets;
  MapNode* node = map->buckets[hash];
  while(node != NULL) {
    if (map->comparator(k, node->k) == 0) {
      return node->v;
    }
    node = node->nextNode;
  }
  return 0;
}


/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k Key of value to increment. 
 */
void incrementKeyValue(HashMap* map, Key k) {
  Hash hash = (*map->hasher)(k) % map->nBuckets;
  //  if (hash > 2000) {
  //printf("we got one at %d\n", hash);
  //}
  MapNode* node = map->buckets[hash];
  // check if our bucket is empty. If it is We need to point
  // it to it's first element when it's created later.
  char bucketIsEmpty = node == NULL;
  MapNode* prevNode = node;
  while(node != NULL) {
    if (map->comparator(k, node->k) == 0) {
      node->v += 1;
      return;
    }
    prevNode = node;
    node = node->nextNode;
  }
  
  node = (MapNode*) malloc(sizeof(MapNode));

  // Add it as the first element in bucket
  if (bucketIsEmpty) { 
    map->buckets[hash] = node;
  }
  map->nElements++;
  node->nextNode = NULL;
  node->v = 1;
  // Copy the key so we have our own local copy.
  int keyLen;
  node->k = (*map->keyCopy)(k, &keyLen);
  // Keep track of total memory used for map. This allows
  // for serialization later.
  map->nBytes += sizeof(Value) + sizeof(char) * (keyLen + 1);
  if (prevNode != NULL) {
    prevNode->nextNode = node;
  }
}

/**
 * Deletes the map and frees memory allocated for it's contents.
 * @param map map to delete
 */
void deleteMap(HashMap* map) {
  MapNode* node;
  MapNode* nextNode;
  uint32_t i;
  for (i = 0; i < map->nBuckets; ++i) {
    node = map->buckets[i];
    while (node != NULL) {
      nextNode = node->nextNode;
      free(node->k);
      free(node);
      node = nextNode;
    }
  }
  free(map->buckets);
  free(map);
}

