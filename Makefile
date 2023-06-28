# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

# Directories
SRC_DIR := src
OBJ_DIR := obj

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# SFML settings
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET := gamefile

# Makefile rules
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

