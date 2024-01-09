lex: yacc 
	flex lang.lxi

yacc: 
	bison -d lang.y

build: lex yacc 
	gcc -g lex.yy.c lang.tab.c -ll

clean: 
	rm a.out
