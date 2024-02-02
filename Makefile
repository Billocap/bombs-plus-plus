# Compiles the project
CC=g++

# Project name
PROJ_NAME=bombs++

# Necessary folders
OBJ_FOLDER=./obj
BIN_FOLDER=./bin

# Entry file
ENTRY=main
# Flags only used when compiling the entry file
ENTRY_FLAGS=-l ncursesw

FLAGS=-pedantic -I ./include
DEBUG_FLAGS=$(FLAGS) -g

SRC_FILES=$(shell find . -regex ".*\.cpp")
OBJ_FILES=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRC_FILES:.cpp=.o)))
DBG_FILES=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRC_FILES:.cpp=.dbg.o)))

default: prod

# Global processes
prep:
	@echo " Verifying if the necessary folders exists ..."
	@if [ ! -d $(OBJ_FOLDER) ]; then mkdir $(OBJ_FOLDER); fi
	@if [ ! -d $(BIN_FOLDER) ]; then mkdir $(BIN_FOLDER); fi
	@echo " Verification complete"

clean:
	@echo " Cleaning up ..."
	@rm -rf $(OBJ_FOLDER)
	@echo " Clean up complete"
#--------------------

# Entry points
# Output for debug mode is always the same
debug: prep dbg.out clean
	@echo ""
	@echo "Compilation complete"
	@echo "- Mode:    DEBUG"
	@echo "- Project: $(PROJ_NAME)"
	@echo "- Binary:  $(BIN_FOLDER)/dbg.out"
	@echo ""

prod: prep $(PROJ_NAME) clean
	@echo ""
	@echo "Compilation complete"
	@echo "- Mode:    PRODUCTION"
	@echo "- Project: $(PROJ_NAME)"
	@echo "- Binary:  $(BIN_FOLDER)/$(PROJ_NAME)"
	@echo ""
#------------------------

# Main file compilation
dbg.out: $(DBG_FILES)
	@echo " Compilling project binary ..."
	$(CC) $^ -o $(BIN_FOLDER)/$@ $(DEBUG_FLAGS) $(ENTRY_FLAGS)
	@echo " Project binary created"

$(PROJ_NAME): $(OBJ_FILES)
	@echo " Compilling project binary ..."
	@$(CC) $^ -o $(BIN_FOLDER)/$@ $(FLAGS) $(ENTRY_FLAGS)
	@echo " Project binary created"
#------------------------

# Object file compilation
$(OBJ_FILES):
	@echo " Compilling object file $@ ..."
	@$(CC) -c $(shell find . -regex ".*$(@F:.o=.cpp)") -o $@ $(FLAGS)
	@echo " Object file $@ compiled"

$(DBG_FILES):
	@echo " Compilling object file $@ ..."
	$(CC) -c $(shell find . -regex ".*$(@F:.dbg.o=.cpp)") -o $@ $(DEBUG_FLAGS)
	@echo " Object file $@ compiled"
#------------------------
