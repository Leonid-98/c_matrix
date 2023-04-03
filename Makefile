CC=gcc
CFLAGS = -Wall -std=c99 -I./inc

EXEC = main
OUT_DIR=obj
SRC_DIR=src

# To compile all files from src folder
SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS := $(filter-out $(SRC_DIR)/main.c, $(SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(SRCS))

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)

$(EXEC): $(OUT_DIR)/main.o $(OBJS)
	@$(CC) $^ -o $@ 

.PHONY: clean
clean:
	@rm -rf $(EXEC) $(OUT_DIR)/*

build: $(EXEC)