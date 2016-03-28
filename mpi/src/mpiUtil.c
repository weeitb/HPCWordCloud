#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#include "mpiUtil.h"
#include "HashMap.h"

/**
 * Create a new empty stack
 * @return pointer to new allocated stack.
 */
FilenameStack* newStack() {
  FilenameStack* stack = (FilenameStack*) malloc(sizeof(FilenameStack));
  stack->front = NULL;
  stack-> nElements = 0;
}

/**
 * Delete the input stack and all it's elements
 * @param stack stack to free from memory.
 */
void deleteStack(FilenameStack* stack) {
  while (stack->front != NULL) {
    FilenameElement* current = stack->front;
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
char* pop(FilenameStack* stack) {
  if (stack->front != NULL) {
    FilenameElement* element;
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
 * Converts a hashmap into a contigious block of memory for
 * sending.
 */
unsigned char* serializeMap(HashMap* map, uint32_t* nBytes) {
  // add 4 bytes to store the number of elements at front.
  *nBytes = map->nBytes + 4;
  //printf("allocating %d bytes for serialization\n", *nBytes);
  unsigned char* data = (unsigned char*)malloc((*nBytes) * sizeof(char));
  unsigned char* startData = data;
  int bucketIdx = 0;
  int j = 0;
  //printf("writing integer %d to first block\n", map->nElements);
  *data++ = map->nElements & 0xff;
  //  printf("first byte %d\n", *(data - 1));
  *data++ = (map->nElements >>  8) & 0xff;
  *data++ = (map->nElements >> 16) & 0xff;
  *data++ = (map->nElements >> 24) & 0xff;
  MapNode* currentBucket;
  for (bucketIdx = 0; bucketIdx < map->nBuckets; bucketIdx++) {
    currentBucket = map->buckets[bucketIdx];
    data = serializeBuckets(data, currentBucket);
  }
  if (data - startData + 1 > *nBytes) {
    printf("We aren't bookeeping properly %d, %d\n", data - startData + 1, nBytes);
  }
  return startData;
}

/**
 * Takes in a linked list of map nodes and serliazes them to
 * a contigious block of characters.
 * @param data contigious block of memory to serliaze bucket to.
 * @param  bucket start pointer of linked list of map elements.
 * @return updated pointer of data incremented past data serialized.
 */
inline unsigned char* serializeBuckets(unsigned char* data, MapNode* bucket) {
  unsigned char* key;
  while (bucket != NULL) {
    // convert a uint32_t to 4 characters
    *data++ = bucket->v & 0xff;
    *data++ = (bucket->v >>  8) & 0xff;
    *data++ = (bucket->v >> 16) & 0xff;
    *data++ = (bucket->v >> 24) & 0xff;
    key = (unsigned char*) bucket->k;
    // copy the string including the null terminator.
    // we will use the null terminator to split data
    // on the receiving end.
    while((*data++ = *key++) != 0);//printf("%c ", *(data - 1));
    bucket = bucket->nextNode;
  }
  return data;
}

/**
 * Reads out one bucket of information from data pointer.
 * @param v pointer to value passed in to be updated by reading bucket.
 * @param strStart pointer to be updated to point to beginning of string
 * in data chunk.
 * @return updated data pointer position after reading bucket.
 */
inline unsigned char* unserializeBucket(Value* v, Key* k, unsigned char* data) {
  // unpack serialized int.
  *v = *data++;
  *v |= *data++ << 8;
  *v |= *data++ << 16;
  *v |= *data++ << 24;
  // set pointer of string to read to start of string.
  *k = data;
  // increment data to start of next chunk.
  while(*data++);// printf("%c ", *(data - 1));
  return data;
}

/**
 * unpacks a block of serialized data and adds it to input
 * hashmap
 * @param map map to add serialized key value pairs to
 * @param data serialized key value pairs to parse
 */
void addSerializedToMap(HashMap* map, unsigned char* data, int nBytes) {
  uint32_t nElements;
  //unsigned char* startPtr = data;
  nElements = *data++;
  nElements |= *data++ << 8;
  nElements |= *data++ << 16;
  nElements |= *data++ << 24;
  //printf("nElements is %d", nElements);
  //printf("number of elements %d\n", nElements);
  uint32_t elementIdx = 0;
  Key k;
  Value v;
  unsigned int hash;
  for (elementIdx = 0; elementIdx < nElements; elementIdx++) {
     data = unserializeBucket(&v, &k, data);
     hash = (*map->hasher)(k) % map->nBuckets;
     //A little inefficient, we could copy location information in message.
     map->nElements += addToBucket(map, k, v, hash);
  }
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
  int strLen;
  map->nBytes += sizeof(Value) + sizeof(char) * (strLen + 1);
  // Copy the key so we have our own local copy.
  node->k = (*map->keyCopy)(k, &strLen);
  if (prevNode != NULL) {
    prevNode->nextNode = node;
  }
  return 1;
}


/**
 * Performs map reduce using mpi message passing.
 * Assumes numprocs is a power of 2. The result will
 * be stored in the map on process with rank 0.
 * @param map local map to reduce
 * @param rank mpi process rank
 * @param numprocs number of mpi processes.
 */
void mapReduce(HashMap* map, int rank, int numprocs) {
  int s;
  int count;
  MPI_Status status;
  char* buffer;
  for (s = numprocs / 2; s > 0; s = s/2) {
    if (rank < s) {
      // Get the number of elements being sent to us.
      //printf("getting next reduce for rank %d\n", rank);
      MPI_Probe(rank + s, 0, MPI_COMM_WORLD, &status);
      MPI_Get_count(&status, MPI_CHAR, &count);
      // receive from higher process. merge data.
      buffer = (char*)malloc(sizeof(char) * count);
      //printf("received %d bytes at %d from %d\n", count, rank, rank + s);
      MPI_Recv(buffer, count, MPI_CHAR, rank  + s, 0,
	       MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      // do stuff with data
      addSerializedToMap(map, (unsigned char*) buffer, count);
      //printf("finished reduce at %d\n", rank);
      free(buffer);
    } else if (rank < 2 * s) {
      // serialize hashmap for sending.
      uint32_t nBytes;
      buffer = (char*)serializeMap(map, &nBytes);
      MPI_Send(buffer, nBytes, MPI_CHAR, rank - s, 0, MPI_COMM_WORLD);
      free(buffer);
    }
  }
}
