#!/bin/sh
#BSUB -J word_cloud_mpi
#BSUB -o output_file
#BSUB -e error_file
#BSUB -n 32
#BSUB -R "span[ptile=5]"
#BSUB -q ht-10g
#BSUB cwd /home/bertorelli.w/project/HPCWordCloudParallel2/
work=/home/bertorelli.w/HPCWordCloudParallel2/
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

mpirun -np 32 -prot -TCP -lsf ./mpi

