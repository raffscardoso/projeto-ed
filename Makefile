CC = gcc
CFLAGS = -Wall -Wextra -Ilib -g

SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(LIB_DIR)/*.c) $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

TARGET = $(BIN_DIR)/jogo

all: createdirs $(TARGET)
	@echo "Compilação concluída. Executável em: $(TARGET)"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

createdirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

run: all
	@echo "--- Executando ---"
	@./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	rm -rf *.txt
	@echo "Limpeza concluída."

.PHONY: all clean run createdirs
