#include "HashMap.h"
#include "MapUtil.h"
#include "mpiUtil.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  HashMap* map = newMap(20, &stringHasher, &stringComparator, &stringCopy);
  char* str1 = "the";
  Key testKeyPtr = (Key)str1;
  incrementKeyValue(map, testKeyPtr);
  incrementKeyValue(map, testKeyPtr);
  incrementKeyValue(map, testKeyPtr);
  char* str2 = "blue";
  Key testKeyPtr2 = (Key)str2;
  incrementKeyValue(map, testKeyPtr2);
  incrementKeyValue(map, testKeyPtr2);
  incrementKeyValue(map, testKeyPtr2);
  printf("key = %d\n", get(map, testKeyPtr));
  printf("key2 = %d\n", get(map, testKeyPtr2));

  char* str3 = "a";
  Key testKeyPtr3 = (Key) str3;
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  printf("key3 = \%d\n", get(map, testKeyPtr3));

  HashMap* map2 = newMap(20, &stringHasher, &stringComparator, &stringCopy);
  char* str4 = "blue";
  Key testKeyPtr4 = (Key) str4;
  incrementKeyValue(map2, testKeyPtr4);
  incrementKeyValue(map2, testKeyPtr4);

  char* str5 = "at";
  Key testKeyPtr5 = (Key) str5;
  incrementKeyValue(map2, testKeyPtr5);
  incrementKeyValue(map2, testKeyPtr5);
  printf("key4 = %d\n", get(map2, testKeyPtr4));
  printf("key5 = %d\n", get(map2, testKeyPtr5));

  char* str6 = "my";
  Key testKeyPtr6 = (Key) str6;
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  printf("key6 = %d\n", get(map2, testKeyPtr6));

  printf("number of bytes in map1:%d\n", map->nBytes);
  char* data;
  uint32_t nBytes;
  data = serializeMap(map, &nBytes);
  printf("number of bytes in map2:%d\n", map2->nBytes);
  int i = 0;
  printf("printing raw bytes\n");
  for(i = 0;  i < nBytes + 4; i++) {
    printf("%c ", data[i]);
  }
  printf("\n");
  addSerializedToMap(map2, data);
  printf("number of bytes in reduced map2:%d\n", map2->nBytes);
  printf("key = %d\n", get(map2, testKeyPtr));
  printf("key2 = %d\n", get(map2, testKeyPtr2));
  printf("key3 = %d\n", get(map2, testKeyPtr3));
  printf("key4 = %d\n", get(map2, testKeyPtr4));
  printf("key5 = %d\n", get(map2, testKeyPtr5));
  printf("key6 = %d\n", get(map2, testKeyPtr6));
  deleteMap(map);
  deleteMap(map2);
}
