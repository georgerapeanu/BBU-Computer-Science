%token<row> NOT
%token<row> PLUS
%token<row> MINUS
%token<row> MULT
%token<row> DIV
%token<row> MOD
%token<row> EQUAL
%token<row> NOT_EQUAL
%token<row> LT
%token<row> LE
%token<row> GT
%token<row> GE
%token<row> ASSIGNMENT
%token<row> AND
%token<row> OR
%token<row> L_BRACKET
%token<row> R_BRACKET
%token<row> L_SQUARE_BRACKET
%token<row> R_SQUARE_BRACKET
%token<row> L_PARANTHESIS
%token<row> R_PARANTHESIS
%token<row> SEMICOLON
%token<row> COMMA
%token<row> APOSTROPHE
%token<row> COLON
%token<row> PERIOD
%token<row> LET
%token<row> IF
%token<row> ELSE
%token<row> WHILE
%token<row> PRINT
%token<row> READ_I32
%token<row> READ_U32
%token<row> READ_STR
%token<row> READ_BOOL
%token<row> READ_F32
%token<row> I32
%token<row> U32
%token<row> STR
%token<row> BOOL
%token<row> F32
%token<row> ARRAY
%token<row> TRUE
%token<row> FALSE
%token<row> IDENTIFIER 
%token<row> CONSTANT

%{
  #include "include.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  static struct row_entry* cons(const char* name, struct row_entry* first_child) {
    struct row_entry* answer = malloc(sizeof(struct row_entry));
    answer->name = strdup(name);
    answer->first_child = first_child;
    answer->next_sibling = NULL;
    return answer;
  }

  static void display(struct row_entry* node, int count_tabs) {
    if(node == NULL) return;
    for(int i = 0; i < count_tabs; i++) {
      printf("\t");
    }
    printf("%s\n", node->name);
    display(node->first_child, count_tabs + 1);
    display(node->next_sibling, count_tabs);
  }
  static void free_row_entry(struct row_entry* node) {
    if(node == NULL) return;
    free_row_entry(node->first_child);
    free_row_entry(node->next_sibling);
    free(node->name);
    free(node);
  }
  extern int yylex();
  extern int yylex_destroy();
%}

%union {
  struct row_entry* row;  
}

%type<row> program
%type<row> statement
%type<row> type
%type<row> decl_statement
%type<row> assignment_statement
%type<row> input
%type<row> output
%type<row> output_expression
%type<row> loop
%type<row> conditional
%type<row> expression
%type<row> term
%type<row> operator

%%
accept: program                                   { display($1, 0); free_row_entry($1); }
program:                                          { $$ = cons("program", NULL); } 
       | program statement                        { $$ = cons("program", $1); $1->next_sibling = $2; }
       ;

statement: SEMICOLON                              { $$ = cons("statement", $1); }
         | decl_statement SEMICOLON               { $$ = cons("statement", $1); $1->next_sibling = $2; }  
         | assignment_statement SEMICOLON         { $$ = cons("statement", $1); $1->next_sibling = $2; } 
         | input SEMICOLON                        { $$ = cons("statement", $1); $1->next_sibling = $2; } 
         | output SEMICOLON                       { $$ = cons("statement", $1); $1->next_sibling = $2; } 
         | conditional                            { $$ = cons("statement", $1); }  
         | loop                                   { $$ = cons("statement", $1); } 
         ;

type: I32                                         { $$ = cons("type", $1); } 
    | U32                                         { $$ = cons("type", $1); } 
    | STR                                         { $$ = cons("type", $1); } 
    | BOOL                                        { $$ = cons("type", $1); }  
    | F32                                         { $$ = cons("type", $1); } 
    | ARRAY L_SQUARE_BRACKET type SEMICOLON expression R_SQUARE_BRACKET { $$ = cons("type", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; $5->next_sibling = $6; } 
    ;


decl_statement: LET IDENTIFIER COLON type               { $$ = cons("decl_statement", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; }
              ;

assignment_statement: IDENTIFIER ASSIGNMENT expression  { $$ = cons("assignment_statement", $1); $1->next_sibling = $2; $2->next_sibling = $3; }
                    ; 
input: IDENTIFIER ASSIGNMENT READ_I32 L_PARANTHESIS R_PARANTHESIS             { $$ = cons("input", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; }
     | IDENTIFIER ASSIGNMENT READ_U32 L_PARANTHESIS R_PARANTHESIS             { $$ = cons("input", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; }
     | IDENTIFIER ASSIGNMENT READ_STR L_PARANTHESIS R_PARANTHESIS             { $$ = cons("input", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; }
     | IDENTIFIER ASSIGNMENT READ_BOOL L_PARANTHESIS R_PARANTHESIS            { $$ = cons("input", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; }
     | IDENTIFIER ASSIGNMENT READ_F32 L_PARANTHESIS R_PARANTHESIS             { $$ = cons("input", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; }
     ;

output: PRINT L_PARANTHESIS output_expression R_PARANTHESIS   { $$ = cons("output", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; }
      ;

output_expression: expression                                 { $$ = cons("output_expression", $1); }
                 | output_expression COMMA expression         { $$ = cons("output_expression", $1); $1->next_sibling = $2; $2->next_sibling = $3; }
                 ;

conditional: IF expression L_BRACKET program R_BRACKET        { $$ = cons("conditional", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; }
           | IF expression L_BRACKET program R_BRACKET ELSE L_BRACKET program R_BRACKET { $$ = cons("conditional", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; $5->next_sibling = $6; $6->next_sibling = $7; $7->next_sibling = $8; $8->next_sibling = $9; }
           ;

loop: WHILE expression L_BRACKET program R_BRACKET  { $$ = cons("loop", $1); $1->next_sibling = $2; $2->next_sibling = $3; $3->next_sibling = $4; $4->next_sibling = $5; }
    ;

operator: NOT               { $$ = cons("operator", $1); } 
        | PLUS              { $$ = cons("operator", $1); } 
        | MINUS             { $$ = cons("operator", $1); }
        | MULT              { $$ = cons("operator", $1); }
        | DIV               { $$ = cons("operator", $1); }
        | MOD               { $$ = cons("operator", $1); }
        | EQUAL             { $$ = cons("operator", $1); }
        | NOT_EQUAL         { $$ = cons("operator", $1); }
        | LT                { $$ = cons("operator", $1); }
        | LE                { $$ = cons("operator", $1); }
        | GT                { $$ = cons("operator", $1); }
        | GE                { $$ = cons("operator", $1); }
        | AND               { $$ = cons("operator", $1); }
        | OR                { $$ = cons("operator", $1); }
        ;

expression: NOT expression                { $$ = cons("expression", $1); $1->next_sibling = $2; }
          | term operator expression      { $$ = cons("expression", $1); $1->next_sibling = $2; $2->next_sibling = $3;}
          | term                          { $$ = cons("expression", $1); }
          | MINUS expression              { $$ = cons("expression", $1); $1->next_sibling = $2; }
          ;

term: IDENTIFIER                                    { $$ = cons("term", $1); }
    | CONSTANT                                      { $$ = cons("term", $1); } 
    | TRUE                                          { $$ = cons("term", $1); } 
    | FALSE                                         { $$ = cons("term", $1); } 
    | L_PARANTHESIS expression R_PARANTHESIS        { $$ = cons("term", $1); $1->next_sibling = $2; $2->next_sibling = $3; }
    ;
%%

int yyerror(char *s) {
  fprintf(stderr, "Error: %s\n", s); 
  return 0; 
}

int main() {
  yyparse();
  yylex_destroy();
  return 0;
}
