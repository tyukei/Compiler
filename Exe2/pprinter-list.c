#include "pprinter-list.h"

/* keyword list */
struct KEY key[KEYWORDSIZE] = {
	{"and", TAND},
	{"array", TARRAY},
	{"begin", TBEGIN},
	{"boolean", TBOOLEAN},
	{"break", TBREAK},
	{"call", TCALL},
	{"char", TCHAR},
	{"div", TDIV},
	{"do", TDO},
	{"else", TELSE},
	{"end", TEND},
	{"false", TFALSE},
	{"if", TIF},
	{"integer", TINTEGER},
	{"not", TNOT},
	{"of", TOF},
	{"or", TOR},
	{"procedure", TPROCEDURE},
	{"program", TPROGRAM},
	{"read", TREAD},
	{"readln", TREADLN},
	{"return", TRETURN},
	{"then", TTHEN},
	{"true", TTRUE},
	{"var", TVAR},
	{"while", TWHILE},
	{"write", TWRITE},
	{"writeln", TWRITELN}};

/* Token counter */
int numtoken[NUMOFTOKEN + 1] = {0};

/* string of each token */
char *tokenstr[NUMOFTOKEN + 1] = {
	"",
	"NAME", "program", "var", "array", "of", "begin", "end", "if", "then",
	"else", "procedure", "return", "call", "while", "do", "not", "or",
	"div", "and", "char", "integer", "boolean", "readln", "writeln", "true",
	"false", "NUMBER", "STRING", "+", "-", "*", "=", "<>", "<", "<=", ">",
	">=", "(", ")", "[", "]", ":=", ".", ",", ":", ";", "read", "write", "break"};

char filename[FILENAME_MAX];

int main(int nc, char *np[])
{
	int token, i;

	if (nc < 2)
	{
		printf("File name id not given.\n");
		return 0;
	}
	if (init_scan(np[1]) < 0)
	{
		printf("File %s can not open.\n", np[1]);
		return 0;
	}
	strcat(filename, np[1]);
	token = scan();
	set_token(token);
	parse_program();

	end_scan();
	return 0;
}

void error(char *mes)
{
	int line = get_linenum();
	printf("\x1b[31m");
	printf("\nERROR(%d): %s", line, mes);
	printf("Check grammar of %d line in %s\n\n", line, filename);
	printf("\x1b[0m");
	end_scan();
	exit(1);
}