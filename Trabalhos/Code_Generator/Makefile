LEX=flex
YY=bison
CXX=g++
BIN = sintatico
L_SOURCE = lexico.l
Y_SOURCE = sintatico.y
CFLAGS = -std=c++11 -I. -w

$(BIN): $(L_SOURCE) $(Y_SOURCE)
	$(LEX) -o lex.yy.cc $(L_SOURCE) 
	$(YY) -d -v $(Y_SOURCE) -o sintatico.tab.cc
	$(CXX) *.cc $(CFLAGS) -o $(BIN) 

clean:
	rm -f $(BIN) lex.yy.c sintatico.tab.* sintatico.output lex.yy.cc
