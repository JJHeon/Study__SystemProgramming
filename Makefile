# Build Variable
CC = gcc

# Build Option Variable
CCFLAGS = -Wall -O2

# Linker Option
LDFLAGS =

# Source File Directory
SRC_DIR = ./src

# Object File Directory
OBJ_DIR = ./obj


# Header Files
HDRS = -I$(SRC_DIR)

# Source Files
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c))

# Object Files
OBJS = $(SRCS:.cc=.o)
OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS))

# Target Variable
TARGET = \
errno-1 \


# Target Files
# TARGETS = $(patsubst %, %.out, $(TARGET))


all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) $(HDRS) -c $< -o $@

errno-1: $(OBJ_DIR)/001_errno-1.o
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)


.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(TARGET)

