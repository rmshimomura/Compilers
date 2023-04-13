LEX=flex
YY=bison
CXX=g++
BIN = gerador
L_SOURCE = lexico.l
Y_SOURCE = sintatico.y
CFLAGS = -std=c++11 -I. -w

sintatico: $(L_SOURCE) $(Y_SOURCE)
	$(LEX) -o lex.yy.cc $(L_SOURCE) 
	$(YY) -d $(Y_SOURCE) -o sintatico.tab.cc
	$(CXX) -g *.cc $(CFLAGS) -o $(BIN) 

debug: $(L_SOURCE) $(Y_SOURCE)
	$(LEX) -o lex.yy.cc $(L_SOURCE) 
	$(YY) -d -v $(Y_SOURCE) -o sintatico.tab.cc
	$(CXX) -g *.cc $(CFLAGS) -o $(BIN)

clean:
	rm -f $(BIN) lex.yy.c sintatico.tab.* sintatico.output lex.yy.cc *.o
