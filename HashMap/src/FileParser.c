#include <stdio.h>
#include <string.h>

int readFile(char* filename, unsigned int startPosition, HashMap map) {
  FILE *fp1;
  char line[100];
  char* word[20];
  char* startIdx;
  char* stopIdx;
  int c;
  fp1 = fopen(filename, "r");
  
  // Jump to first new line after position specified.
  if (startPosition != 0) {
    // Jump 1 space back from desired position in case we land 
    // exactly on a new line.
    fseek(fp1, startPosition - 1, SEEK_SET);
  }
  fgets(line, 100, fp1);
  
  while(fgets(line, 100, fp1)) {
    startIdx = line;
    stopIdx = line;
    
    while(*startIdx && *stopIdx) {
      startIdx = stopIdx;
      // Stop when we encounter the first alphabetical character
      while(*startIdx && !isalpha(*startIdx)) {
	startIdx++;
      }
      // convert alphabetical character to lowercase
      *startIdx = tolower(*startIdx);
      stopIdx = startIdx;
      // Stop when we encounter the first non-alphabetical character
      // (include apostraphe for conjunctions)
      while (*stopIdx && (isalpha(*stopIdx) || *stopIdx == '\'')) {
	// Convert each alphabetical character to lowercase
	*stopIdx = tolower(*stopIdx);
	stopIdx++;
      }
      // If we have a valid string of characters, add it.
      if (startIdx != stopIdx) {
	strncpy(word, startIdx, stopIdx - startIdx);
	word[stopIdx - startIdx] = 0;
	incrementKeyValu(map, word);
      }
    }
  }
  fclose(fp1);
  return 0;
}
