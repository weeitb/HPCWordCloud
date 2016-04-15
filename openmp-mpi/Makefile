all:
	mpiCC  -fopenmp -o openmp-mpi src/Main.c ../hashmap/src/HashMap.c ../hashmap/src/stack.c ../hashmap/src/MapUtil.c ../mpi/src/mpiUtil.c ../openmp/src/OpenMPUtil.c ../hashmap/src/FileParser.c -I../hashmap/include/ -I../mpi/include/ -I../openmp/include/

clean:
	rm hostlist-tcp hostlistrun output_file error_file openmp-mpi core*
