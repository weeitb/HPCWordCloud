#ifndef OPEN_MP_UTIL__H
#define OPEN_MP_UTIL__H

#include "HashMap.h"
/**
 * Utility data structures and functions for openmp
 * implementation.
 * @author Wyatt Bertorelli <wyattbertorelli@gmail.com>
 */


/**
 * Element for for filename stack data structure.
 */
typedef struct FilenameElements {
  char* filename;
  struct FilenameElements* nextNode;
} FilenameElement;

/**
 * Stack data structure for holding list of files to parse.
 * Designed so that each thread or process can pop a file off
 * the stack to process. Mutation of this data structure must 
 * be surrounded with a critical section, so that multiple
 * threads do not end up working on the same files.
 */
typedef struct FilenameStacks {
  FilenameElement* front;
  unsigned int nElements;
} FilenameStack;


/**
 * Create a new empty stack
 * @return pointer to new allocated stack.
 */
FilenameStack* newStack();

/**
 * Delete the input stack and all it's elements
 * @param stack stack to free from memory.
 */
void deleteStack(FilenameStack* stack);

/**
 * push a new filename string onto the stack.
 * Ownership of the filename memory is given
 * to the stack, and should only be free'd after
 * the element has been pushed off the stack.
 * @param stack stack to push onto.
 * @param filename filename to push onto stack.
 */
void push(FilenameStack* stack, char* filename);

/**
 * Pop the first filename string off of the stack.
 * Ownership of the allocated memory for the filename
 * is given to the process that pops the element off 
 * the stack.
 * @param stack to pop off of.
 * @return filename string. Null if stack empty.
 */
char* pop(FilenameStack* stack);

/**
 * Aggregates the results of each hashmap into the map at index 0.
 * Each thread performs work on the same block in each map calculated
 * by it's thread id, and the maps' bucket size.
 * @param array of hash maps to aggregate
 * @param threadId the thread number of the calling thread
 * @param nThreads the number of threads executing reduction
 */
void mapReduce(HashMap** map, unsigned int threadId, unsigned int nThreads);

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


/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k Key of value to increment. 
 * @param v Value to increment by.
 * @return 1 if value added, 0 if merged with an existing.
 */
unsigned int addToBucket(HashMap* map, Key k, Value v, unsigned int hash);


#endif /* OPEN_MP_UTIL__H */
