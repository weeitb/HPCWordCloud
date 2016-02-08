#ifndef STRING_KEY__H
#define STRING_KEY__H
/**
 * Utility functions to use Strings as keys for HashMap.
 * @author Wyatt Bertorelli <wyattbertorelli@gmail.com>
 */
#include <stdio.h>

#include "HashMap.h"

/**
 * djb2 hashing function invented/reported by Dan Bernstein.
 * Mysteriously good at generating hashes for character arrays
 * using the magic number 33.
 * @param k String key (casted as void*) to hash
 * @return Hash hash of key
 */
Hash StringHasher(Key strK);

/**
 * Wrapper function for standard c library string comparator. 
 * @param strKA String A to compare (casted as void*)
 * @param strKB string B to compare (casted as void*)
 * @return comparison result.
 */
int32_t StringComparator(Key strKA, Key strKB);

/**
 * Create a new copy of input string.
 * @param strK String to copy (casted as void*)
 * @return pointer to new copy (casted as void*)
 */
Key StringCopy(Key strK);
#endif /* STRING_KEY__H */
