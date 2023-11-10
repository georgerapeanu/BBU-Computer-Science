Statement: Implement a scanner (lexical analyzer): Implement the scanning algorithm and use ST from lab 2 for the symbol table.

Input: Programs p1/p2/p3/p1err and token.in (see Lab 1a)

Output: PIF.out, ST.out, message “lexically correct” or “lexical error + location”

Deliverables: input, output, source code, documentation

Details:

    ST.out should give information about the data structure used in representation

    If there exists an error the program should give a description and the location (line and token)


 Documentation:

 This project contains 2 files. `symbol_table.rs`, which is the one from lab2 with no changes, and `main.rs`.
 In `main.rs`, regexes are defined to match constants and identifiers. They are matched together with a separator following them(or end-of-line). This is done in order to correctly match the whole of a token. Splitting by spaces is not correct, since strings can contains spaces inside of them.

 So the code works as follows: first, the input string is split by newlines. Afterwards, comments are replaced by empty strings so they are ignored. Afterwards, for each line, we process the string character by character. Whitespace is skipped. After that, we try to match against a reserved word. If there is a match, we take the token and continue. Otherwise, we match the identifier, and search for it in the symbol table. If it doesn't exist, we create a new entry for it.
