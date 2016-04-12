all:
	mpiCC  -o mpi src/Main.c ../hashmap/src/HashMap.c ../hashmap/src/stack.c ../hashmap/src/MapUtil.c src/mpiUtil.c ../hashmap/src/FileParser.c -I../hashmap/include/ -I./include/

clean:
	rm hostlist-tcp hostlistrun output_file error_file mpi core*
