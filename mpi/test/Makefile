all: testmpiUtil

testmpiUtil:
	gcc -o testmpiUtil ../src/testmpiUtil.c ../src/mpiUtil.c ../../hashmap/src/HashMap.c ../../hashmap/src/MapUtil.c -I../include/ -I../../hashmap/include/

clean:
	rm testmpiUtil
