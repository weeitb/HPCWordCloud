#!/bin/sh
#BSUB -J word_cloud_mpi
#BSUB -o output_file
#BSUB -e error_file
#BSUB -n 16
#BSUB -R "span[ptile=4]"
#BSUB -q ht-10g
#BSUB cwd /home/bertorelli.w/project/project/mpi
work=/home/bertorelli.w/project/project/mpi
cd $work
tempfile1=hostlistrun
tempfile2=hostlist-tcp
echo $LSB_MCPU_HOSTS > $tempfile1
declare -a hosts
read -a hosts < ${tempfile1}
for ((i=0; i<${#hosts[@]}; i+=2)) ;
  do
    HOST=${hosts[$i]}
    CORE=${hosts[(($i+1))]}
    echo $HOST:$CORE >> $tempfile2
done

mpirun -np 16 -prot -TCP -lsf ./mpi

