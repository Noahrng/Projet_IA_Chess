# === Variables ===
CC       := g++
CFLAGS   := -std=c++23 -Wall -Wextra -g
INC_DIR  := include
SRC_DIR  := src
BLD_DIR  := build
EXE      := AICHESS

# === Trouve automatiquement tous les fichiers .c dans SRC_DIR ===
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(SRCS))

# === Règle principale ===
all: $(BLD_DIR)/$(EXE)

# === Lien final ===
$(BLD_DIR)/$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# === Compilation générique pour chaque .o ===
$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BLD_DIR)
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@

# === Crée le dossier build s’il n’existe pas ===
$(BLD_DIR):
	mkdir -p $(BLD_DIR)

# === Nettoyage ===
clean:
	rm -f $(BLD_DIR)/*.o
	rm -f $(BLD_DIR)/$(EXE)
	rm -f *.out
	rm -f *.txt

hclean:
	rm -f $(BLD_DIR)/*.o
	rm -f *.out
	rm -f *.txt

# === Recompilation complete avec nettoyage
remake:
	make clean
	make

.PHONY: all clean
