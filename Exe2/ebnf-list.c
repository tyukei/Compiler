#include "pprinter-list.h"
#define NOMAL 0
#define ERROR 1
int token;

void set_token(int t)
{
    token = t;
}

int parse_program()
{
    // program ::= "program" NAME ";" block "."
    if (token != TPROGRAM)
    {
        error("Keyword 'program' is not found\n");
        // return ERROR;
    }
    token = scan();
    if (token != TNAME)
    {
        error("Program name is not found\n");
    }
    token = scan();
    if (token != TSEMI)
    {
        error("';' is not found in parse_program\n");
    }
    token = scan();
    if (parse_block() == ERROR)
    {
        // error("Block is not found\n");
    }
    if (token != TDOT)
    {
        error("'.' is not found at the end of program\n");
    }
    printf("\n");
    token = scan();
    return NOMAL;
}

int parse_block()
{
    // block ::= {variable_declaration | procedure_declaration} compound_statement
    while ((token == TVAR) || (token == TPROCEDURE))
    {
        if (token == TVAR)
        {
            if (parse_variable_declaration() == ERROR)
            {
                // error("Variable declaration is not found in block\n");
            }
        }
        else if (token == TPROCEDURE)
        {
            if (parse_subprogram_declaration() == ERROR)
            {
                // error("Subprogram declaration is not found in block\n");
            }
        }
    }
    if (parse_compound_statement() == ERROR)
    {
        // error("Compound statement is not found in block\n");
    }
    return NOMAL;
}

int parse_variable_declaration()
{
    // variable_declaration ::= "var" variable_names ":" type ";" {variable_names ":" type ";"}

    // when call this function, token is "var"
    //  if(token != TVAR){
    //      error("Keyword 'var' is not found in variable_declaration\n");
    //  }
    token = scan();
    if (parse_variable_names() == ERROR)
    {
        // error("Variable name is not found in variable_declaration\n");
    }
    if (token != TCOLON)
    {
        error("':' is not found in variable_declaration1\n");
    }
    token = scan();
    if (parse_type() == ERROR)
    {
        // error("Type is not found in variable_declaration\n");
    }
    if (token != TSEMI)
    {
        error("';' is not found in variable_declaration\n");
    }
    token = scan();
    while (token == TNAME)
    {
        if (parse_variable_names() == ERROR)
        {
            // error("Variable name is not found in variable_declaration\n");
        }
        if (token != TCOLON)
        {
            error("':' is not found in variable_declaration2\n");
        }
        token = scan();
        if (parse_type() == ERROR)
        {
            // error("Type is not found in variable_declaration\n");
        }
        if (token != TSEMI)
        {
            error("';' is not found in variable_declaration\n");
        }
        token = scan();
    }
    return NOMAL;
}

int parse_variable_names()
{
    // variable_names ::= NAME {"," NAME}
    if (token != TNAME)
    {
        error("Variable name is not found in variable_names1\n");
    }
    token = scan();
    while (token == TCOMMA)
    {
        token = scan();
        if (token != TNAME)
        {
            error("Variable name is not found in variable_names2\n");
        }
        token = scan();
    }
    return NOMAL;
}

int parse_type()
{
    // type ::= standard_type | array_type
    if (token == TINTEGER || token == TBOOLEAN || token == TCHAR)
    {
        if (parse_standard_type() == ERROR)
        {
            // error("Standard type is not found in type\n");
        }
    }
    else if (token == TARRAY)
    {
        if (parse_array_type() == ERROR)
        {
            // error("Array type is not found in type\n");
        }
    }
    else
    {
        error("Type is not found in type\n");
    }
    return NOMAL;
}

int parse_standard_type()
{
    // standard_type ::= "integer" | "boolean" | "char"
    switch (token)
    {
    case TINTEGER:
    case TBOOLEAN:
    case TCHAR:
        token = scan();
        break;
    default:
        error("Standard type is not found in standard_type\n");
    }
    return NOMAL;
}

int parse_array_type()
{
    // array_type ::= "array" "[" NUMBER "]" "of" standard_type

    // when call this function, token is "array"
    //  if(token != TARRAY){
    //      error("Keyword 'array' is not found in array_type\n");
    // }
    token = scan();
    if (token != TLSQPAREN)
    {
        error("'[' is not found in array_type\n");
    }
    token = scan();
    if (token != TNUMBER)
    {
        error("Number is not found in array_type\n");
    }
    token = scan();
    if (token != TRSQPAREN)
    {
        error("']' is not found in array_type\n");
    }
    token = scan();
    if (token != TOF)
    {
        error("Keyword 'of' is not found in array_type\n");
    }
    token = scan();
    if (parse_standard_type() == ERROR)
    {
        // error("Standard type is not found in array_type\n");
    }
    return NOMAL;
}

int parse_subprogram_declaration()
{
    // subprogram_declaration ::= "procedure" NAME [formal_parameters] ";" [variable_declaration] compound_statement ";"

    // when call this function, token is "procedure"
    //  if(token != TPROCEDURE){
    //      error("Keyword 'procedure' is not found in subprogram_declaration\n");
    // }
    token = scan();
    if (token != TNAME)
    {
        error("Procedure_name is not found in subprogram_declaration\n");
    }
    token = scan();
    if (token == TLPAREN)
    { // it is ok if formal_parameters is not found
        if (parse_formal_parameters() == ERROR)
        {
            // error("Formal parameters is not found in subprogram_declaration\n");
        }
    }
    if (token != TSEMI)
    {
        error("';' is not found in subprogram_declaration\n");
    }
    token = scan();
    if (token == TVAR)
    { // it is ok if variable_declaration is not found
        if (parse_variable_declaration() == ERROR)
        {
            // error("Variable declaration is not found in subprogram_declaration\n");
        }
    }
    if (parse_compound_statement() == ERROR)
    {
        // error("Compound statement is not found in subprogram_declaration\n");
    }
    if (token != TSEMI)
    {
        error("';' is not found in subprogram_declaration\n");
    }
    token = scan();
    return NOMAL;
}

int parse_formal_parameters()
{
    // formal_parameters ::= "(" variable_names ":" type {";" variable_names ":" type} ")"

    // when call this function, token is "("
    //  if(token != TLPAREN){
    //      error("'(' is not found in formal_parameters\n");
    // }
    token = scan();
    if (parse_variable_names() == ERROR)
    {
        // error("Variable name is not found in in formal_parameters\n");
    }
    if (token != TCOLON)
    {
        error("':' is not found in formal_parameters\n");
    }
    token = scan();
    if (parse_type() == ERROR)
    {
        // error("Type is not found in in formal_parameters\n");
    }
    while (token == TSEMI)
    {
        token = scan();
        if (parse_variable_names() == ERROR)
        {
            // error("Variable name is not found in in formal_parameters\n");
        }
        if (token != TCOLON)
        {
            error("':' is not found in formal_parameters in in formal_parameters\n");
        }
        token = scan();
        if (parse_standard_type() == ERROR)
        {
            // error("Standard type is not found in formal_parameters\n");
        }
    }
    if (token != TRPAREN)
    {
        error("')' is not found in formal_parameters\n");
    }
    token = scan();
    return NOMAL;
}

int parse_compound_statement()
{
    // compound_statement ::= "begin" statement {";" statement} "end"
    if (token != TBEGIN)
    {
        error("Keyword 'begin' is not found\n");
    }
    token = scan();
    if (parse_statement() == ERROR)
    {
        // error("Statement is not found in compound_statement1\n");
    }
    while (token == TSEMI)
    {
        token = scan();
        if (parse_statement() == ERROR)
        {
            // error("Statement is not found in compound_statement2\n");
        }
    }
    if (token != TEND)
    {
        error("Keyword 'end' is not found in compound_statement\n");
    }
    token = scan();
    return NOMAL;
}

int parse_statement()
{
    /*
        statement ::= assignment_statement | condition_statement | iteration_statement |
                      exit_statement | call_statement | return_statement | input_statement|
                      output_statement | compound_statement | empty_statement
    */
    switch (token)
    {
    case TNAME:
        if (parse_assignment_statement() == ERROR)
        {
            // error("Assignment statement is not found in parse_statement\n");
        }
        break;
    case TIF:
        if (parse_condition_statement() == ERROR)
        {
            // error("Condition statement is not found in parse_statement\n");
        }
        break;
    case TWHILE:
        if (parse_iteration_statement() == ERROR)
        {
            // error("Iteration statement is not found in parse_statement\n");
        }
        break;
    case TBREAK:
        if (parse_exit_statement() == ERROR)
        {
            // error("Exit statement is not found in parse_statement\n");
        }
        break;
    case TCALL:
        if (parse_call_statement() == ERROR)
        {
            // error("Call statement is not found in parse_statement\n");
        }
        break;
    case TRETURN:
        if (parse_return_statement() == ERROR)
        {
            // error("Return statement is not found in parse_statement\n");
        }
        break;
    case TREAD:
    case TREADLN:
        if (parse_input_statement() == ERROR)
        {
            // error("Input statement is not found in parse_statement\n");
        }
        break;
    case TWRITE:
    case TWRITELN:
        if (parse_output_statement() == ERROR)
        {
            // error("Output statement is not found in parse_statement\n");
        }
        break;
    case TBEGIN:
        if (parse_compound_statement() == ERROR)
        {
            // error("Compound statement is not found in parse_statement\n");
        }
        break;
    default:
        parse_empty_statement();
    }
    return NOMAL;
}

int parse_condition_statement()
{
    // condition_statement ::= "if" expression "then" statement ["else" statement]

    // when call this function, token is "if"
    //  if(token != TIF){
    //      error("Keyword 'if' is not found in condition_statement\n");
    // }
    token = scan();
    if (parse_expression() == ERROR)
    {
        // error("Expression is not found in condition_statement\n");
    }
    if (token != TTHEN)
    {
        error("Keyword 'then' is not found in condition_statement\n");
    }
    token = scan();
    if (parse_statement() == ERROR)
    {
        // error("Statement is not found in condition_statement\n");
    }
    if (token == TELSE)
    { // it is ok if there is no else statement
        token = scan();
        if (token != TIF)
        {
            print_indent();
        }
        if (parse_statement() == ERROR)
        {
            // error("Statement is not found in condition_statement\n");
        }
    }
    return NOMAL;
}

int parse_iteration_statement()
{
    // iteration_statement ::= "while" expression "do" statement

    // when call this function, token is "while"
    //  if(token != TWHILE){
    //      error("Keyword 'while' is not found in iteration_statement\n");
    // }
    token = scan();
    if (parse_expression() == ERROR)
    {
        // error("Expression is not found in iteration_statement\n");
    }
    if (token != TDO)
    {
        error("Keyword 'do' is not found in iteration_statement\n");
    }
    token = scan();
    if (parse_statement() == ERROR)
    {
        // error("Statement is not found in iteration_statement\n");
    }
    return NOMAL;
}

int parse_exit_statement()
{
    // exit_statement ::= "break"

    // when call this function, token is "break"
    //  if(token != TBREAK){
    //      error("Keyword 'break' is not found in exit_statement\n");
    // }
    token = scan();
    return NOMAL;
}

int parse_call_statement()
{
    // call_statement ::= "call" NAME ["(" expressions ")"]

    // when call this function, token is "call"
    //  if(token != TCALL){
    //      error("Keyword 'call' is not found in call_statement\n");
    // }
    token = scan();
    if (token != TNAME)
    {
        error("Procedure name is not found in call_statement\n");
    }
    token = scan();
    if (token == TLPAREN)
    { // it is ok if there is no expression
        token = scan();
        if (parse_expressions() == ERROR)
        {
            // error("Expressions are not found in call_statement\n");
        }
        if (token != TRPAREN)
        {
            error("')' is not found in call_statement\n");
        }
        token = scan();
    }
    return NOMAL;
}

int parse_expressions()
{
    // expressions ::= expression {"," expression}
    if (parse_expression() == ERROR)
    {
        // error("Expression is not found in expressions\n");
    }
    while (token == TCOMMA)
    {
        token = scan();
        if (parse_expression() == ERROR)
        {
            // error("Expression is not found in expressions\n");
        }
    }
    return NOMAL;
}

int parse_return_statement()
{
    // return_statement ::= "return"

    // when call this function, token is "return"
    //  if(token != TRETURN){
    //      error("Keyword 'return' is not found in return_statement\n");
    // }
    token = scan();
    // return NOMAL;
}

int parse_assignment_statement()
{
    // assignment_statement ::= variable ":=" expression
    if (parse_variable() == ERROR)
    {
        // error("Variable name is not found in return_statement\n");
    }
    if (token != TASSIGN)
    {
        error("':=' is not found in return_statement\n");
    }
    token = scan();
    if (parse_expression() == ERROR)
    {
        // error("Expression is not found in return_statement\n");
    }
    return NOMAL;
}

int parse_variable()
{
    // variable = NAME ["[" expression "]"]
    if (token != TNAME)
    {
        error("Variable name is not found in variable\n");
    }
    token = scan();
    if (token == TLSQPAREN)
    { // it is ok if there is no [ expression ]
        token = scan();
        if (parse_expression() == ERROR)
        {
            // error("Expression is not found in variable\n");
        }
        if (token != TRSQPAREN)
        {
            error("']' is not found in variable\n");
        }
        token = scan();
    }
    return NOMAL;
}

int parse_expression()
{
    // expression ::= simple_expression {relational_operator simple_expression}
    if (parse_simple_expression() == ERROR)
    {
        // error("Simple expression is not found in expression\n");
    }
    if (token == TEQUAL || token == TNOTEQ || token == TLE || token == TLEEQ || token == TGR || token == TGREQ)
    {
        token = scan();
        if (parse_simple_expression() == ERROR)
        {
            // error("Simple expression is not found in expression\n");
        }
    }

    return NOMAL;
}

int parse_simple_expression()
{
    // simple_expression ::= ["+"|"-"] term {adding_operator term}
    if (token == TPLUS || token == TMINUS)
    { // it is ok if there is no sign
        token = scan();
    }
    if (parse_term() == ERROR)
    {
        // error("Term is not found in simple_expression\n");
    }
    if (token == TPLUS || token == TMINUS || token == TOR)
    {
        while (token == TPLUS || token == TMINUS || token == TOR)
        {
            token = scan();
            if (parse_term() == ERROR)
            {
                // error("Term is not found in simple_expression\n");
            }
        }
    }
    return NOMAL;
}

int parse_term()
{
    // term ::= factor {multiplying_operator factor}
    if (parse_factor() == ERROR)
    {
        // error("Factor is not found in term\n");
        // return(ERROR);
    }

    while (token == TSTAR || token == TAND || token == TDIV)
    {
        token = scan();
        if (parse_factor() == ERROR)
        {
            // error("Factor is not found in term\n");
        }
    }
    return NOMAL;
}

int parse_factor()
{
    // factor ::= variable | constant | "(" expression ")" | "not" factor | standard_type "(" expression ")"
    if (token == TNAME)
    {
        if (parse_variable() == ERROR)
        {
            // error("Variable is not found in factor\n");
        }
    }
    else if (token == TNUMBER || token == TSTRING || token == TFALSE || token == TTRUE)
    {
        token = scan();
    }
    else if (token == TLPAREN)
    {
        token = scan();
        if (parse_expression() == ERROR)
        {
            // error("Expression is not found in factor\n");
        }
        if (token != TRPAREN)
        {
            error("')' is not found in factor\n");
        }
        token = scan();
    }
    else if (token == TNOT)
    {
        token = scan();
        if (parse_factor() == ERROR)
        {
            // error("Factor is not found in factor\n");
        }
    }
    else if (token == TINTEGER || token == TBOOLEAN || token == TCHAR)
    {
        token = scan();
        if (token != TLPAREN)
        {
            error("'(' is not found in factor\n");
        }
        token = scan();
        if (parse_expression() == ERROR)
        {
            // error("Expression is not found in factor\n");
        }
        if (token != TRPAREN)
        {
            error("')' is not found in factor\n");
        }
        token = scan();
    }
    else
    {
        error("Factor is not found in factor\n");
    }
    return NOMAL;
}

/***

// instead of parse_standard_type, NUMBER, STRING, FALSE, TRUE are used
int parse_constant(){
    // constant ::= "NUMBER" | "false" | "true" | "STRING"
    if(token == TNUMBER || token == TSTRING || token == TFALSE || token == TTRUE){
        token = scan();
        return NOMAL;
    }
    error("Constant is not found in constant\n");
}

// instead of parse_standard_type, INTEGER, BOOLEAN, CHAR are used
int parse_multiplicative_operator(){
    // multiplicative_operator ::= "*" | "div" | "and"
    if(token == TSTAR || token == TDIV || token == TAND){
        token = scan();
        return NOMAL;
    }
    error("Multiplicative operator is not found in multiplicative_operator\n");
}

// instead of parse_standard_type, TPLUS, TMINUS, TOR are used
int parse_additive_operator(){
    // adding_operator ::= "+" | "-" | "or"
    if(token == TPLUS || token == TMINUS || token == TOR){
        token = scan();
        return NOMAL;
    }
    error("Additive operator is not found in additive_operator\n");
    return ERROR;
}

// instead of parse_standard_type, TEQUAL, TNOTEQ, TLE, TLEEQ, TGR, TGREQ are used
int parse_relational_operator(){
    // relational_operator ::= "=" | "<>" | "<" | "<=" | ">" | ">="
    if(token == TEQUAL || token == TNOTEQ || token == TLE || token == TLEEQ || token == TGR || token == TGREQ){
        token = scan();
        return NOMAL;
    }
    error("Relational operator is not found in relational_operator\n");
    return ERROR;
}

***/

int parse_input_statement()
{
    // input_statement ::= ("read" | "readln") ["(" variable {"," variable} ")"]

    // when call this function, token is already "read" or "readln"
    // if(token != TREAD && token != TREADLN){
    //     error("Keyword 'read' or 'readln' is not found in input_statement\n");
    // }
    token = scan();
    if (token == TLPAREN)
    { // it is ok if there is no variable
        token = scan();
        if (parse_variable() == ERROR)
        {
            // error("Variable is not found in input_statement\n");
        }
        while (token == TCOMMA)
        {
            token = scan();
            if (parse_variable() == ERROR)
            {
                // error("Variable is not found in input_statement\n");
            }
        }
        if (token != TRPAREN)
        {
            error("')' is not found in input_statement\n");
        }
        token = scan();
    }
    return NOMAL;
}

int parse_output_statement()
{
    // output_statement ::= ("write" | "writeln") ["(" output_format {"," output_format} ")"]

    // when call this function, token is TWRITE or TWRITELN
    // if(token != TWRITE && token != TWRITELN){
    //     error("Keyword 'write' or 'writeln' is not found in output_statement\n");
    // }
    token = scan();
    if (token == TLPAREN)
    { // it is ok if there is no output_format
        token = scan();
        if (parse_output_format() == ERROR)
        {
            // error("Output format is not found in output_statement\n");
        }
        while (token == TCOMMA)
        {
            token = scan();
            if (parse_output_format() == ERROR)
            {
                // error("Output format is not found in output_statement\n");
            }
        }
        if (token != TRPAREN)
        {
            error("')' is not found in output_statement\n");
        }
        token = scan();
    }
    return NOMAL;
}

int parse_output_format()
{
    // output_format ::= expression [":" "NUMBER"] | "STRING"
    if (token == TSTRING)
    {
        token = scan();
    }
    else
    {
        if (parse_expression() == ERROR)
        {
            // error("Expression is not found in output_format\n");
        }
        if (token == TCOLON)
        { // it is ok if there is no number
            token = scan();
            if (token != TNUMBER)
            {
                error("Number is not found in output_format\n");
            }
            token = scan();
        }
    }
    return NOMAL;
}

int parse_empty_statement()
{
    // empty_statement ::= ε
    return NOMAL;
}