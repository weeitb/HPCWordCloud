#ifndef OPEN_MP_UTIL__H
#define OPEN_MP_UTIL__H

#include "HashMap.h"
#include "stack.h"

/**
 * Utility data structures and functions for openmp
 * implementation.
 * @author Wyatt Bertorelli <wyattbertorelli@gmail.com>
 */

/**
 * Pop the first filename string off of the stack.
 * Ownership of the allocated memory for the filename
 * is given to the process that pops the element off 
 * the stack. Uses openmp pragmas to prevent corruption
 * of internal data structure
 * @param stack to pop off of.
 * @return filename string. Null if stack empty.
 */
char* OpenMPPop(FilenameStack* stack);

/**
 * Aggregates the results of each hashmap into the map at index 0.
 * Each thread performs work on the same block in each map calculated
 * by it's thread id, and the maps' bucket size.
 * @param array of hash maps to aggregate
 * @param threadId the thread number of the calling thread
 * @param nThreads the number of threads executing reduction
 */
void OpenMPMapReduce(HashMap** map, unsigned int threadId, unsigned int nThreads);

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
unsigned int mergeBuckets(HashMap* dest, HashMap* src, unsigned int bucketIdx);

#endif /* OPEN_MP_UTIL__H */
