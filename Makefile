# Build Variable
CC = gcc

# Build Option Variable
CCFLAGS = -Wall -W -O2 -std=c17

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
OBJS = $(SRCS:.c=.o)
OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS))

# Target Variable
TARGET = \
errno-1 \
clock-1 \
timer-1 \

# Target Files
# TARGETS = $(patsubst %, %.out, $(TARGET))


all: $(TARGET)

$(OBJ_DIR)/002_clock-1.o: $(SRC_DIR)/002_clock-1.c
	$(CC) $(CCFLAGS) -D_POSIX_C_SOURCE=199309L $(HDRS) -c $< -o $@

$(OBJ_DIR)/003_timer-1.o: $(SRC_DIR)/003_timer-1.c
	$(CC) $(CCFLAGS) $(HDRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) $(HDRS) -c $< -o $@

errno-1: $(OBJ_DIR)/001_errno-1.o
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)

clock-1: $(OBJ_DIR)/002_clock-1.o
	$(CC) $(CCFLAGS) -lrt $^ -o $@ $(LDFLAGS)

timer-1: $(OBJ_DIR)/003_timer-1.o
	$(CC) $(CCFLAGS) -lrt $^ -o $@ $(LDFLAGS)

.PHONY: clean all
clean:
	rm -f  $(OBJECTS) $(TARGET)

