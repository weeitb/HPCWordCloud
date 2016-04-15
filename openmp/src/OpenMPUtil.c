#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "OpenMPUtil.h"
#include "HashMap.h"
#include "MapUtil.h"
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
