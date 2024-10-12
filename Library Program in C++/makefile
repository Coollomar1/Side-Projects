# Name: Omar Masri
# Date: 5/2/24

# Code Description:



CC = g++
CFLAGS = -Wall -g 

EXECUTABLE = library.exe
MAIN = driver.cpp

# Includes the file containing SOURCES and HEADERS
include defs.mk

# Added to compile the .cpp files into object files using the header files
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Change MAIN to MAIN.CPP=.o to replace the .cpp with .o
# This allows for driver-1.o object file to be created, which is needed for the library.exe executable
$(EXECUTABLE): $(MAIN.cpp=.o) objects
	$(CC) $(CFLAGS) $(MAIN) $(OBJECTS) -o $(EXECUTABLE)
objects: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -c


run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

empty:
	rm -f *.o
	rm -f $(EXECUTABLE)
