.PHONY: clean build all

# compilation settings
CC = gcc 
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g

# directory paths
INCLUDE_DIR = ./
SRC_DIR = ./
OBJ_DIR = ./

# file lists
CFILES = hashmap.c search.c train.c retrieve.c
OBJS = hashmap.o search.o train.o retrieve.o

# binary
BIN = search

all: $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

clean:
	rm -f $(OBJS) $(BIN) *~
