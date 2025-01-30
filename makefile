# Variáveis
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = 
OBJDIR = obj
BINDIR = bin
SRCDIR = src
INCDIR = include

# Diretórios e arquivos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/sistema_locadora

# Regras de compilação
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Regra padrão
all: $(EXEC)

.PHONY: all clean
