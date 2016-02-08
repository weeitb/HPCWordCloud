/**
 * Utility functions to use Strings as keys for HashMap.
 * @author Wyatt Bertorelli <wyattbertorelli@gmail.com>
 */
#include <stdio.h>

#include "StringKey.h"
#include "HashMap.h"

/**
 * djb2 hashing function invented/reported by Dan Bernstein.
 * Mysteriously good at generating hashes for character arrays
 * using the magic number 33.
 * @param k String key (casted as void*) to hash
 * @return Hash hash of key
 */
Hash StringHasher(Key k) {
  Hash hash = 5381;
  int c;
  char* str = k;
  while (c = *str++) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

/**
 * Wrapper function for standard c library string comparator. 
 * @param strKA String A to compare (casted as void*)
 * @param strKB string B to compare (casted as void*)
 * @return comparison result.
 */
int32_t StringComparator(Key kA, Key kB) {
  return strcmp((char*) kA, (char*) kB);
}

/**
 * Create a new copy of input string.
 * @param strK String to copy (casted as void*)
 * @return pointer to new copy (casted as void*)
 */
Key StringCopy(Key strK) {
  char* newCopy = malloc(sizeof(char) * strlen((char*) k));
  strcpy(newCopy, (char*) k);
  return (Key) newCopy;
}
