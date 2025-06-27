# Diretórios base dos fontes
SRC_DIR_BST := modules/arvore-binaria-de-busca/src
SRC_DIR_AVL := modules/arvore-avl/src
SHARED_DIR := modules/shared # Ajustado para o diretório correto dos serviços compartilhados
OBJ_DIR := libs
BIN_DIR := build

# Nomes dos executáveis finais
TARGET_BST := $(BIN_DIR)/index_bst # Executável para a Árvore Binária de Busca
TARGET_AVL := $(BIN_DIR)/index_avl # Executável para a Árvore AVL

# Flags do compilador
CFLAGS := -ansi -pedantic -Wall

# ======================================================================================
# Arquivos .c específicos da Árvore Binária de Busca (BST)
# Encontra todos os arquivos .c dentro de modules/arvore-binaria-de-busca/src/
SRC_FILES_BST := $(shell find $(SRC_DIR_BST) -name '*.c')

# ======================================================================================
# Arquivos .c específicos da Árvore AVL
# Encontra todos os arquivos .c dentro de modules/arvore-avl/src/
SRC_FILES_AVL := $(shell find $(SRC_DIR_AVL) -name '*.c')

# ======================================================================================
# Arquivos .c compartilhados entre as estruturas de dados
# Encontra todos os arquivos .c dentro de modules/shared/services/
SHARED_SERVICES_FILES := $(shell find $(SHARED_DIR) -name '*.c')

# ======================================================================================
# Arquivos objeto (.o) pre-compilados na pasta libs/ (gov_dev.o, parson.o, etc.)
LIB_OBJ_FILES := $(shell find $(OBJ_DIR) -name '*.o')

# ======================================================================================
# Regras de Build

# Regra para compilar o executável da Árvore Binária de Busca (BST)
$(TARGET_BST): $(SRC_FILES_BST) $(SHARED_SERVICES_FILES) $(LIB_OBJ_FILES)
	@mkdir -p $(BIN_DIR) # Garante que o diretório de build existe
	gcc $(CFLAGS) $(SRC_FILES_BST) $(SHARED_SERVICES_FILES) $(LIB_OBJ_FILES) -o $(TARGET_BST)
	@echo "✅ Build completo para BST: $(TARGET_BST)"

# Regra para compilar o executável da Árvore AVL
$(TARGET_AVL): $(SRC_FILES_AVL) $(SHARED_SERVICES_FILES) $(LIB_OBJ_FILES)
	@mkdir -p $(BIN_DIR) # Garante que o diretório de build existe
	gcc $(CFLAGS) $(SRC_FILES_AVL) $(SHARED_SERVICES_FILES) $(LIB_OBJ_FILES) -o $(TARGET_AVL)
	@echo "✅ Build completo para AVL: $(TARGET_AVL)"

# ======================================================================================
# Regras de Limpeza

clean:
	rm -rf $(BIN_DIR) # Remove o diretório de build e seus conteúdos
	@echo "🧹 Limpeza feita."

# ======================================================================================
# Regras Padrão (all)
# O alvo 'all' construirá ambos os executáveis
all: $(TARGET_BST) $(TARGET_AVL)

# Define alvos 'phony' que não correspondem a nomes de arquivos, garantindo que o make os execute
.PHONY: all clean $(TARGET_BST) $(TARGET_AVL)
