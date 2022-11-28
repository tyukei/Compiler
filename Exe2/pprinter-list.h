#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXSTRSIZE 1024
#define MAXINTSIZE 2147483647

/* Token */
#define TNAME 1		  /* Name : Alphabet { Alphabet | Digit } */
#define TPROGRAM 2	  /* program : Keyword */
#define TVAR 3		  /* var : Keyword */
#define TARRAY 4	  /* array : Keyword */
#define TOF 5		  /* of : Keyword */
#define TBEGIN 6	  /* begin : Keyword */
#define TEND 7		  /* end : Keyword */
#define TIF 8		  /* if : Keyword */
#define TTHEN 9		  /* then : Keyword */
#define TELSE 10	  /* else : Keyword */
#define TPROCEDURE 11 /* procedure : Keyword */
#define TRETURN 12	  /* return : Keyword */
#define TCALL 13	  /* call : Keyword */
#define TWHILE 14	  /* while : Keyword */
#define TDO 15		  /* do : Keyword */
#define TNOT 16		  /* not : Keyword */
#define TOR 17		  /* or : Keyword */
#define TDIV 18		  /* div : Keyword */
#define TAND 19		  /* and : Keyword */
#define TCHAR 20	  /* char : Keyword */
#define TINTEGER 21	  /* integer : Keyword */
#define TBOOLEAN 22	  /* boolean : Keyword */
#define TREADLN 23	  /* readln : Keyword */
#define TWRITELN 24	  /* writeln : Keyword */
#define TTRUE 25	  /* true : Keyword */
#define TFALSE 26	  /* false : Keyword */
#define TNUMBER 27	  /* unsigned integer */
#define TSTRING 28	  /* String */
#define TPLUS 29	  /* + : symbol */
#define TMINUS 30	  /* - : symbol */
#define TSTAR 31	  /* * : symbol */
#define TEQUAL 32	  /* = : symbol */
#define TNOTEQ 33	  /* <> : symbol */
#define TLE 34		  /* < : symbol */
#define TLEEQ 35	  /* <= : symbol */
#define TGR 36		  /* > : symbol */
#define TGREQ 37	  /* >= : symbol */
#define TLPAREN 38	  /* ( : symbol */
#define TRPAREN 39	  /* ) : symbol */
#define TLSQPAREN 40  /* [ : symbol */
#define TRSQPAREN 41  /* ] : symbol */
#define TASSIGN 42	  /* := : symbol */
#define TDOT 43		  /* . : symbol */
#define TCOMMA 44	  /* , : symbol */
#define TCOLON 45	  /* : : symbol */
#define TSEMI 46	  /* ; : symbol */
#define TREAD 47	  /* read : Keyword */
#define TWRITE 48	  /* write : Keyword */
#define TBREAK 49	  /* break : Keyword */

#define NUMOFTOKEN 49

/* token-list.c */

#define KEYWORDSIZE 28

extern struct KEY
{
	char *keyword;
	int keytoken;
} key[KEYWORDSIZE];

extern void error(char *mes);
extern char *tokenstr[NUMOFTOKEN + 1];
extern void init_idtab();
extern void id_countup(char *np);
extern void print_idtab();
extern void release_idtab();

/* list-scan.c */
extern int init_scan(char *filename);
extern int scan(void);
extern int num_attr;
extern char string_attr[MAXSTRSIZE];
extern int get_linenum(void);
extern void end_scan(void);
extern int isNumber(int c);
extern int isChar(int c);
extern void UntilFun(int c);
extern void UntilComment(void);
extern void UntilString(void);
extern void print_indent(void);
extern void print_tab(void);
extern void init_string_atr(int count);
extern int programPrint(int count);
extern int beginPrint(int count);
extern int endPrint(int count);
extern int ifPrint(int count);
extern int elsePrint(int count);
extern int thenPrint(int count);
extern int noteqPrint(void);
extern int grPrint(void);
extern int assignPrint(void);
extern int semiPrint(void);

/* pprinter-list.c */
extern void error(char *mes);

/* ebnf-list.c */
extern void set_token(int token);
extern int parse_program();
extern int parse_block();
extern int parse_variable_declaration();
extern int parse_variable_names();
extern int parse_variable_name();
extern int parse_type();
extern int parse_standard_type();
extern int parse_array_type();
extern int parse_subprogram_declaration();
extern int parse_procedure_name();
extern int parse_formal_parameters();
extern int parse_compound_statement();
extern int parse_statement();
extern int parse_condition_statement();
extern int parse_iteration_statement();
extern int parse_exit_statement();
extern int parse_call_statement();
extern int parse_expressions();
extern int parse_return_statement();
extern int parse_assignment_statement();
extern int parse_left_part();
extern int parse_variable();
extern int parse_expression();
extern int parse_simple_expression();
extern int parse_term();
extern int parse_factor();
extern int parse_constant();
extern int parse_multiplicative_operator();
extern int parse_additive_operator();
extern int parse_relational_operator();
extern int parse_input_statement();
extern int parse_output_statement();
extern int parse_output_format();
extern int parse_empty_statement();