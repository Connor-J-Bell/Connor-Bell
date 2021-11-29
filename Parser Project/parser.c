#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <malloc.h>

//If non-0, enable all of the printf statements
#define PRINT 1
//#define TESTLEX 1
//#define TESTSYNTAX 1
//#define LINES 1
//#define LEXLINES 1
//#define ERRORS 1

#define MAX_LEX_LENGTH 100

#define PROG 0
#define START 1
#define FINISH 2
#define LOAD 3
#define SAVE 4
#define IF 5
#define THEN 6
#define ELSE 7
#define WHILE 8
#define DO 9
#define SEMICOLON 10
#define ASSIGN_OP 11
#define LEFT_PAREN 12
#define RIGHT_PAREN 13
#define COMMA 14
#define ADD_OP 15 //When looking for SIGN, ADD_OP should work
#define SIGN 15 
#define MULT_OP 16
#define REL_OP_MULT 17
#define REL_OP 18
#define INT_LITERAL 19
#define PROG_NAME 20 //When looking for a VARIABLE, getting PROG_NAME should work too
#define VARIABLE 21
#define COMMENT 22
#define ENDFILE -1

//Number of Regex patterns:
#define REGEX_VAL 23

/* Global Variables */
char *program; //array that holds all chars from file
char lexeme[MAX_LEX_LENGTH]; //array that holds the current lexeme
int token; //tokens represented by ints, correlating to a regex in regex_patterns
int lineNumber; //holds which line an error is thrown on
int errorNum; //Number of errors in parsed file

char regex_patterns[REGEX_VAL][30] = {
	"^prog",
	"^start",
	"^finish",
	"^load",
	"^save",
	"^if",
	"^then",
	"^else",
	"^while",
	"^do",
	"^;",
	"^:=",
	"^\\(",
	"^\\)",
	"^,",
	"^[+|-]",
	"^[*|/]",
	"^[<>|<=|>=]",
	"^[=|<|>]",
	"^[0-9][0-9]*",
	"^[A-Z][A-Za-z0-9]*",
	"^[A-Za-z][A-Za-z0-9]*",
	"^#"};

/* match[]- metadata for the match, holds start and end positions for lexeme,
	the struct regmatch_t holds the values, gotten with match->rm_so and 
	match->rm_eo respectively */
regmatch_t match[1];
regex_t *regex; //pointer to compiled regular expressions

/* Regex Function Declarations */
int checkformatch(char *value, regex_t *regex);
void start_regex(char *argv);
int setup_regex(regex_t *regex, char *regex_pattern);
char *lineBreak(char *value);
char *trim(char *value);

/* Syntax Analyzer Function Declarations, subroutine for each grammar rule */
void lex();
void program_grammar();
void compound_stmt();
void stmt();
void simple_stmt();
void assign_stmt();
void load_stmt();
void save_stmt();
void structured_stmt();
void if_stmt();
void while_stmt();
void expr();
void simple_expr();
void term();
void factor();

//set up the regex and then start the analyzer
int main(int argc, char **argv) {
#ifdef PRINT
	printf("------------------------------\n");
	printf("Starting Parser:\n");
#endif
	start_regex(*(argv + 1)); //compile all the regular expressions
	lineNumber = 1; //program starts on the first line (not line '0')

	printf("Starting Syntax analyzer:\n");
	lex();
	program_grammar();
}

void lex() {
#ifdef TESTLEX
	printf("Calling lex()------------------\n");
#endif
	trim(program); //cut out the whitespace to the next char
	int i;
	int ifmatch;
#ifdef TESTLEX
	printf("Reading Program-'%s'\n", program);
#endif
	if (*program == '\0'){
#ifdef TESTSYNTAX
		printf("reached end of file with lex()\n");
#endif
		token = ENDFILE;
		return;
	}
	for (i = 0; i < REGEX_VAL; i++) {
		/* call checkformatch() in the loop, until a match is found */
		ifmatch = checkformatch(program, regex + i);
		/* ifmatch is 0 if there was a match, or 1 if not */
		if (!ifmatch && i == COMMENT) {
		//a comment was matched
#ifdef TESTLEX
			printf("Comment found and removed\n");
#endif
			lineBreak(program); // both of these return something and I'm not doing anything with them
			i = -1;
		} else if (!ifmatch) {
		//a lexeme was matched
			
#ifdef LEXLINES
			printf("Lexeme copied from file\n");
#endif
			/* copy the matched string into lexeme from program (end of match @ match->rm_eo) */
			strncpy(lexeme, program, match->rm_eo);
			/* add the null terminator to the lexeme */
			*(lexeme + match->rm_eo) = '\0'; 
#ifdef TESTSYNTAX
			printf("Next Lexeme: '%s' on line %d\n", lexeme, lineNumber);
#endif
			
#ifdef LEXLINES
			printf("Taking out: '%s', length: %d\n", lexeme, match->rm_eo);
			printf("program:\n%s\n", program);
			printf("program + match->rm_eo:\n%s\n", program + match->rm_eo);
			printf("strcpy(program, program + match->rm_eo); runs to shorten the file\n");
#endif

			/* shorten the program */
			memmove(program, program + match->rm_eo, strlen(program) - (match->rm_eo - 1));
			/* int i correlates to which token the lexeme is, tokens as #define statements 	
			matched with regexs in regex_patterms[i][] */
			token = i;
#ifdef TESTLEX
			
			printf("---------Token Found---------\n");
#endif
			break;
		} else if (ifmatch && i == COMMENT) {
		//an illegal character was found
			//there were not matches, at the end of the list => illegal character
			//send an error message for an illegal character
#ifdef TESTLEX
			printf("Illegal char found and removed\n");
#endif		
#ifdef LEXLINES
			printf("Removing illegal char with strcpy(program, program + 1);\n");
#endif
			printf("Error: illegal character found on line: %d\n", lineNumber);
			errorNum++;
			memmove(program, program + 1, strlen(program)); //cut off the character
			i = -1;
		}
	}
}

/* Subroutine Functions */
/* <program>::= prog <progname> <compound stmt> */
void program_grammar() {
#ifdef TESTSYNTAX
	printf("In program_grammar()\n");
#endif
	while (token != PROG && token != EOF) { //loop until either 'prog' or the end of the file is found, throwing an error every time prog isnt found
		printf("Error: '%s' found at line %d, expected token: 'prog'\n", lexeme, lineNumber);
		errorNum++;
		lex();
	}
	if (token == PROG) {
		lex();
		if (token == PROG_NAME){
			lex();
			if (token == START) {
				lex();
				compound_stmt();
			} else {
				printf("Error: '%s' found at line %d, expected token: 'start'\n", lexeme, lineNumber);
				errorNum++;
				compound_stmt(); //the lexeme should stay what it was if start wasn't found
			}
		} else {
			printf("Error: '%s' found at line %d, expected token: 'progname'\n", lexeme, lineNumber);
			errorNum++;
			lex();
			if (token == START) {
				lex();
				compound_stmt();
			} else {
				printf("Error: '%s' found at line %d, expected token: 'start'\n", lexeme, lineNumber);
				errorNum++;
				compound_stmt();//the lexeme should stay what it was if start wasn't found
			} 
		}
		printf("File compiled with %d error(s).\n", errorNum);
	} else {
		printf("Error: token 'prog' never found\n");
	}
#ifdef TESTSYNTAX
	printf("Exiting program_grammar()\n");
#endif
}

/* <compount stmt>::= start <stmt> {;<stmt>} finish */
//There is no semicolon before finish
//compound_stmt() is only called when token == START -> tested in program_grammar()
void compound_stmt() {
#ifdef TESTSYNTAX
	printf("In compound_stmt()\n");
#endif
	stmt();
	while (token == SEMICOLON) { //this is the only time lex() should ever be called when token = SEMICOLON
		lex();
		stmt();
	} if (token == FINISH) {
		lex();
		/* lexeme should now be at the end of the file if there are no errors after 'finish' */
	} else {
		printf("Error: '%s' found at line %d, missing token: 'finish', or incorrect semicolon placement\n", lexeme, lineNumber);
		errorNum++;
		lex();
	}
	while (token != EOF) {
	//Run through the file until you find EOF, throw an error every time you don't find one
		printf("Error: code after ending token: '%s' on line %d\n", lexeme, lineNumber);
		errorNum++;
		lex();
	}
#ifdef TESTSYNTAX
	printf("Exiting compound_stmt()\n");
#endif
}

/* <stmt>::= <simple stmt> | <structured stmt> */
void stmt() {
#ifdef TESTSYNTAX
	printf("In stmt()\n");
#endif
	/* call simple_stmt() or structured_stmt() */
	if (token == LOAD || token == SAVE || token == PROG_NAME || token == VARIABLE) {
		simple_stmt();
	} else if (token == IF || token == WHILE || token == START) {
		structured_stmt();
	} else {
		printf("Error: '%s' found at line: %d, expected legal statement\n", lexeme, lineNumber);
		errorNum++;
		while (token != EOF) { //loop to the end of the file or until a semicolon or 'finish' is found-> designating the next legal statement
			lex();
			if (token == FINISH) {
				break;
			} else if (token == SEMICOLON) {
				break;
			}
		}
	}
#ifdef TESTSYNTAX
	printf("Exiting stmt()\n"); //the token should always be either ';' or 'finish' at this point
#endif
}

/* <simple stmt>::= <assisgnment stmt> | <load stmt> | <save stmt> */
void simple_stmt() {
#ifdef TESTSYNTAX
	printf("In simple_stmt()\n");
#endif
	if (token == LOAD) {
		lex();
		load_stmt();
	} else if (token == SAVE) {
		lex();
		save_stmt();
	} else {
		lex();
		assign_stmt();
	}
#ifdef TESTSYNTAX
	printf("Exiting simple_stmt()\n");
#endif
}

/* <assignment stmt>::= <variable> := <expression> */
void assign_stmt() {
#ifdef TESTSYNTAX
	printf("In assign_stmt()\n");
#endif
	if (token == ASSIGN_OP) {
		lex();
		expr();
	} else {
		printf("Error: '%s' found at line %d, expected token: ':='\n", lexeme, lineNumber);
		errorNum++;
		lex();
		if(token != SEMICOLON) { //if just the ':=' was missing, the next lexeme would be ';'
			expr();
		}
	}
#ifdef TESTSYNTAX
	printf("Exiting assign_stmt()\n");
#endif
}

/* <load stmt>::= load (<variable> {, <variable>}) */
void load_stmt() {
#ifdef TESTSYNTAX
	printf("In load_stmt()\n");
#endif
	if(token == LEFT_PAREN) {
		lex();
		if (token == PROG_NAME || token == VARIABLE) {
			lex();
			while (token == COMMA) {
				lex();
				if (token == PROG_NAME || token == VARIABLE) {
					lex();
				} else {
					printf("Error: '%s' found at line %d, expected token: 'VARIABLE'\n", lexeme, lineNumber);
					errorNum++;
				}
			}
		} else {
			printf("Error: '%s' found at line %d, expected token: 'VARIABLE'\n", lexeme, lineNumber);
			errorNum++;
		}
	} else {
		printf("Error: '%s' found at line %d, expected token: '('\n", lexeme, lineNumber);
		errorNum++;
	}
	while (token != RIGHT_PAREN && token != SEMICOLON && token != FINISH) { //after the load keyword, loop until ')' 'finish' or ';' is found
		lex();
	}
	if (token == RIGHT_PAREN) {
		lex();
	} else {
		printf("Error: '%s' found at line %d, expected token: ')'\n", lexeme, lineNumber);
		errorNum++;
	}
#ifdef TESTSYNTAX
	printf("Exiting load_stmt()\n");
#endif
}

/* <save stmt>::= save (<expression> {, <expression> }) */
void save_stmt() {
#ifdef TESTSYNTAX
	printf("In save_stmt()\n");
#endif
	if (token == LEFT_PAREN) {
		lex();
		expr();
		while (token == COMMA) {
			lex();
			if (token != VARIABLE && token != PROG_NAME && token != INT_LITERAL && token != LEFT_PAREN && token != SIGN) {
				printf("Error in save statement at line %d, replace %s with legal expression\n", lineNumber, lexeme);
				errorNum++;
			} else {
				expr();
			}
		}
	} else {
		printf("Error: '%s' found at line %d, expected token: '('\n", lexeme, lineNumber);
		errorNum++;
	}
	while (token != RIGHT_PAREN && token != SEMICOLON && token != FINISH) {
		lex();
	}
	if (token == RIGHT_PAREN) {
		lex();
	} else {
		printf("Error: '%s' found at line %d, expected token: ')'\n", lexeme, lineNumber);
		errorNum++;
	}
#ifdef TESTSYNTAX
	printf("Exiting save_stmt\n");
#endif
}

/* <structured stmt>::= <compound stmt> | <if stmt> | <while stmt> */
void structured_stmt() {
#ifdef TESTSYNTAX
	printf("In structured_stmt()\n");
#endif
	//call compound_stmt() or if_stmt() or while_stmt()
	if (token == WHILE) {
		while_stmt();
	} else if (token == IF) {
		if_stmt();
	} else if (token == START) {
		compound_stmt();
	}
#ifdef TESTSYNTAX
	printf("Exiting structured_stmt()\n");
#endif
}

/* <if stmt>::= if <expression> then <stmt> | if <expression> then <stmt> else <stmt> */
void if_stmt() {
#ifdef TESTSYNTAX
	printf("In if_stmt()\n");
#endif
	lex();
	expr();
	if (token == THEN) {
		lex();
		stmt();
		if (token == ELSE) {
			lex();
			stmt();
		}
	} else {
		printf("Error: '%s' found at line %d, expected token: 'then'\n", lexeme, lineNumber);
		errorNum++;
		lex();
		stmt();
		if (token == ELSE) {
			lex();
			stmt();
		}
	}
#ifdef TESTSYNTAX
	printf("Exiting if_stmt()\n");
#endif
}

/* <while stmt>::= while <expression> do <stmt> */
void while_stmt() {
#ifdef TESTSYNTAX
	printf("In while_stmt()\n");
#endif
	lex();
	expr();
	if (token == DO) {
		lex();
		stmt();
	} else {
		printf("Error: %s found at line %d, expected token: 'do'\n", lexeme, lineNumber);
		errorNum++;
		lex();
		stmt();
	}
#ifdef TESTSYNTAX
	printf("Exiting while_stmt()\n");
#endif
}

/* <expression>::= <simple expr> | <simple expr> <relational_operator> <simple expr> */
void expr() {
#ifdef TESTSYNTAX
	printf("In expr()\n");
#endif
	simple_expr();
	if (token == REL_OP || token == REL_OP_MULT) {
		lex();
		simple_expr();
	}
#ifdef TESTSYNTAX
	printf("Exiting expr()\n");
#endif
}

/* <simple expr>::= [<sign>] <term> { <adding_operator> <term> } */
void simple_expr() {
#ifdef TESTSYNTAX
	printf("In simple_expr()\n");
#endif
	if (token == SIGN) {
		lex();
	}
	term();
	while (token == ADD_OP) {
		lex();
		term();
	}
	//Error messages will come from->term()->factor()
#ifdef TESTSYNTAX
	printf("Exiting simple_expr()\n");
#endif
}

/* <term>::= <factor> { <multiplying_operator> <factor> } */
void term() {
#ifdef TESTSYNTAX
	printf("In term()\n");
#endif
	factor();
	if (token == MULT_OP) {
		lex();
		factor();
	}
#ifdef TESTSYNTAX
	printf("Exiting term()\n");
#endif
}

/* <factor>::= <variable> | <int_literal> | (<expression>) */
void factor() {
#ifdef TESTSYNTAX
	printf("In factor()\n");
#endif
	if (token == LEFT_PAREN) {
		lex();
		expr();
		while (token != RIGHT_PAREN && token != SEMICOLON && token != FINISH) {
			lex();
		}
		if (token == RIGHT_PAREN) {
			lex();
		} else {
			printf("Error: '%s' found at line %d, expected token: ')'\n", lexeme, lineNumber);
			errorNum++;
		}
	} else {
		if (token == VARIABLE || token == PROG_NAME || token == INT_LITERAL) {
			lex();
		} else {
			printf("Error: '%s' found at line %d, expected token: 'VARIABLE' or 'INT_LITERAL'\n", lexeme, lineNumber);
			errorNum++;
			lex();
		}
	}
#ifdef TESTSYNTAX
	printf("Exiting factor()\n");
#endif
}

/* Regular Expression Functions */
void start_regex(char *main_arg) {
	regex = (regex_t *)malloc(REGEX_VAL*sizeof(regex_t));
	int i;
	int test;
	for (i = 0; i < REGEX_VAL; i++) {	
		test = setup_regex(regex + i, regex_patterns[i]);
		if (test != 0)
			printf("Error compiling regex: %s\n", regex_patterns[i]);
	}

#ifdef PRINT
	printf("Regexs compiled\n");
	printf("File: %s\n", main_arg);
#endif
	
	FILE *data;
	data = fopen((main_arg), "r");
	if(data==NULL) {
		printf("File could not be opened\n");
	}

	int count;
	char ch;
	count = 0;
	while((ch=fgetc(data))!=EOF) {
		count++;
		// find # of chars in data
	}
	
	/* close and reopen to reset data */
	fclose(data);
	data = fopen((main_arg), "r");

	/* use malloc to allocate an array of that length + 1 */
	program = (char *)malloc((count + 1)*sizeof(char));

	/* read file into allocated memory */
	i = 0;
	while ((program[i]=fgetc(data)) != EOF) {
		i++;
	}
	program[i] = '\0';
	/* close file */
	fclose(data);
#ifdef TESTLEX
	printf("Exiting start_regex()\n");
#endif
}

/* Compile the regular expression. Return the compilation result code */
int setup_regex(regex_t *regex, char *regex_pattern) {
	int return_value;
	return_value = regcomp(regex, regex_pattern, REG_EXTENDED);
	if (return_value) {
		printf("Error: Could not compile regex pattern: %s\n", regex_pattern);
	}
	return return_value;
}

/* Check a string to see if the regular expression matches
any portion of it. Only the first (left-most) match is reported.
Takes the character array 'value' -> the text being checked.
Takes the regex_t *regex -> the regular expression being checked */
int checkformatch(char *value, regex_t *regex) {
	int return_value = regexec(regex, value, 1, match, 0);
	/* return_value is either 1 or 0 base on whether there was a match or not respectively */
	return return_value;
}

/* Removes chars until it hits '\n' for when comments are found */
char *lineBreak(char *value) {
#ifdef LEXLINES
	printf("lineBreak() called\n");
#endif
#ifdef LINES
	printf("Removing comment (lineBreak()) on line: %d\n", lineNumber);
#endif
	memmove(value, value + 1, strlen(value)); //skips '#'
	while (*value != '\n') {
		memmove(value, value + 1, strlen(value));
	}
	memmove(value, value + 1, strlen(value));
	++lineNumber;
#ifdef LINES
	printf("(lineBreak()) Incremented to line: %d\n", lineNumber);
	printf("=-=-=-=-=-=-=-=-=-=-\n");
#endif
	return value;
}

/* Removes whitespace */
char *trim(char *value) {
#ifdef LEXLINES
	printf("trim() called\n");
#endif
#ifdef LINES
	printf("value in trim() before cut:\n%s\n", value);
#endif
	while (isspace(*value)) {
		if (*value == '\n'){
			++lineNumber;
#ifdef LINES
			printf("Incremented lineNumber (trim())\n"); 
			/* Error: the lineNumber is being incremented before the next token is found, 
			the last token on the line is thought of as on the next line. */
#endif
		}
		memmove(value, value + 1, strlen(value));
	}
#ifdef LINES
	printf("(trim())at line: %d, with lexeme: %s\n", lineNumber, lexeme);
	printf("value in trim() after cut:\n%s\n", value);
	printf("=-=-=-=-=-=-=-=-=-=-\n");
#endif
	return value;
}
