#include "OpenMPUtil.h"

int main(int argc, char** argv) {
  FilenameStack* stack = newStack();
  char name1[] = "hello";
  char name2[] = "my name is";
  char name3[] = "bob";
  char* nullChar = pop(stack);
  if (nullChar == null) {
    printf("it's null!\n");
  }
  push(stack, name1);
  push(stack, name2);
  push(stack, name3);
  printf("%s\n", pop(stack));
  printf("%s\n", pop(stack));
  printf("%s\n", pop(stack));

  nullChar = pop(stack);
  if (nullChar == null) {
    printf("it's null!\n");
  }
  deleteStack(stack);
  return 0;
}
