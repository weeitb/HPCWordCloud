#include "HashMap.h"
#include "MapUtil.h"
#include "stdio.h"
#include "stdlib.h"

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
  printf("key = %d\n", get(map, testKeyPtr));
  printf("key2 = %d\n", get(map, testKeyPtr2));
  
  Key testKeyPtr3 = (Key) &key3;
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  incrementKeyValue(map, testKeyPtr3);
  printf("key3 = \%d\n", get(map, testKeyPtr3));

  HashMap* map2 = newMap(20, &stringHasher, &stringComparator, &stringCopy);
  Hash key4 = 0;
  Key testKeyPtr4 = (Key) &key4;
  incrementKeyValue(map2, testKeyPtr4);
  incrementKeyValue(map2, testKeyPtr4);
  Hash key5 = 30;
  Key testKeyPtr5 = (Key) &key5;
  incrementKeyValue(map2, testKeyPtr5);
  incrementKeyValue(map2, testKeyPtr5);
  printf("key4 = %d\n", get(map2, testKeyPtr4));
  printf("key5 = %d\n", get(map2, testKeyPtr5));
  Hash key6 = 40;
  Key testKeyPtr6 = (Key) &key6;
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  incrementKeyValue(map2, testKeyPtr6);
  printf("key6 = \%d\n", get(map2, testKeyPtr6));

  Hash key7 = 1;
  Key testKeyPtr7 = (Key) &key7;
  incrementKeyValue(map2, testKeyPtr7);
  printf("key7 = \%d\n", get(map2, testKeyPtr7));

  HashMap** maps = (HashMap**) malloc(sizeof(HashMap*) * 2);
  maps[0] = map;
  maps[1] = map2;

  printf("key + key4 = \%d\n", get(map, testKeyPtr));
  printf("key6 = \%d\n", get(map, testKeyPtr6));
  printf("key5 = \%d\n", get(map, testKeyPtr5));
  printf("key3 = \%d\n", get(map, testKeyPtr3));
  printf("key7 = \%d\n", get(map, testKeyPtr7));
  printf("key + key4 = \%d\n", get(map, testKeyPtr));
  printf("key6 = \%d\n", get(map, testKeyPtr6));
  printf("key5 = \%d\n", get(map, testKeyPtr5));
  printf("key3 = \%d\n", get(map, testKeyPtr3));
  printf("key7 = \%d\n", get(map, testKeyPtr7));
  deleteMap(map2);
  deleteMap(map);
  free(maps);
}
