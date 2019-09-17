#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	FILE *fa,*fb;
	int ca,cb;
	char buffer[7];
	fa=fopen("inpfile.c","r");
	if(fa==NULL){
		printf("Can't open the file\n");
		exit(0);
	}

	fb=fopen("opfile.c","w");
	ca=getc(fa);

	while(ca!=EOF){
		if(ca=='\"'){
			putc(ca,fb);
			ca=getc(fa);
			while(ca!='\"'){
				putc(ca,fb);
				ca=getc(fa);
			}
			putc(ca,fb);
		}
		else if(ca=='#'){
			fread(buffer,7,1,fa);
			if(strcmp(buffer,"include")==0 || strcmp(buffer,"INCLUDE")==0 || strncmp(buffer,"define",6)==0 || strncmp(buffer,"DEFINE",6)==0){
				ca=getc(fa);
				while(ca!='\n')
					ca=getc(fa);					
			}						
		}
		else
			putc(ca,fb);
		
		ca=getc(fa);
	}

	fclose(fa);
	fclose(fb);
	return 0;
}