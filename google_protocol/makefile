CXX=g++
CXX_FLAGS=-g -Wall -O0
LIBS=-lpthread -lprotobuf

SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cc
	$(CXX) -c $(CXX_FLAGS) $^ -o $@

TARGETS=$(BIN_DIR)/person_test

# 编译目标
all : $(TARGETS)

$(BIN_DIR)/person_test:$(OBJ_DIR)/main.o $(OBJ_DIR)/Person.pb.o
	$(CXX) $(CXX_FLAGS) $(LIBS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*



