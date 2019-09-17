%{
	int vows=0,conson=0;
%}

%% 

[a|e|i|o|u|A|E|I|O|U] {vows++;}
[a-zA-Z] {conson++;}

%%

main(int argc,char **argv){
	yyin=fopen("inpfile.c","r");
	yylex();	
	printf("\n\nVowels:%d  Consonants:%d\n",vows,conson);
	return 0;
}

int yywrap(){return 1;}


