
CC = gcc
CFLAGS = -Wall -g

BISON_SRC = test2.y
FLEX_SRC = test2.l
BISON_C = test2.tab.c
BISON_H = test2.tab.h
FLEX_C = lex.yy.c
TARGET = a.exe

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