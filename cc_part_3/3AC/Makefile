
CC = gcc
CFLAGS = -Wall -g

BISON_SRC = parser.y
FLEX_SRC = lexer.l
BISON_C = parser.tab.c
BISON_H = parser.tab.h
FLEX_C = lex.yy.c
TARGET = a.out

all: $(TARGET)

$(BISON_C) $(BISON_H): $(BISON_SRC)
	bison -d $(BISON_SRC)

$(FLEX_C): $(FLEX_SRC)
	flex $(FLEX_SRC)

$(TARGET): $(BISON_C) $(FLEX_C)
	$(CC) $(CFLAGS) -o $(TARGET) $(BISON_C) $(FLEX_C)

test: $(TARGET)
	./$(TARGET) input.txt

clean:
	rm -f $(TARGET) $(BISON_C) $(BISON_H) $(FLEX_C) *.o

.PHONY: all test clean