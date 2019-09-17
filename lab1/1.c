#include<stdio.h>
#include<stdlib.h>  
int main(){
	FILE *fa,*fb;
	int ca,cb;
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
		else if(ca=='\t' || ca==' '){
			putc(' ',fb);
			ca=getc(fa);
			if(ca=='\t' || ca==' '){
				while(ca=='\t' || ca==' '){
					ca=getc(fa);
					if(ca!=' ' && ca!='\t'){
						putc(ca,fb);
						break;
					}
				}	
			}
			else
				putc(ca,fb);
		}			
		else
			putc(ca,fb);

		ca=getc(fa);
	}

	fclose(fa);
	fclose(fb);
	return 0;
}