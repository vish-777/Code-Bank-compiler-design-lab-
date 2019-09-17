%{
	int simple_flag = 1;
%}
%%
(and|or|if) {simple_flag = 0; }
%%
main(int argc,char **argv){
        yyin=fopen("inpfile.c","r");
	yylex();
	if(simple_flag)
		printf("Simple!\n");
	else
		printf("Compound!\n");
	return 0;
}
int yywrap() {
	return 1;
}
