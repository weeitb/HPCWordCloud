all: testStack testOpenMPUtil
testStack: 
	gcc -o testStack ../../hashmap/src/HashMap.c ../src/OpenMPUtil.c ../src/testStack.c -I../include/ -I../../hashmap/include/

testOpenMPUtil:
	gcc -o testOpenMPUtil ../src/testOpenMPUtil.c ../src/OpenMPUtil.c ../../hashmap/src/HashMap.c -I../include/ -I../../hashmap/include/
