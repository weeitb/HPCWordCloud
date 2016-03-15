#!/bin/sh
#BSUB -J  bertore_WordCountOMP
#BSUB -o output_log
#BSUB -e error_log
#BSUB -n 1
#BSUB -q ht-10g
#BSUB cwd /home/bertorelli.w/project/HPCWordCloudOpenMP/openmp
work=/home/bertorelli.w/project/HPCWordCloudOpenMP/openmp
cd $work

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1

echo ""

export OMP_NUM_THREADS=4
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=8
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=16
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=24
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
export OMP_NUM_THREADS=32
 ./openmp ../resources/bibleChapters/ good 2000
sleep 1
