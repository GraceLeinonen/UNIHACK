CXX		  := g++
CXX_FLAGS := -Wall -Wextra -Wno-unused-parameter -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
MAIN_SOURCE := main.cpp
TEST_SOURCE := tests

INCLUDE1:= include #this is the include folder that contains all the headers files
#for Mac
INCLUDE2 :=/opt/homebrew/Cellar/sfml/2.6.1/include #this is the directory that you can find the sfml library.
LIB		:= /opt/homebrew/Cellar/sfml/2.6.1/lib 

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main

TARGET_TEST := test_output


MKDIR_P = mkdir -p

.PHONY: directories

all: directories $(BIN)/$(EXECUTABLE)

directories: ${BIN}

${BIN}:
	${MKDIR_P} ${BIN}

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) $(MAIN_SOURCE) -I$(INCLUDE1) -I$(INCLUDE2) -L$(LIB) $^ -o $@ $(LIBRARIES)
	

#For window, use: $(CXX) $(CXX_FLAGS) -I$(INCLUDE1) $^ -o $@ $(LIBRARIES)
#For Mac, use: $(CXX) $(CXX_FLAGS) -I$(INCLUDE1) -I$(INCLUDE2) -L$(LIB) $^ -o $@ $(LIBRARIES) 
#Other way of make test: g++ $(FLAGS) -o test_exec $(TEST_SOURCE) -I$(INCLUDE1) -I$(INCLUDE2) -L$(LIB) $(LIBRARIES)

clean:
	-rm -r $(BIN)/*

test:
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE1) -I$(INCLUDE2) -L$(LIB) -o $(TARGET_TEST) $(TEST_SOURCE)/*.cpp $(SRC)/*.cpp $(LIBRARIES)
	./$(TARGET_TEST)

clean_test:
	rm -f $(TARGET_TEST) 
	-rm -r $(TARGET_TEST).dSYM/*