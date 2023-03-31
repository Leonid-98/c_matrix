CC=gcc
CFLAGS= -Wall -I./inc

OUT_DIR=obj

$(OUT_DIR)/main.o: src/main.c
	@$(CC) $(CFLAGS) -c src/main.c -o $(OUT_DIR)/main.o

$(OUT_DIR)/main: $(OUT_DIR)/main.o
	@$(CC) $(CFLAGS) (OUT_DIR)/main.o -o $(OUT_DIR)/main.exe

clean:
	@rm -fr $(OUT_DIR)/*