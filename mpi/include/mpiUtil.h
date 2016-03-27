#include "mpiUtil.h"
#include "HashMap.h"

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
 * Converts a hashmap into a contigious block of memory for
 * sending.
 */
void* serializeMap(HashMap* map);

/**
 * Takes in a linked list of map nodes and serliazes them to
 * a contigious block of characters.
 * @param data contigious block of memory to serliaze bucket to.
 * @param  bucket start pointer of linked list of map elements.
 * @return updated pointer of data incremented past data serialized.
 */
inline char* serializeBuckets(char* data, MapNode* bucket);

/**
 * Reads out one bucket of information from data pointer.
 * @param v pointer to value passed in to be updated by reading bucket.
 * @param strStart pointer to be updated to point to beginning of string
 * in data chunk.
 * @return updated data pointer position after reading bucket.
 */
inline char* unserializeBucket(Value* v, Key* k, char* data);

/**
 * unpacks a block of serialized data and adds it to input
 * hashmap
 * @param map map to add serialized key value pairs to
 * @param data serialized key value pairs to parse
 */
void addSerializedToMap(HashMap* map, char* data, uint32_t dataLen);

/**
 * Increments the value for specified key by 1. If no
 * key-value pair exists, one will be created with value 1.
 * @param map pointer to map to put pair
 * @param k Key of value to increment. 
 * @param v Value to increment by.
 * @param 1 if added. 0 if merged with existing.
 */
unsigned int addToBucket(HashMap* map, Key k, Value v, unsigned int hash);
