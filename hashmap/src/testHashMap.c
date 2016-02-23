#include "HashMap.h"
#include "stdio.h"
#include "stdlib.h"

#define wrapVal 20

/**
 * Simple test code that uses both uint32 as the key and hash.
 * collisions checked by wrapping the key value by a specified amount.
 */


Hash testHashFunction(const Key k) {
  return *(Hash*) k % wrapVal;
}


int32_t testComparator(const Key kA, const Key kB) {
  return *(Hash*)kA - *(Hash*)kB;
}

Key testKeyCopy(const Key k) {
  Hash* newK = (Hash*) malloc(sizeof(Hash));
  *newK = *(Hash*)k;
  return (Key*)newK;
}

int main(int argc, char** argv) {
  HashMap* map = newMap(40, &testHashFunction, &testComparator, &testKeyCopy);
  Hash key = 0;
  Key testKeyPtr = (Key) &key;
  incrementKeyValue(map, testKeyPtr);
  incrementKeyValue(map, testKeyPtr);
  incrementKeyValue(map, testKeyPtr);
  Hash key2 = 20;
  Key testKeyPtr2 = (Key) &key2;
  incrementKeyValue(map, testKeyPtr2);
  incrementKeyValue(map, testKeyPtr2);
  printf("key = %d\n", get(map, testKeyPtr));
  printf("key2 = %d\n", get(map, testKeyPtr2));
  Hash key3 = 18;
  Key testKeyPtr3 = (Key) &key3;
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  printf("key3 = \%d\n", get(map, testKeyPtr3));
  deleteMap(map);
}
