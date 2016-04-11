#include "stack.h"

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
