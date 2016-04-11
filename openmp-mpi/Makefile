all:
	mpicc -fopenmp -o openmp-mpi src/Main.c ../hashmap/src/HashMap.c ../hashmap/src/MapUtil.c ../openmp/src/OpenMPUtil.c ../mpi/src/mpiUtil.h ../hashmap/src/FileParser.c -I../hashmap/include/ -I../mpi/include/ -I../openmp/include/
