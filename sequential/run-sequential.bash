#!/bin/sh
#BSUB -J  bertore_WordCountSeq
#BSUB -o output_log
#BSUB -e error_log
#BSUB -n 10
#BSUB -q ht-10g
#BSUB cwd /home/bertorelli.w/project/HPCWordCloudOpenMP/sequential
work=/home/bertorelli.w/project/HPCWordCloudOpenMP/sequential
cd $work
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1
./sequential ../resources/bibleChapters/ good 2000
sleep 1

# sleep 1
# ./sequential ../resources/bibleChapters/ good 100
# sleep 1
# ./sequential ../resources/bibleChapters/ good 1000
# sleep 1
# ./sequential ../resources/bibleChapters/ good 10000
# sleep 1
# ./sequential ../resources/bibleChapters/ good 100000

# echo "running algorithm with bad hasher, bins ranging from 100 - 100000"
# ./sequential ../resources/bibleChapters/ bad 10
# sleep 1
# ./sequential ../resources/bibleChapters/ bad 100
# sleep 1
# ./sequential ../resources/bibleChapters/ bad 1000
# sleep 1
# ./sequential ../resources/bibleChapters/ bad 10000
# sleep 1
# ./sequential ../resources/bibleChapters/ bad 100000

