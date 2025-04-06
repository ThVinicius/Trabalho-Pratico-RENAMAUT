# Diretórios
SRC_DIR := src
OBJ_DIR := libs
BIN_DIR := .build

# Nome do executável final
TARGET := $(BIN_DIR)/index

# Flags do compilador
CFLAGS := -ansi -pedantic -Wall

# Encontra todos os arquivos .c dentro de src/
SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')

# Encontra todos os arquivos .o dentro de libs/
OBJ_FILES := $(shell find $(OBJ_DIR) -name '*.o')

# Cria o binário a partir dos arquivos .c e .o
$(TARGET): $(SRC_FILES) $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) $(SRC_FILES) $(OBJ_FILES) -o $(TARGET)
	@echo "✅ Build completo: $(TARGET)"

# Limpa o binário
clean:
	rm -rf $(BIN_DIR)
	@echo "🧹 Limpeza feita."

# Build padrão
all: $(TARGET)
