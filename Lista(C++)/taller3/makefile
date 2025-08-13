# makefile: brigido noguera

# Variable para el compilador
CC = g++

QFLAGS = -std=c++98 -Wall -Wextra 
MAIN = main.cpp

# en esta variable ira el directorio de los archivos *.hpp
DIR = ../lib

# Como ira despues del main.cpp, le dira donde se ubica los archivos cabezera
HEADS = -I$(DIR)

TARGET = RUN


all: $(TARGET)


$(TARGET): $(MAIN)
	$(CC) -O3 $(QFLAGS) $(MAIN) $(HEADS) -o $(TARGET)
	
clean:
	rm -f ./*.o $(TARGET)
	
.PHONY:	clean all
