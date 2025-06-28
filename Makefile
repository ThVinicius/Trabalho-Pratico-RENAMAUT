# Diretórios base dos fontes
SRC_DIR_LISTA_ENCADEADA := modules/lista-encadeada
SRC_DIR_BST := modules/arvore-binaria-de-busca
SRC_DIR_AVL := modules/arvore-avl
SRC_DIR_HASH := modules/hash
SRC_DIR_TREE := modules/busca-digital
SHARED_DIR := modules/shared
OBJ_DIR := libs
BIN_DIR := build

# Nomes dos executáveis finais
TARGET_BST := $(BIN_DIR)/index_bst # Executável para a Árvore Binária de Busca
TARGET_AVL := $(BIN_DIR)/index_avl # Executável para a Árvore AVL
TARGET_HASH := $(BIN_DIR)/index_hash # Novo Executável para a Tabela Hash
TARGET_LIST := $(BIN_DIR)/index_list # Novo Executável para a Lista encadeada
TARGET_TREE := $(BIN_DIR)/index_busca-digital # Novo Executável para a Arvore Patricia

# Flags do compilador
CFLAGS := -ansi -pedantic -Wall -g

# ======================================================================================
# Arquivos .c específicos da Árvore Binária de Busca (BST)
# Encontra todos os arquivos .c dentro de modules/arvore-binaria-de-busca/src/
SRC_FILES_BST := $(shell find $(SRC_DIR_BST) -name '*.c')

# ======================================================================================
# Arquivos .c específicos da Árvore AVL
# Encontra todos os arquivos .c dentro de modules/arvore-avl/src/
SRC_FILES_AVL := $(shell find $(SRC_DIR_AVL) -name '*.c')

# ======================================================================================
# Arquivos .c específicos da Tabela Hash
# Encontra todos os arquivos .c dentro de modules/hash/src/
SRC_FILES_HASH := $(shell find $(SRC_DIR_HASH) -name '*.c')

# ======================================================================================

# ======================================================================================
# Arquivos .c específicos da Lista encadeada
# Encontra todos os arquivos .c dentro de modules/lista-encadeada
SRC_FILES_LIST := $(shell find $(SRC_DIR_LISTA_ENCADEADA) -name '*.c')

# ======================================================================================

# ======================================================================================
# Arquivos .c específicos da Arvore Patricia
# Encontra todos os arquivos .c dentro de modules/arvore-patricia
SRC_FILES_TREE := $(shell find $(SRC_DIR_TREE) -name '*.c')

# ======================================================================================

# Arquivos .c compartilhados entre as estruturas de dados
SHARED_SERVICES_FILES := $(shell find $(SHARED_DIR) -name '*.c')

# ======================================================================================
# Arquivos objeto (.o) pre-compilados na pasta libs/ (gov_dev.o, parson.o, etc.)
LIB_OBJ_FILES := $(shell find $(OBJ_DIR) -name '*.o')

# ======================================================================================
# Regra Padrão (all) - MOVIDA PARA O INÍCIO
# O alvo 'all' construirá todos os executáveis
# Esta regra sendo a primeira faz com que 'make' sozinho compile todos os executáveis
all: $(TARGET_BST) $(TARGET_AVL) $(TARGET_HASH) $(TARGET_LIST) $(TARGET_TREE)

# ======================================================================================
# Regras de Build

# Regra para compilar o executável da Árvore Binária de Busca (BST)
$(TARGET_BST): $(SRC_FILES_BST) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES)
	@mkdir -p $(BIN_DIR) # Garante que o diretório de build existe
	gcc $(CFLAGS) $(SRC_FILES_BST) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES) -o $(TARGET_BST)
	@echo "✅ Build completo para BST: $(TARGET_BST)"

# Regra para compilar o executável da Árvore AVL
$(TARGET_AVL): $(SRC_FILES_AVL) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES)
	@mkdir -p $(BIN_DIR) # Garante que o diretório de build existe
	gcc $(CFLAGS) $(SRC_FILES_AVL) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES) -o $(TARGET_AVL)
	@echo "✅ Build completo para AVL: $(TARGET_AVL)"

# Regra para compilar o executável da Tabela Hash
$(TARGET_HASH): $(SRC_FILES_HASH) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES)
	@mkdir -p $(BIN_DIR) # Garante que o diretório de build existe
	gcc $(CFLAGS) $(SRC_FILES_HASH) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES) -o $(TARGET_HASH)
	@echo "✅ Build completo para Hash: $(TARGET_HASH)"

# Regra para compilar o executável da Lista Encadeada
$(TARGET_LIST): $(SRC_FILES_LIST) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES)
	@mkdir -p $(BIN_DIR) # Garante que o diretório de build existe
	gcc $(CFLAGS) $(SRC_FILES_LIST) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES) -o $(TARGET_LIST)
	@echo "✅ Build completo para Lista Encadeada: $(TARGET_LIST)"

# Regra para compilar o executável da Arvore patricia
$(TARGET_TREE): $(SRC_FILES_TREE) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES)
	@mkdir -p $(BIN_DIR) # Garante que o diretório de build existe
	gcc $(CFLAGS) $(SRC_FILES_TREE) $(SHARED_SERVICES_FILES) $(SHARED_INTERFACE_USECASE_FILES) $(LIB_OBJ_FILES) -o $(TARGET_TREE)
	@echo "✅ Build completo para Busca Digital: $(TARGET_TREE)"

# ======================================================================================
# Regras de Limpeza

clean:
	rm -rf $(BIN_DIR) # Remove o diretório de build e seus conteúdos
	@echo "🧹 Limpeza feita."

# Define alvos 'phony' que não correspondem a nomes de arquivos, garantindo que o make os execute
.PHONY: all clean $(TARGET_BST) $(TARGET_AVL) $(TARGET_HASH) $(TARGET_LIST) $(TARGET_TREE)