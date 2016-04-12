#ifndef MPI_UTIL__H
#define MPI_UTIL__H

#include "mpiUtil.h"
#include "HashMap.h"

union SerializedData {
  uint32_t* intPtr;
  char* strPtr;
};

/**
 * Converts a hashmap into a contigious block of memory for
 * sending.
 * @param map map to serialize
 * @param nBytes serialized block size.
 * @return pointer to serialized block of data
 */
unsigned char* serializeMap(HashMap* map, uint32_t* nBytes);

/**
 * Takes in a linked list of map nodes and serliazes them to
 * a contigious block of characters.
 * @param data contigious block of memory to serliaze bucket to.
 * @param  bucket start pointer of linked list of map elements.
 * @return updated pointer of data incremented past data serialized.
 */
inline unsigned char* serializeBuckets(unsigned char* data, MapNode* bucket);

/**
 * Reads out one bucket of information from data pointer.
 * @param v pointer to value passed in to be updated by reading bucket.
 * @param strStart pointer to be updated to point to beginning of string
 * in data chunk.
 * @return updated data pointer position after reading bucket.
 */
inline unsigned char* unserializeBucket(Value* v, Key* k, unsigned char* data);

/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k Key of value to increment. 
 * @param v Value to increment by.
 * @param 1 if added. 0 if merged with existing.
 */
unsigned int addToBucket(HashMap* map, Key k, Value v, unsigned int hash);

/**
 * Performs map reduce using mpi message passing.
 * Assumes numprocs is a power of 2. The result will
 * be stored in the map on process with rank 0.
 * @param map local map to reduce
 * @param rank mpi process rank
 * @param numprocs number of mpi processes.
 */
void mpiMapReduce(HashMap* map, int rank, int numprocs);

#endif /* MPI_UTIL__H */
