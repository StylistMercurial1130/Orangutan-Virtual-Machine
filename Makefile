CC = gcc
SRC = ./src
INC = ./include
BIN = ./bin
BUILD = ./build
vpath %.c $(SRC)

$(BUILD)/%.o : %.c
	$(CC) -c -I $(INC) -o $@ $^

$(BIN)/% : 	$(wildcard $(BUILD)/*.o)
	$(CC) -g -o $@ $^


