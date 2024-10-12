# Name: Omar Masri
# Date: 4/16/24
# CPSC 1070 AND 1071
# Project 1: Strands

# Code Description: Actual makefile. Uses the SOURCES and HEADERS variables contained in the defs.mk file.
# This file creates an executable file by combining main.c, strand.c, and game.c 
# (HEADERS is used to ensure that the .c files get their appropriate prototypes and #inclusions)
# strands.exe executable file is created, and it is run by default with 1 argument (so the user will have to input a .txt file to play)
# clean removes the executable file
# This is a more neat method to create a makefile, as it keeps everything under one variable rather than typing out:
# gcc -Wall -o strands.exe main.c strand.c game.c



CC = gcc
CFLAGS = -Wall

EXECUTABLE = strands.exe
MAIN = main.c

# Includes the file containing SOURCES and HEADERS
include defs.mk

$(EXECUTABLE): $(MAIN) $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(MAIN) $(SOURCES)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)