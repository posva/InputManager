CXX = g++
OBJ = obj
SRC = src
BIN = bin
STD := -std=c++0x
EXT_IL := -I$(SRC)

MAIN := main
TEST_DIR := tests

ifeq ($(SHELL), sh.exe) 
OS := Win
FOLDERS := $(wildcard $(SRC)/*/) $(wildcard $(SRC)/*/*/) $(wildcard $(SRC)/*/*/*/)
POINTC = $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*/*.cpp) $(wildcard $(SRC)/*/*/*.cpp) $(wildcard $(SRC)/*/*/*/*.cpp)
POINTOP := $(POINTC:.cpp=.o)
POINTO = $(patsubst src/%,$(OBJ)%,$(POINTOP)) #$(POINTOP:src=obj)
#CREER LA LISTE DE DOSSIERS À LA MAIN :/
else
OS := $(shell uname)
FOLDERSP := $(shell find $(SRC)/* -type d)
FOLDERS := $(patsubst $(SRC)/%,$(OBJ)/%,$(FOLDERSP))
POINTC := $(shell find $(SRC)/* -type f -name '*.cpp')
POINTO := $(patsubst $(SRC)/%,$(OBJ)/%,$(POINTC))
POINTO := $(POINTO:.cpp=.o)
endif

EXEC := InputManager

ifeq ($(OS), Linux)
RM = rm
LIBS := -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
endif
ifeq ($(OS), Darwin)
RM = rm
LIBS := -L/usr/local/lib -framework sfml-system -framework sfml-window -framework sfml-graphics
CXX := xcrun clang++
STD := -std=c++11 -stdlib=libc++
EXT_IL := -I$(SRC)
endif
ifeq ($(OS), Win)
RM = del
LIBS := -lsfml-graphics -lsfml-window -lsfml-system
endif

OPT := -Wall -Wno-long-long -Os -g $(EXT_IL) $(STD)

all : dirs $(BIN)/$(EXEC)
	

# TESTS
# For any test just add a new rule. ex:
#test_list: $(OBJ)/Core/blabla.o
#	$(CXX) $(OPT) $^ $(TEST_DIR)/"$@".cpp -o $(BIN)/"$@" $(LIBS)

dirs : 
ifeq ($(OS), Darwin)
	@mkdir -p $(OBJ) $(FOLDERS) $(BIN)
endif
ifeq ($(OS), Linux)
	@mkdir -p $(OBJ) $(FOLDERS) $(BIN)
endif
	
ifeq ($(OS), Win)
	@echo "You need to manually create subdirectories"
endif
.PHONY : dirs

clean: 
	$(RM) -rf $(OBJ) $(BIN)
.PHONY : clean

run: dirs $(BIN)/$(EXEC)
ifeq ($(OS), Darwin)
	./$(BIN)/$(EXEC)
endif
ifeq ($(OS), Linux)
	./$(BIN)/$(EXEC)
endif
ifeq ($(OS), Win)
	$(BIN)/$(EXEC).exe
endif
.PHONY : run

$(OBJ)/$(MAIN).o : $(SRC)/$(MAIN).cpp
	$(CXX) $(OPT) $< -c -o $@

$(OBJ)/%.o : $(SRC)/%.cpp $(SRC)/%.hpp
	$(CXX) $(OPT) $< -c -o $@


$(BIN)/$(EXEC) : $(POINTO)
	$(CXX) $(OPT) $^ -o "$@" $(LIBS)

valgrind : dirs $(BIN)/$(EXEC)
	valgrind -v --leak-check=full --tool=memcheck ./$(BIN)/$(EXEC)
	
info:
	@echo "Lines\tWords\tBytes"
	@cd src ; \
	find -E . -regex "(.+)\.(h|cpp|c|hpp)" -print0 | xargs -0 cat | wc ; \
	cd ..
.PHONY : info
