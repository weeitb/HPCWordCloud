#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
  FILE *fp1;
  char word[100];
  char word2[100];
  char* startWord;
  char* endWord;
  int c;
  fp1 = fopen("Alice_In_Wonderland.txt", "r");
  int i = 0;
  do {
    c = fscanf(fp1, "%s", word);
    startWord = word;
    endWord = word;
    while(*startWord && *endWord) {
      startWord = endWord;
      while(*startWord && !isalpha(*startWord)) {
	*startWord = tolower(*startWord);
	startWord++;
      }
      endWord = startWord;
      while (*endWord && (isalpha(*endWord) || *endWord == '\'')) {
	*endWord = tolower(*endWord);
	endWord++;
      }
      if (startWord != endWord) {
	strncpy(word2, startWord, endWord - startWord);
	word2[endWord - startWord] = 0;
	printf("%s, %d\n", word2, endWord - startWord);
      }
      //printf("%s\n", word);
      i++;
    }
  } while (c != EOF || i < 50);

  fclose(fp1);
}
