# === Variables ===
CC       := g++
CFLAGS   := -std=c++23 -Wall -Wextra -g
INC_DIR  := include
SRC_DIR  := src
RAYLIB_INC_DIR := include/raylib-5.5_linux_amd64/include
RAYLIB_LIB_DIR := include/raylib-5.5_linux_amd64/lib
BLD_DIR  := build
EXE      := AICHESS

# === Trouve automatiquement tous les fichiers .c dans SRC_DIR ===
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(SRCS))

# === Règle principale ===
all: $(BLD_DIR)/$(EXE)

# === Lien final ===
$(BLD_DIR)/$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(RAYLIB_LIB_DIR) -Wl,-Bstatic -lraylib -Wl,-Bdynamic

# === Compilation générique pour chaque .o ===
$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BLD_DIR)
	$(CC) -c $(CFLAGS) -I$(RAYLIB_INC_DIR) -I$(INC_DIR) $< -o $@

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
