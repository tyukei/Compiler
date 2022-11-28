#include "pprinter-list.h"
#define ERROR (-1)
#define EOFCODE (-2)
int cbuf, num_line = 1;
int num_indent = 1;
int num_attr;
int num_then = 0;
enum PreState
{
	OTEHER,
	SEMI,
	THEN,
	ELSE
};
enum PreState prestate = OTEHER;
char string_attr[MAXSTRSIZE];
FILE *fp = NULL;

int init_scan(char *filename)
{ /* open file if it suceed return 0 and if not return -1 */
	if ((fp = fopen(filename, "r+")) == NULL)
	{
		return ERROR;
	}
	else
	{
		cbuf = fgetc(fp);
		return 0;
	}
}

int scan(void)
{
	int isSeparator = 1;
	while (isSeparator)
	{ // if  separator, skip read
		switch (cbuf)
		{
		case '\r': // end of line
			cbuf = fgetc(fp);
			if (cbuf == '\n')
			{
				cbuf = fgetc(fp);
			}
			num_line++;
			break;
		case '\n': // end of line Unix,Mac
			cbuf = fgetc(fp);
			if (cbuf == '\r')
			{
				cbuf = fgetc(fp);
			}
			num_line++;
			break;
		case ' ':  // space
		case '\t': // tab
			cbuf = fgetc(fp);
			break;
		case '{': // coment {...}
			UntilFun('}');
			break;
		case '/':
			cbuf = fgetc(fp);
			if (cbuf == '*')
			{
				UntilComment();
				break;
			}
			else
			{
				error("/ is not undeclared\n");
				return ERROR;
			}
			break;
		case '\'':
			UntilString();
			return TSTRING;
			break;
		default:
			isSeparator = 0;
			break;
		}
	}
	int count = 0;
	if (isChar(cbuf))
	{ // if char, read them by end
		int i, j = 0;
		for (i = 0; (isChar(cbuf) + isNumber(cbuf)) >= 1; i++)
		{
			string_attr[i] = cbuf;
			if (i >= MAXSTRSIZE)
			{
				error("string is too long\n");
				return ERROR;
			}
			cbuf = fgetc(fp);
			count++;
		}
		// cbuf = fgetc(fp);
		// id_countup(string_attr);
		for (j = 0; j <= NUMOFTOKEN; j++)
		{ // check whether keyword or name
			if (strcmp(string_attr, key[j].keyword) == 0)
			{
				if (key[j].keytoken == TPROGRAM)
				{
					return programPrint(count);
				}
				else if (key[j].keytoken == TBEGIN)
				{ // if begin, print next line
					return beginPrint(count);
				}
				else if (key[j].keytoken == TEND)
				{ // if end, print next line
					return endPrint(count);
				}
				else if (key[j].keytoken == TIF)
				{ // if if, print next line
					return ifPrint(count);
				}
				else if (key[j].keytoken == TELSE)
				{ // if else, print next line
					return elsePrint(count);
				}
				else if (key[j].keytoken == TTHEN)
				{ // if then, print next line
					return thenPrint(count);
				}
				else
				{
					printf(" %s", string_attr);
					init_string_atr(count);
					return key[j].keytoken; // retrun keyword
				}
			}
		}
		printf(" %s", string_attr);
		init_string_atr(count);
		return TNAME; // return name
	}
	else if (isNumber(cbuf))
	{ // if number, read them by end
		int i = 0;
		num_attr = 0;
		for (i = 0; isNumber(cbuf) > 0; i++)
		{
			num_attr = num_attr * 10 + (cbuf - 48);
			cbuf = fgetc(fp);
			if ((num_attr > MAXINTSIZE) || (num_attr < 0))
			{
				error("number is too long\n");
				return ERROR;
			}
		}
		// cbuf = fgetc(fp);
		printf(" %d", num_attr);
		return TNUMBER;
	}
	else
	{
		int i = TPLUS;
		for (i = TPLUS; i <= TSEMI; i++)
		{
			if (cbuf == tokenstr[i][0])
			{
				if (i == TNOTEQ)
				{ // if cbuf is '<' check whether '<>' , '<=' or '<'
					return noteqPrint();
				}
				else if (i == TGR)
				{ // if cbuf is '>' check whether '>=' or '>'
					return grPrint();
				}
				else if (i == TASSIGN)
				{ // if cbuf is ':' check whether ':=' or ':'
					return assignPrint();
				}
				else if (i == TSEMI)
				{
					return semiPrint();
				}
				else
				{
					cbuf = fgetc(fp);
					printf(" %s", tokenstr[i]);
					return i;
				}
			}
		}
		if (cbuf == EOF)
		{
			return EOFCODE;
		}

		char dst[100];
		snprintf(dst, sizeof dst, "%c is undeclared.\n", cbuf);
		error(dst);
		return ERROR;
	}
}

int isNumber(int c)
{
	if (c >= '0' && c <= '9')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isChar(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void UntilFun(int c)
{
	char cin = cbuf;
	cbuf = fgetc(fp);
	while (cbuf != c)
	{
		if (cbuf == EOF)
		{
			char mes[100];
			sprintf(mes, "%c is undeclared. %c is expected.\n", cin, c);
			error(mes);
			break;
		}
		cbuf = fgetc(fp);
	}
	cbuf = fgetc(fp);
}

void UntilComment(void)
{
	while (1)
	{
		cbuf = fgetc(fp);
		if (cbuf == '*')
		{
			cbuf = fgetc(fp);
			if (cbuf == '/')
			{
				cbuf = fgetc(fp);
				break;
			}
		}
		if (cbuf == EOF)
		{
			error("/* is undeclared.another */ is expected.\n");
			break;
		}
	}
}

void UntilString(void)
{
	char sttemp[MAXSTRSIZE];
	int i = 0;
	sttemp[0] = '\'';
	while (i < MAXSTRSIZE)
	{
		cbuf = fgetc(fp);
		i++;
		sttemp[i] = cbuf;
		if (cbuf == '\'')
		{
			cbuf = fgetc(fp);
			if (cbuf != '\'')
			{
				int j = 0;
				printf(" ");
				while (j <= i)
				{ // print string
					printf("%c", sttemp[j]);
					j++;
				}
				break;
			}
			else
			{
				i++;
				sttemp[i] = '\'';
			}
		}
		if (cbuf == EOF)
		{
			error("\' is undeclared.another \' is expected.\n");
			break;
		}
	}
}

int get_linenum(void)
{
	return num_line;
}
void end_scan(void)
{
	fclose(fp);
}

void print_indent(void)
{
	int i = 0;
	printf("\n");
	for (i = 1; i < num_indent; i++)
	{
		printf("    ");
	}
}

void print_tab(void)
{
	int i = 0;
	for (i = 1; i < num_indent; i++)
	{
		printf("    ");
	}
}

void init_string_atr(int count)
{
	prestate = OTEHER;
	while (count >= 0)
	{ // init string_attr
		string_attr[count] = '\0';
		count--;
	}
}

int programPrint(int count)
{ // print process when token is program
	print_indent();
	printf(" %s", string_attr);
	init_string_atr(count);
	num_indent += 1;
	return TPROGRAM;
}

int beginPrint(int count)
{ // print process when token is begin
	if (prestate == THEN)
	{
		num_then--;
		num_indent--;
		printf("\r");
		print_tab();
		printf(" %s", string_attr);
		num_indent += 1;
		print_indent();
		init_string_atr(count);
		return TBEGIN;
	}
	else if (prestate == ELSE)
	{
		print_indent();
		printf(" %s", string_attr);
		num_indent += 1;
		print_indent();
		init_string_atr(count);
		return TBEGIN;
	}
	else if (prestate != SEMI)
	{
		print_indent();
		printf(" %s", string_attr);
		num_indent += 1;
		print_indent();
		init_string_atr(count);
		return TBEGIN;
	}
	else
	{
		printf(" %s", string_attr);
		num_indent += 1;
		print_indent();
		init_string_atr(count);
		return TBEGIN;
	}
}

int endPrint(int count)
{ // print process when token is end
	if (prestate == SEMI)
	{
		if (num_then > 0)
		{
			num_then -= 1;
			printf("\r");
			num_indent -= 2;
			print_tab();
			printf(" %s", string_attr);
			init_string_atr(count);
			return TEND;
		}
		printf("\r");
		num_indent -= 1;
		print_tab();
		printf(" %s", string_attr);
		init_string_atr(count);
		return TEND;
	}
	if (num_then > 0)
	{
		num_then -= 1;
		printf("\r");
		num_indent -= 1;
		print_tab();
		printf(" %s", string_attr);
		init_string_atr(count);
		return TEND;
	}
	num_indent -= 1;
	print_indent();
	printf(" %s", string_attr);
	init_string_atr(count);
	return TEND;
}

int ifPrint(int count)
{ // print process when token is if
	if (num_then > 0)
	{
		num_then -= 1;
		printf("\r");
		num_indent -= 1;
		print_tab();
	}
	printf(" %s", string_attr);
	init_string_atr(count);
	return TIF;
}

int elsePrint(int count)
{ // print process when token is else
	if (num_then > 0)
	{
		num_then--;
		printf("\r");
		num_indent--;
		print_indent();
		printf(" %s", string_attr);
		init_string_atr(count);
		prestate = ELSE;
		return TELSE;
	}
	else if (prestate == SEMI)
	{
		printf(" %s", string_attr);
		init_string_atr(count);
		prestate = ELSE;
		return TELSE;
	}
	else
	{
		print_indent();
		printf(" %s", string_attr);
		init_string_atr(count);
		prestate = ELSE;
		return TELSE;
	}
}

int thenPrint(int count)
{ // print process when token is then
	printf(" %s", string_attr);
	init_string_atr(count);
	num_indent += 1;
	print_indent();
	num_then += 1;
	prestate = THEN;
	return TTHEN;
}

int noteqPrint(void)
{
	cbuf = fgetc(fp);
	if (cbuf == '>')
	{
		cbuf = fgetc(fp);
		printf("%s", tokenstr[TNOTEQ]);
		return TNOTEQ;
	}
	else if (cbuf == '=')
	{
		cbuf = fgetc(fp);
		printf("%s", tokenstr[TLEEQ]);
		return TLEEQ;
	}
	else
	{
		printf("%s", tokenstr[TLE]);
		return TLE;
	}
}

int grPrint(void)
{
	cbuf = fgetc(fp);
	if (cbuf == '=')
	{
		cbuf = fgetc(fp);
		printf("%s", tokenstr[TGREQ]);
		return TGREQ;
	}
	else
	{
		printf("%s", tokenstr[TGR]);
		return TGR;
	}
}

int assignPrint(void)
{
	cbuf = fgetc(fp);
	if (cbuf == '=')
	{
		cbuf = fgetc(fp);
		printf(" %s", tokenstr[TASSIGN]);
		return TASSIGN;
	}
	else
	{
		printf("%s", tokenstr[TCOLON]);
		return TCOLON;
	}
}

int semiPrint(void)
{
	prestate = SEMI;
	cbuf = fgetc(fp);
	printf("%s", tokenstr[TSEMI]);
	print_indent();
	return TSEMI;
}
