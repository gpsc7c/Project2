Invoked with frontEnd [file]
Author: Gregory Shelton
Started (DD/MM/YYYY): 12/03/2024
CLASS:   Code Translation
PROFESSOR: Mark Hauschild
PROJECT: Program Translation Project 2 parser
PURPOSE: Create a parser using the scanner from previous project designed to be used in a compiler
HELP:	 Command is -h, or putting in more (or less)  information than is necessary.

COMPILATION METHOD: Makefile
	 Compile with make, remove compiled files with make clean
	 invoke with "./scanner [filename]"
FILES:	 
	frontEnd.c: The file the program starts execution in.
	Makefile:   The make file.
	langscan.c: Completed functions for use by scanner.c includes FSA table
		    and several lengthy and reused functions.
	langscan.h: Function definitions for langscan.c made to improve make 
		    behavior.
	scanner.c:  Scanner lookahed, filter, driver functions.
	scanner.h:  Scanner function definitions.
	ttoken.h:   Definition of token struct, includes enumerations of 
		    several key variable sets.
	node.h:     Definition of node struct for the parse tree, and necessary
		    substructs.
	tree.h:     Definitions of functions for loading things onto the parse
		    tree, printing it, and deleting it
	parser.h:   Function definitions for parser.
	parser.c:   Actual parser, BNF structure, and error handling.
	p2t001:     Test for most basic possible program
	p2t002:     Test for var declaration and cout, which is more complex 
		    than cin.
	p2t003:     Test for a more complex program w/ jumps, loops, and a func.
	p2t004:     Test for expression variety.
	p2t005:     Test for deeper loops/statement connections. 
	p2t006+:    Test for errors.
	


SCANNER INFORMATION

Option 3
langscan.h contains the FSA table
scanner.h function FSADriver is the scanner, scanner.h function filter is the filter that goes over the scanner.
filter requires row and column be passed in as pointers to integers
scanner.h function testScan is the scan tester
An Excel spreadsheet version of the FSA table can be found in FSAChart.xlsx, 
but would need to be removed from the server to be checked.

Author: Gregory Shelton
Started (DD/MM/YYYY): 13/02/2024
CLASS:   Code Translation
PROFESSOR: Mark Hauschild
PROJECT: Program Translation Project 1 Scanner
PURPOSE: Create a scanner with lookahead designed to be used in a compiler
HELP:	 Command is -h, or putting in more (or less)  information than is necessary.

COMPILATION METHOD: Makefile
	 Compile with make, remove compiled files with make clean
	 invoke with "./scanner [filename]"
FILES:	 
	 scanner.c is the location of main, arg intake, and help function
	 scanner.h is the location of the scanner with lookahead, filter, and scanner testing function.
	  It also includes several error handlers and token creation/generation
	 ttoken.h holds the ttoken structure and the enumeration and strings for token IDs
	 langscan.h is the location of the FSA table and numerous setters for the FSADriver function 
	 FSAChart.xlsx is a spreadsheet format of the FSA table
	 .txt files
	 aside from readme, these are tests, but readme can also function as a test. 
	  One which should fail on line 19, character 15
	 test1.txt tests ID tokens
	 test2.txt tests bad ID token
	 test3.txt tests a bad non-ID token
	 test4.txt tests all symbol tokens
	 testkw.txt tests all keywords
	 multiline.txt tests over multiple lines
	 comment.txt tests comments
	 teof.txt was used for testing EOF bugs.

