#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUFF_SIZE 1024
#define F_NAME "/home/linus/code/ToDo/ToDoList.bin"
#define F_TEMP "/home/linus/code/ToDo/tmp.bin"
#define F_SAVE "/home/linus/code/ToDo/save.bin"

//Dumb github comment
/*void createSave(){
FILE *save;
if ((save = fopen(F_SAVE,"wb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
	}
}
*/
void initFile(){
FILE *fptr;
FILE *save;
char *tempChr;
if ((fptr = fopen(F_NAME,"wb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
}
/*if ((save = fopen(F_SAVE,"rb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
}

while(fread(&tempChr,sizeof(char),1,save) > 0){
	fwrite(&tempChr,sizeof(char),1,fptr);
}
*/
fclose(fptr);
}

void saveFile(){
FILE *fptr;
FILE *save;
char* tempChr;
if ((fptr = fopen(F_NAME,"rb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
}
if ((save = fopen(F_SAVE,"wb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
}
while(fread(&tempChr,sizeof(char),1,fptr) > 0){
	fwrite(&tempChr,sizeof(char),1,save);
}
fclose(fptr);
fclose(save);
}

void appendToFile(char* task){
FILE *fptr; 
FILE *tmp;
char tempChr;
if ((fptr = fopen(F_NAME,"rb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
}
if ((tmp = fopen(F_TEMP,"wb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
}
while(fread(&tempChr,sizeof(char),1,fptr) > 0){
	fwrite(&tempChr,sizeof(char),1,tmp);
}
fclose(fptr);
fwrite(task,sizeof(char)*strlen(task) + 1,1,tmp);
fclose(tmp);
remove(F_NAME);
rename(F_TEMP,F_NAME);
}

void printFile(){
FILE *fptr;
if ((fptr = fopen(F_NAME,"rb")) == NULL){
	fprintf(stderr, "Error Could Not Open File");
	exit(1);
}
int i = 0;
size_t buffSize = BUFF_SIZE;
char* tempStr = malloc(sizeof(char) * buffSize);
char tempChr;
while(fread(&tempChr,sizeof(char),1,fptr) > 0){
if(tempChr == '\0'){
tempStr[i] = '\n';
tempStr[i+1] = '\0';
printf("%s",tempStr);
i = 0;
}
else{
tempStr[i] = tempChr;
i++;
}
}
free(tempStr);
fclose(fptr);
}

int main(int argc, char* argv[]){
 int s = 1;
 char c;
FILE *fptr;
int loop = 0;
//createSave();
//remove(F_NAME);
initFile();
printf("Enter a task or q to quit\n");
char* userString = malloc(sizeof(char) * BUFF_SIZE);
while(s != 0){
fgets(userString,sizeof(char) * BUFF_SIZE,stdin);
userString[strchr(userString,'\n') - userString] = '\0';
  if(userString[0] == '\0'){
    printf("Please enter a character\n");
 }
  if(userString[1] == '\0' && userString[0] == 'q'){
    s = 1;
    printf("Exiting Program\n");
    break;
  }
  appendToFile(userString);
 }
printFile();
return 0;
}
