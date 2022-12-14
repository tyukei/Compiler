#include "token-list.h"
#define ERROR (-1)
#define EOFCODE (-2)
int cbuf, num_line = 0;
int num_attr;
char string_attr[MAXSTRSIZE];
FILE *fp = NULL;

int init_scan(char *filename) { /* open file if it suceed return 0 and if not return -1 */
	if ((fp = fopen(filename, "r+")) == NULL) {
		return ERROR;
	} else {
		cbuf = fgetc(fp);
		return 0;
	}
}

int scan(void) {
	int isSeparator = 1;
	while (isSeparator) { // if  separator, skip read
		switch (cbuf) {
		case '\r': //end of line
			cbuf = fgetc(fp);
			if(cbuf == '\n'){
				cbuf = fgetc(fp);
			}
			num_line++;
			break;
		case '\n': //end of line Unix,Mac
			cbuf = fgetc(fp);
			if(cbuf == '\r'){
				cbuf = fgetc(fp);
			}
			num_line++;
			break;		
		// case '\n': //end of line Unix,Mac
		// 	cbuf = fgetc(fp);
		// 	num_line++;
		// 	break;	
		case ' ': //space
		case '\t': //tab
			cbuf = fgetc(fp);
			break;
		case '{': //coment {...}
			UntilFun('}');
			break;
		case '/':
			cbuf = fgetc(fp);
			if (cbuf == '*') {		
				UntilComment();
				break;
			}else{
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
	if (isChar(cbuf)) { // if char, read them by end
		int i, j = 0;
		for (i = 0; (isChar(cbuf) + isNumber(cbuf)) >= 1; i++) {
			string_attr[i] = cbuf;
			if(i >= MAXSTRSIZE){
				error("string is too long\n");
				return ERROR;
			}
			cbuf = fgetc(fp);
			count++;
		}
		//printf("string_attr: %s\n", string_attr);
		id_countup(string_attr);
		for (j = 0; j <= NUMOFTOKEN; j++) { //check whether keyword or name
			if (strcmp(string_attr, key[j].keyword) == 0) {
				while (count >= 0) {//init string_attr
					string_attr[count] = '\0';
					count--;
				}
				return key[j].keytoken; //retrun keyword
				break;
			}
		}
		while (count >= 0) { //init string_attr
			string_attr[count] = '\0';
			count--;
		}
		return TNAME; //return name
	} else if (isNumber(cbuf)) { //if number, read them by end
		int i = 0;
		num_attr = 0;
		for (i = 0; isNumber(cbuf)>0; i++) {
			num_attr = num_attr * 10 + (cbuf-48);
			cbuf = fgetc(fp);
			if((num_attr > MAXINTSIZE)||(num_attr < 0)){
				error("number is too long\n");
				return ERROR;
			}
		}
		return TNUMBER;
	} else {
		int i = TPLUS;
		for (i = TPLUS; i <= TSEMI; i++) {
			if (cbuf == tokenstr[i][0]) {
				cbuf = fgetc(fp);
				return i;
			}
		}
		if(cbuf == EOF){
			return EOFCODE;
		}

		char dst[100];
		snprintf(dst, sizeof dst, "%c is undeclared.\n", cbuf);
		error(dst);
		return ERROR;
	}
}

int isNumber(int c) {
	if (c >= '0' && c <= '9') {
		return 1;
	} else {
		return 0;
	}
}

int isChar(int c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		return 1;
	} else {
		return 0;
	}
}

void UntilFun(int c) {
	char cin = cbuf;
	cbuf = fgetc(fp);
	while (cbuf != c) {
		if (cbuf == EOF) {
			char mes[100];
			sprintf(mes, "%c is undeclared. %c is expected.\n",cin,c);
			error(mes);
			break;
		}
		cbuf = fgetc(fp);
	}
	cbuf = fgetc(fp);
}

void UntilComment(void) {
	while (1) {
		cbuf = fgetc(fp);
		if (cbuf == '*') {
			cbuf = fgetc(fp);
			if (cbuf == '/') {
				cbuf = fgetc(fp);
				break;
			}
		}
		if (cbuf == EOF) {
			error("/* is undeclared.another */ is expected.\n");
			break;
		}
	}
}

void UntilString(void) {
	while (1) {
		cbuf = fgetc(fp);
		if (cbuf == '\'') {
			cbuf = fgetc(fp);
			if (cbuf != '\'') {
				cbuf = fgetc(fp);
				break;
			}
		}
		if (cbuf == EOF) {
			error("\' is undeclared.another \' is expected.\n");
			break;
		}
	}
}

int get_linenum(void) {
	return num_line;
}
void end_scan(void) {
	fclose(fp);
}
