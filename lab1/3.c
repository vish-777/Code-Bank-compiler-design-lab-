#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
	FILE *fa;
	int ca, cb;
	int x;
	fa = fopen("inpfile.c", "r");
	if (fa == NULL){
		printf("Cannot open file \n");
		exit(0); 
	}
	
	ca = fgetc(fa);
	char word[][20]={"int","char","double","define","break","return","if"};
	
	int i=0;
	char buf[20];
	
	int line=1,column=1;
	while (ca != EOF){
			
			do{
				if(isalpha(ca)){
					buf[i++]=ca;
					ca=getc(fa);                    //store letters in buffer
					column++;
				}
				else
					break;					
			}while(1);
			
			buf[i]='\0';
			if(ca=='\n'){
				line++;
				column=0;
			}
			//printf("word:%s\n",buf);
			if(ca!='_'){
				for(int j=0;j<7;j++){                                  //checking its an identifier(show line and column)
					if(strcmp(word[j],buf)==0){
						for(int k=0;k<i;k++)
							printf("%c",toupper(buf[k]));												
						printf(" (Line:%d,column:%d)\n",line,column-(int)strlen(buf));
					}	
				}
			}
			i=0;
			ca=getc(fa);
			column++;			
	}
	
	fclose(fa);
	
	return 0; 
}
