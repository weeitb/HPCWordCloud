#include "HashMap.h"
#include "stdio.h"
#include "stdlib.h"

/**
 * Simple test code that uses both uint32 as the key and hash.
 * collisions checked by wrapping the key value by a specified amount.
 */


Hash testHashFunction(const Key k) {
  return *(Hash*) k;
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
  HashMap* map = newMap(20, &testHashFunction, &testComparator, &testKeyCopy);
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
  Hash key3 = 10;
  Key testKeyPtr3 = (Key) &key3;
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  printf("key3 = \%d\n", get(map, testKeyPtr3));

  HashMap* map2 = newMap(40, &testHashFunction, &testComparator, &testKeyCopy);
  Hash key4 = 0;
  Key testKeyPtr4 = (Key) &key4;
  incrementKeyValue(map2, testKeyPtr4);
  incrementKeyValue(map2, testKeyPtr4);
  incrementKeyValue(map2, testKeyPtr4);
  Hash key5 = 30;
  Key testKeyPtr5 = (Key) &key5;
  incrementKeyValue(map2, testKeyPtr5);
  incrementKeyValue(map2, testKeyPtr5);
  printf("key = %d\n", get(map2, testKeyPtr4));
  printf("key2 = %d\n", get(map2, testKeyPtr5));
  Hash key6 = 40;
  Key testKeyPtr6 = (Key) &key6;
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  printf("key3 = \%d\n", get(map2, testKeyPtr6));

  HashMap** maps = (HashMap**) malloc(sizeof(HashMap*) * 2);
  maps[0] = map;
  maps[1] = map;
  mapReduce(maps, 0, 1);
  printf("key + key4 = \%d\n", get(map, testKeyPtr));
  printf("key6 = \%d\n", get(map, testKeyPtr6));
  printf("key6 = \%d\n", get(map, testKeyPtr5));
  printf("key6 = \%d\n", get(map, testKeyPtr3));
  deleteMap(map2);
  deleteMap(map);
  free(maps);
}
