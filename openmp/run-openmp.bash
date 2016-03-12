#!/bin/sh
#BSUB -J  bertore_WordCountOMP
#BSUB -o output_log
#BSUB -e error_log
#BSUB -n 10
#BSUB -q ht-10g
#BSUB cwd /home/bertorelli.w/project/HPCWordCloudOpenMP/openmp
work=/home/bertorelli.w/project/HPCWordCloudOpenMP/openmp
cd $work

export OMP_NUM_THREADS=10
echo "running algorithm with 10 threads, good hasher, bins ranging from 100 - 100000"
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
#echo "now bad"
#./openmp ../resources/bibleChapters/ bad 100000
# sleep 1
# ./openmp ../resources/bibleChapters/ good 100
# sleep 1
# ./openmp ../resources/bibleChapters/ good 1000
# sleep 1
# ./openmp ../resources/bibleChapters/ good 10000
# sleep 1
# ./openmp ../resources/bibleChapters/ good 100000

# echo "running algorithm with bad hasher, bins ranging from 100 - 100000"
# ./openmp ../resources/bibleChapters/ bad 10
# sleep 1
# ./openmp ../resources/bibleChapters/ bad 100
# sleep 1
# ./openmp ../resources/bibleChapters/ bad 1000
# sleep 1
# ./openmp ../resources/bibleChapters/ bad 10000
# sleep 1
# ./openmp ../resources/bibleChapters/ bad 100000

