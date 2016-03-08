#ifndef OPEN_MP_UTIL__H
#define OPEN_MP_UTIL__H
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
  struct FileNameElements* nextNode;
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
char* filename pop(FileNameStack* stack);

#endif /* OPEN_MP_UTIL__H */
