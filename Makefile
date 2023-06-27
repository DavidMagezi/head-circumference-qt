CXX = g++
CFLAGS = $$(pkg-config --cflags --libs Qt5Widgets) -fPIC
OBJ_EXT = .o
CPP_EXT =.cpp

BASE_DIR = ./
EXEC_DIR = $(BASE_DIR)bin
SRC_DIR = $(BASE_DIR)src
OBJ_DIR =$(BASE_DIR)objs

IQUOTE=-iquote$(SRC_DIR)

TARGET_STEM = viewer
TARGET = $(EXEC_DIR)/$(TARGET_STEM)

_GUI = gui
_GUI_DEPS = image.h select.h

GUI_OBJ_DIR = $(OBJ_DIR)/$(_GUI)
GUI_SRC_DIR = $(SRC_DIR)/$(_GUI)
GUI_DEPS = $(addprefix $(GUI_SRC_DIR)/, $(_GUI_DEPS))
_GUI_OBJS = $(_GUI_DEPS:.h=.o) 
GUI_OBJS = $(addprefix $(GUI_OBJ_DIR)/, $(_GUI_OBJS))

all: $(TARGET)

$(EXEC_DIR):
	mkdir -p $@

$(GUI_OBJ_DIR):
	mkdir -p $@

$(GUI_OBJS): $(GUI_OBJ_DIR)/%$(OBJ_EXT): $(GUI_SRC_DIR)/%$(CPP_EXT) $(GUI_DEPS) | $(GUI_OBJ_DIR)
	$(CXX)  $< -c -o $@  $(CFLAGS) $(IQUOTE)

$(TARGET): $(SRC_DIR)/$(TARGET_STEM)$(CPP_EXT) $(GUI_OBJS) | $(EXEC_DIR)
	@echo "Compiling and linking $(TARGET) ..."
	$(CXX) $< -o $@ $(CFLAGS) $(GUI_OBJS)

clean:
	rm $(TARGET) 
	rmdir $(EXEC_DIR) 

run:
	$(TARGET)
