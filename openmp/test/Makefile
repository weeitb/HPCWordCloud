all: testStack testOpenMPUtil
testStack: 
	gcc -o testStack ../src/testStack.c ../hashmap/src/HashMap.c -I../include/ -I../../hashmap/include/

testOpenMPUtil
	gcc -o testOpenMPUtil ../src/testOpenMPUtil.c ../src/OpenMPUtil.c -I../include/ -I../../hashmap/src/HashMap.c
