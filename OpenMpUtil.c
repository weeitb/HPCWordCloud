#include "OpenMPUtil.h"
#include "HashMap.h"

/**
 * Create a new empty stack
 * @return pointer to new allocated stack.
 */
FilenameStack* newStack() {
  FilenameStack* stack = (FilenameStack*) malloc(sizeof(FilenameStack));
  stack->nextNode = NULL;
  stack-> nElements = 0;
}

/**
 * Delete the input stack and all it's elements
 * @param stack stack to free from memory.
 */
void deleteStack(FilenameStack* stack) {
  while (stack->front != NULL) {
    filenameElement* current = stack->front;
    free(current->filename);
    stack->front = current->nextNode;
    free(current);
  }
  free(stack);
}

/**
 * push a new filename string onto the stack.
 * Ownership of the filename memory is given
 * to the stack, and should only be free'd after
 * the element has been pushed off the stack.
 * @param stack stack to push onto.
 * @param filename filename to push onto stack.
 */
void push(FilenameStack* stack, char* filename) {
  FilenameElement* newElement = (FilenameElement*)malloc(sizeof(FilenameElement));
  newElement->filename = filename;
  newElement->nextNode = stack->front;
  stack->front = newElement;
}

/**
 * Pop the first filename string off of the stack.
 * Ownership of the allocated memory for the filename
 * is given to the process that pops the element off 
 * the stack.
 * @param stack to pop off of.
 * @return filename string. Null if stack empty.
 */
char* filename pop(FilenameStack* stack) {
  if (stack->front != NULL) {
    FilenameElement* element = stack->front;
    stack->front = element->nextNode;
    stack->nElements--;
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
void mapReduce(HashMap** map, unsigned int threadId, unsigned int nThreads) {
  int nBuckets = map[0]->nBuckets;
  unsigned int startIdx = threadId * nBuckets / nThreads;
  unsigned int endIdx;
  if (threadId == nThreads - 1) {
    endIdx = nBuckets;
  } else {
    endIdx = (threadId + 1) * nBuckets / nThreads;
  }
  unsigned int bucketIdx;
  unsigned int mapIdx;
  for(bucketIdx = startIdx; bucketIdx < endIdx; bucketIdx++) {
    for(mapIdx = 0; mapIdx < nThreads; mapIdx++) {
      
    }
  }
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
void mergeBuckets(HashMap* dest, HashMap* src, unsigned int bucketIdx) {
  MapNode* currentBucket = src->buckets[bucketIdx];

  while(currentBucket != NULL) {
    addToBucket(dest, currentBucket->k, currentBucket->v, bucketIdx);
    currentBucket = currentBucket->nextNode;
  }
}


/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k Key of value to increment. 
 * @param v Value to increment by.
 */
void addToBucket(HashMap* map, Key k, Value v = 1, unsigned int hash) {
  MapNode* node = map->buckets[hash];
  // check if our bucket is empty. If it is We need to point
  // it to it's first element when it's created later.
  char bucketIsEmpty = node == NULL;
  MapNode* prevNode = node;
  while(node != NULL) {
    if (map->comparator(k, node->k) == 0) {
      node->v += v;
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
  node->v = v;
  // Copy the key so we have our own local copy.
  node->k = (*map->keyCopy)(k);
  if (prevNode != NULL) {
    prevNode->nextNode = node;
  }
}
