# Makefile for the graph project

# Compiler
CC = g++

# include directories
INCLUDE_DIR = include
INCLUDES = ${wildcard ${INCLUDE_DIR}/*}
INCLUDE_FLAGS = ${addprefix -I, ${INCLUDES}}

# Source directories
SOURCE_DIR = src

# Source files
SOURCE_FILES = $(wildcard $(SOURCE_DIR)/**/*.cpp) main.cpp
OUTPUT = counter


all: compile

compile:
	${CC} ${INCLUDE_FLAGS} ${SOURCE_FILES} -o ${OUTPUT}

run:
	./counter ./datasets/citeseer.edgelist 3 0 5