-----------------------Repository Structure-------------------------------------

HPCWordCloud/ Top level folder containing repository
            hashmap/ source code related to hashmap implementation.
                   src/ C Source files for hashmap
                   include/ C Header files for hashmap
                   test/ code for testing hashmap independently
            sequential/ Code for running word count sequentially.
                      src/Main.c Sequential source code entry point. Timing is
		      performed here.
                      run-sequential.bash Bash file for submitting sequential
		                          job to lsf on Discovery Cluster.
                      run-results/ Output files of runs performed for sequential
		                   timing measurements.
                      Makefile Build script for building sequential configuration
		               of word counting.
             resources/ Sample text to parse.
                      bibleChapters/ Text files for measuring run-time.
            openmp/ source code related to hashmap implementation.
                  src/ C Source files for openmp utility functions that use the
	               openmp hashmap code. Includes Main.c which is the
		       openmp entry point to the algorithm that contains timing
		       calculations.
                  include/ C Header files for openmp utility functions
                  test/ code for testing utility functions independently
                  run-openmp.bash Bash file for submitting parallel job to lsf on
	                          Discovery Cluster.
                  run-results/ Output files of runs performed for parallel timing
	                       measurements.
                  Makefile build script for building openmp parallel configuration
		           of word counting.
            mpi/ source code related to hashmap implementation.
               src/ C Source files for openmp utility functions that use the
	            parallel mpi hashmap code. Includes Main.c which is the
		    mpi entry point to the algorithm that contains timing
		    calculations.
               include/ C Header files for openmp utility functions
               test/ code for testing utility functions independently
               run-mpi.bash Bash file for submitting parallel job to lsf on
	                    Discovery Cluster.
               run-results/ Output files of runs performed for parallel timing
	                    measurements.
               Makefile build script for building mpi parallel configuration of
	                word counting.

----------------------------Running the source code-----------------------------
SEQUENTIAL:
The following steps describe how to run the Serial code to reproduce results
[1.] Download the Project Update Sequential Code release for the stable branch of
the codeline for this project submission at:
https://hithub.com/weeitb/HPCWordCloud
[2.] Enter the directory HPCWordCloud/sequential
[3.] Call 'make'
[4.] The code can then be called through the command line, or issuing a job
through the batch script. Call the code on the command line as such (after
requesting an interactive node):
  ./sequential <path to directory of texts> (good) | (bad) <hashmap array size>

A specific example being:
  ./sequential ../resources/bibleChapters/ good 1000

Alternatively, the code can be rerun by issuing a batch job through the following
steps:
     [i] Edit lines 7 and 8 of run-sequential.bash to set the working directory
     to the current directory the script is located in.
     [ii] Submit a job to the discovery cluster queue through the command:
       'bsub $<$ run-sequential.bash'
     [iii] Output logs will be written in the current directory to output_log


OpenMP:
The following steps describe how to run the Parallel code to reproduce results
in the report.
[1.] Download the Project Update Paralllel 1 Code release for the stable branch
of the codeline for this project submission at:
https://hithub.com/weeitb/HPCWordCloud
[2.] Enter the directory HPCWordCloud/openmp
[3.] Call 'make'
[4.] The code can then be called through the command line, or issuing a job
through the batch script. Call the code on the command line as such (after
requesting an interactive node):
  ./openmp <path to directory of texts> (good) | (bad) <hashmap array size>

A specific example being:
  ./openmp ../resources/bibleChapters/ good 2000

Alternatively, the code can be rerun by issuing a batch job through as such:
     [i] Edit lines 7 and 8 of run-openmp.bash to set the working directory to
     the current directory the script is located in.
     [ii] Submit a job to the discovery cluster queue through the command
       'bsub $<$ run-openmp.bash'

     [iii] Output logs will be written in the current directory to output_log

MPI:
The following steps describe how to run the mpi results to reproduce results shown
in the report.
[1.] Download the Project Update Paralllel 2 Code release for the stable branch of the codeline for this project submission. See references for url.
[2.] Enter the directory HPCWordCloud/mpi
[3.] Call 'make'
[4.] The code can then be called through issuing a job through the batch script by following the steps below:
     [i] Edit lines 7 and 8 of run-mpi.bash to set the working directory to the current directory the script is located in.
     [ii] Submit a job to the discovery cluster queue through the command
	'bsub $<$ run-mpi.bash'
     [iii] Output logs will be written in the current directory to output_file
