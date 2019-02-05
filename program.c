#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

//function to compile regEx pattern
int match(const char *string, const char *pattern){
  regex_t re;
  if(regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) !=0) return 0;
  int status = regexec(&re, string,0, NULL,0);
  regfree(&re);
  if(status!= 0) return 0;
  return 1;
}

int main(int argc, char *argv[]){

//checks for the correct number of arguements
if(argc!=3){
  printf("Error: Please provide only 3 arguments.\n");
  printf("Example:  Badwordremover input.txt config.txt\n");
  exit(0);
}

  FILE *input, *output, *config;
  const char* str2;
  const char* delims = " ";
  char* token;

  char *txtPtr;
  char *exp;
  char *ch;
  size_t len=0;
  ssize_t read;
  char content;

  int i,cont,sz;
  int space, regMatch;

  //open config and input files from command line arguments
  if((input = fopen(argv[1], "r")) == NULL){
    printf("Error opening file : %s", argv[1]);
    exit(1);
  }

  printf("[*] Input file open...\n");



  //get file size
  fseek(input, 0L, SEEK_END);
  sz = ftell(input) +1;
  printf("[*] File Size = %d\n", sz);
  rewind(input);

  //set buffer sizes
  char finalBuffer[sz];
  char tempBuffer[sz];
  char text[sz];

  //open and error check config file
  if((config = fopen(argv[2], "r")) == NULL){
    printf("Error opening file : %s", argv[2]);
    exit(1);
  }
  printf("[*] Config file open...\n");


  //read file content into text array
  for( i=0; (i < (sizeof(text)-1)&&((cont =fgetc(input)) != EOF)); i++){
    text[i] = cont;
  }

  text[i] = '\0';
  printf("[*] Input file read...\n");

  //points to input string for parsing by space delimiter
  txtPtr = text;
  char* ptr = strdup(txtPtr);
  token = strtok(ptr, delims);

//loops through each config regular expression
while((read = getline(&exp, &len, config)) != -1){




memset(finalBuffer, 0, 255); //clears buffer



  exp[strcspn(exp, "\r\n")] =0; //strips regex of return and newline
  printf("[*] Checking for expression: %s\n", exp);

//builds output string
  while(token != NULL){
    //token[strcspn(token, "\n")] =0;
    if(match(token, exp)){
      token = strtok(NULL, delims);
      continue;
    }


    strcat(finalBuffer, token);
    strcat(finalBuffer, " ");

    token = strtok(NULL, delims);

  }

  strncpy(tempBuffer, finalBuffer, sz);
  txtPtr = tempBuffer;
  char* ptr = strdup(txtPtr);
  token = strtok(ptr, delims);

}

//saving output to file
output = fopen("filtered.txt", "w");
fprintf(output,"%s", finalBuffer);
printf("[*] Filtered output saved to filtered.txt ...\n");

printf("\n**Filtered output**\n%s\n",  finalBuffer);

fclose(input);
fclose(config);
free(ptr);
fclose(output);

return 0;

}
