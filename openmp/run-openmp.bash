#!/bin/sh
#BSUB -J  bertore_WordCountOMP
#BSUB -o output_log
#BSUB -e error_log
#BSUB -n 1
#BSUB -q ser-par-10g
#BSUB cwd /home/bertorelli.w/project/HPCWordCloud/openmp
work=/home/bertorelli.w/project/HPCWordCloud/openmp
cd $work

export OMP_NUM_THREADS=32
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1

./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1

./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1

./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1

./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1
./openmp ../resources/bibleChapters/ good 2000
sleep 1

