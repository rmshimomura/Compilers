LEX=flex
YY=bison
CC=gcc
BIN = sintatico
L_SOURCE = lexico.l
Y_SOURCE = sintatico.y
CFLAGS = -std=c99 -I. -w

$(BIN): $(L_SOURCE) $(Y_SOURCE)
	$(LEX) $(L_SOURCE)
	$(YY) -d -t $(Y_SOURCE)
	$(CC) *.c $(CFLAGS) -o $(BIN)