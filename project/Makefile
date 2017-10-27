#Note, you may have to update CXX_DIR and
#CXXTEXT to point the right locations and executables
#to get it to work - look at your Lab 3 Makefile
CXX_DIR = ./lib/cxxtest
CXXTEST = $(CXX_DIR)/bin/cxxtestgen
CXXFLAGS = --error-printer --abort-on-fail --have-eh

FLAGS = -g -Wall -I. -std=gnu++11

all: parser run-tests

# Program files.

cpp:
	python3 cpplint.py --repository=.. src/*.cc include/*.h

read_input.o:	src/read_input.cc include/read_input.h
	g++ $(FLAGS) -c src/read_input.cc

regex.o:	src/regex.cc include/regex.h
	g++ $(FLAGS) -c src/regex.cc

# Below is a possible way to make scanner
# Yours may vary depending on your implementation
#scanner.o:	src/scanner.cc include/scanner.h include/regex.h
#	g++ $(FLAGS) -c src/scanner.cc

scanner: scanner.o token.o regex.o read_input.o
	g++ -Wall -o scanner scanner.o token.o regex.o read_input.o

scanner.o: src/scanner.cc src/regex.cc src/read_input.cc include/scanner.h include/regex.h include/read_input.h
	g++ $(FLAGS) -c src/scanner.cc

token.o: src/token.cc include/token.h include/scanner.h
	g++ $(FLAGS) -c src/token.cc

parser: ext_token.o parser.o token.o scanner.o regex.o read_input.o
	g++ -Wall -o parser parser.o ext_token.o scanner.o token.o regex.o read_input.o

parser.o: src/parser.cc include/parser.h src/scanner.cc include/scanner.h src/ext_token.cc include/ext_token.h include/parse_result.h include/ast.h include/declarations.h include/expr.h include/program.h include/stmt.h include/stmts.h include/decl.h
	g++ $(FLAGS) -Wno-reorder -Wno-return-type -c src/parser.cc

ext_token.o: src/ext_token.cc include/ext_token.h src/token.cc include/token.h src/scanner.cc include/scanner.h src/parser.cc include/parser.h include/ast.h include/parse_result.h
	g++ $(FLAGS) -c -Wno-reorder -Wno-return-type src/ext_token.cc

Matrix.o: src/Matrix.cc include/Matrix.h
	g++ $(FLAGS) -c src/Matrix.cc

# path to run a test case on matrix.cc
matrix_test: Matrix.o matrix_test.cc
	g++ $(FLAGS) -o matrix_test matrix_test.cc Matrix.o

# Testing files and targets.
# run-tests should work once
# and run regex_tests once you put the files
# we gave you in the right places
# and update the CXX_DIR and CXXTEST variables so they
# reference the correct directory locations
# Add scanner_tests to the dependency list and uncomment when
# you are ready to start testing units with scanner_tests.
run-tests:	regex_tests scanner_tests parser_tests ast_tests codegeneration_tests
	./regex_tests
	./scanner_tests
	./parser_tests
	./ast_tests
	./codegeneration_tests

# below are the paths to compile codegeneration_tests
codegeneration_tests: codegeneration_tests.cc parser.o scanner.o token.o Matrix.o read_input.o ext_token.o regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -Wno-reorder -Wno-return-type -o codegeneration_tests \
		parser.o scanner.o token.o Matrix.o read_input.o ext_token.o regex.o codegeneration_tests.cc

codegeneration_tests.cc: parser.o read_input.o tests/codegeneration_tests.h
	$(CXXTEST) $(CXXFLAGS) -o codegeneration_tests.cc tests/codegeneration_tests.h

# below are the paths to compile ast_tests
ast_tests: ast_tests.cc parser.o scanner.o token.o read_input.o ext_token.o regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -Wno-reorder -Wno-return-type -o ast_tests parser.o \
		read_input.o ext_token.o regex.o scanner.o token.o ast_tests.cc

ast_tests.cc: parser.o read_input.o tests/ast_tests.h
	$(CXXTEST) $(CXXFLAGS) -o ast_tests.cc tests/ast_tests.h

# below are the paths to compile parser_tests
parser_tests: parser_tests.cc scanner.o parser.o token.o read_input.o regex.o ext_token.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -Wno-reorder -Wno-return-type -o parser_tests \
		scanner.o token.o ext_token.o regex.o read_input.o parser.o parser_tests.cc

parser_tests.cc: scanner.o token.o parser.o tests/parser_tests.h include/read_input.h
	$(CXXTEST) $(CXXFLAGS) -o parser_tests.cc tests/parser_tests.h

# This should work once you put the files
# we gave you in the right places
regex_tests: regex_tests.cc regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -o regex_tests regex.o regex_tests.cc

regex_tests.cc: include/regex.h tests/regex_tests.h
	$(CXXTEST) $(CXXFLAGS) -o regex_tests.cc tests/regex_tests.h

# Below is a possible way to make scanner_tests and scanner_tests.cc
# Yours may vary depending on your design and implementation
scanner_tests: scanner_tests.cc scanner.o token.o regex.o read_input.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -o scanner_tests \
		scanner.o token.o regex.o read_input.o scanner_tests.cc

scanner_tests.cc: scanner.o token.o tests/scanner_tests.h include/read_input.h
	$(CXXTEST) $(CXXFLAGS) -o scanner_tests.cc tests/scanner_tests.h

clean:
	rm -Rf *.o \
		regex_tests regex_tests.cc \
		scanner_tests scanner_tests.cc \
		parser_tests parser_tests.cc \
		ast_tests ast_tests.cc \
		codegeneration_tests codegeneration_tests.cc \
		samples/*.dslup* \
		matrix_test
