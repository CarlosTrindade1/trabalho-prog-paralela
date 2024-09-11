# Makefile for the graph project

# Compiler
CC = g++

all: compile run

compile:
	${CC} -Iinclude graph.cpp main.cpp -o main

run:
	./main ./datasets/citeseer.edgelist 0