CXX = g++
CFLAGS = $$(pkg-config --cflags --libs Qt5Widgets) -fPIC
OBJ_EXT = .o
CPP_EXT =.cpp

BASE_DIR = ./
EXEC_DIR = $(BASE_DIR)bin
SRC_DIR = $(BASE_DIR)src
OBJ_DIR =$(BASE_DIR)objs

TARGET_STEM = viewer
TARGET = $(EXEC_DIR)/$(TARGET_STEM)

all: $(TARGET)

$(EXEC_DIR):
	mkdir -p $@

$(TARGET): $(SRC_DIR)/$(TARGET_STEM)$(CPP_EXT) | $(EXEC_DIR)
	@echo "Building $(TARGET) ..."
	$(CXX) $< -o $@ $(CFLAGS)

clean:
	rm $(TARGET) 
	rmdir $(EXEC_DIR) 

run:
	$(TARGET)
