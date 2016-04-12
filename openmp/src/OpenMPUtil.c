#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "OpenMPUtil.h"
#include "HashMap.h"
#include "stack.h"

/**
 * Pop the first filename string off of the stack.
 * Ownership of the allocated memory for the filename
 * is given to the process that pops the element off 
 * the stack.
 * @param stack to pop off of.
 * @return filename string. Null if stack empty.
 */
char* OpenMPPop(FilenameStack* stack) {
  if (stack->front != NULL) {
    FilenameElement* element;
    #pragma omp critical
    {
      element = stack->front;
      stack->front = element->nextNode;
      stack->nElements--;
    }
    char* filename = element->filename;
    free(element);
    return filename;
  } else {
    return NULL;
  }
}

/**
 * Aggregates the results of each hashmap into the map at index 0.
 * Each thread performs work on the same block in each map calculated
 * by it's thread id, and the maps' bucket size.
 * @param array of hash maps to aggregate
 * @param threadId the thread number of the calling thread
 * @param nThreads the number of threads executing reduction
 */
void OpenMPMapReduce(HashMap** map, unsigned int threadId, unsigned int nThreads) {
  int nBuckets = map[0]->nBuckets;
  unsigned int startIdx = (threadId * nBuckets) / nThreads;
  unsigned int endIdx;
  if (threadId == nThreads - 1) {
    endIdx = nBuckets;
  } else {
    endIdx = ((threadId + 1) * nBuckets) / nThreads;
  }
  unsigned int bucketIdx;
  unsigned int mapIdx;
  unsigned int valuesAdded = 0;
  for(bucketIdx = startIdx; bucketIdx < endIdx; bucketIdx++) {
    for(mapIdx = 1; mapIdx < nThreads; mapIdx++) {
      valuesAdded += mergeBuckets(map[0], map[mapIdx], bucketIdx);
    }
  }
  //printf("adding %d values to map[0] for thread %d\n", valuesAdded, threadId);
  #pragma omp atomic
  map[0]->nElements += valuesAdded;
}

/**
 * Adds the two hashmaps together at the given bucket index.
 * 'Add' means that entries with matching keys have their
 * values added together, and unique keys from src are
 * added to the destination map.
 * The result is stored in the dest hashmap.
 * @param dest first operand and result map to add
 * @param src second operand map to add
 * @param bucketIdx bucket index to add to maps at
 */
unsigned int mergeBuckets(HashMap* dest, HashMap* src, unsigned int bucketIdx) {
  MapNode* currentBucket = src->buckets[bucketIdx];
  unsigned int valuesAdded = 0;
  while(currentBucket != NULL) {
    valuesAdded += addToBucket(dest, currentBucket->k, currentBucket->v, bucketIdx);
    currentBucket = currentBucket->nextNode;
  }
  return valuesAdded;
}


/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k Key of value to increment. 
 * @param v Value to increment by.
 * @param 1 if added. 0 if merged with existing.
 */
unsigned int addToBucket(HashMap* map, Key k, Value v, unsigned int hash) {
  MapNode* node = map->buckets[hash];
  // check if our bucket is empty. If it is We need to point
  // it to it's first element when it's created later.
  char bucketIsEmpty = node == NULL;
  MapNode* prevNode = node;
  while(node != NULL) {
    if (map->comparator(k, node->k) == 0) {
      node->v += v;
      return 0;
    }
    prevNode = node;
    node = node->nextNode;
  }
  
  node = (MapNode*) malloc(sizeof(MapNode));

  // Add it as the first element in bucket
  if (bucketIsEmpty) { 
    map->buckets[hash] = node;
  }
  node->nextNode = NULL;
  node->v = v;
  // Copy the key so we have our own local copy.
  int strLen;
  node->k = (*map->keyCopy)(k, &strLen);
  if (prevNode != NULL) {
    prevNode->nextNode = node;
  }
  return 1;
}
