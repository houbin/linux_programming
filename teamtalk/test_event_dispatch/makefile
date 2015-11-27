CXX=g++
CXX_FLAGS=-g -Wall

LIBS = -lpthread

MAKE_DIR=.
OBJ_DIR = $(MAKE_DIR)/obj
BIN_DIR = $(MAKE_DIR)/bin
SRC_DIR = $(MAKE_DIR)/src

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CXX) -c $(CXX_FLAGS) $^ -o $@

TARGET = $(BIN_DIR)/test_teamtalk

all : $(TARGET)

$(TARGET): $(OBJ_DIR)/BaseSocket.o $(OBJ_DIR)/EventDispatch.o $(OBJ_DIR)/imconn.o $(OBJ_DIR)/main.o $(OBJ_DIR)/netlib.o $(OBJ_DIR)/Lock.o $(OBJ_DIR)/util.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBS)

clean:
	rm -rf $(BIN_DIR)/$(TARGET) $(OBJ_DIR)/*

