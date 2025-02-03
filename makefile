# Variáveis
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
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
	@mkdir -p $(BINDIR)  # Garante que o diretório bin/ exista
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)  # Garante que o diretório obj/ exista
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Regra padrão
all: $(EXEC)

.PHONY: all clean
