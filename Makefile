CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra 
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR := ./src
OBJDIR := ./obj
BINDIR := .

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all clean run

all: $(BINDIR)/gamefile

$(BINDIR)/gamefile: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(BINDIR)/gamefile

run: $(BINDIR)/gamefile
	./$(BINDIR)/gamefile


# -pedantic -Werror
