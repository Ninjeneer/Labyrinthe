# ENSICAEN
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex
#
# This file is owned by ENSICAEN students. No portion of this
# document may be reproduced, copied or revised without written
# permission of the authors.
#
# Author : Loan Alouache

CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ansi -std=c99 -lm

FOLDER_SRC=src
FOLDER_INC=includes
OBJ=labyrinth.o game.o display.o file.o monsters.o deck.o
EXECOBJS=$(OBJ) main.o
TESTSOBJ=$(OBJ) tests/tests.o

EXEC=game
TESTS=testsuite
DOC_OUTPUT=doc/

FOLDER_MAP=maps/
FOLDER_SCORE=scores/

# Compile the game
all: $(EXEC)

$(EXEC): $(EXECOBJS)
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo 'Game compiled ! Run "make run" to start the game.'
	@make -s clean
	@make -s folders

$(TESTS): $(TESTSOBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo 'Test suite compiled ! Run "make run_test" to start the test suite.'
	@make -s clean
	@make -s folders


labyrinth.o: $(FOLDER_SRC)/labyrinth.c $(FOLDER_INC)/labyrinth.h
	@$(CC) -o $@ -c $< $(CFLAGS)

game.o: $(FOLDER_SRC)/game.c $(FOLDER_INC)/game.h
	@$(CC) -o $@ -c $< $(CFLAGS)

monsters.o: $(FOLDER_SRC)/monsters.c $(FOLDER_INC)/monsters.h
	@$(CC) -o $@ -c $< $(CFLAGS)

display.o: $(FOLDER_SRC)/display.c $(FOLDER_INC)/display.h
	@$(CC) -o $@ -c $< $(CFLAGS)

main.o: $(FOLDER_SRC)/main.c
	@$(CC) -o $@ -c $< $(CFLAGS)

file.o: $(FOLDER_SRC)/file.c $(FOLDER_INC)/file.h
	@$(CC) -o $@ -c $< $(CFLAGS)

deck.o: $(FOLDER_SRC)/deck.c $(FOLDER_INC)/deck.h
	@$(CC) -o $@ -c $< $(CFLAGS)

# Run the game
run:
	@./$(EXEC)

# Run test suite
run_test:
	@./$(TESTS)

# Generate documentation
doc:
	@rm -rf $(DOC_OUTPUT)
	@doxygen doxyfile

# Create the maps and scores folder
folders:
	@if [ ! -d "$(FOLDER_MAP)" ]; then mkdir $(FOLDER_MAP); fi
	@if [ ! -d "$(FOLDER_SCORE)" ]; then mkdir $(FOLDER_SCORE); fi

# Clean directory of temp. files
clean:
	@rm -rf *.o
	@rm -rf tests/*.o

# Reset the directory before make command
distclean: clean
	@rm -f $(EXEC)
	@rm -f $(TESTS)
	@rm -rf $(DOC_OUTPUT)

.PHONY: all clean distclean run run_test doc folders $(EXEC) $(TESTS)