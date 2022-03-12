# COMPILER INFO
CC_CPP := clang++
FLG := -g -Wall

# PATHS AND FILES INFO

MAIN_SRC_PATH = src/
MAIN_BIN_PATH = bin/
TST_SRC_PATH = t_src/
TST_BIN_PATH = t_bin/
LIB_PATH = lib/
OBJ_PATH = obj/

EXT_LIB_PATH = extlib/

MAIN_SRC = $(wildcard $(MAIN_SRC_PATH)*.cpp)
MAIN_BIN = $(patsubst $(MAIN_SRC_PATH)%.cpp,$(MAIN_BIN_PATH)%,$(MAIN_SRC))
TST_SRC = $(wildcard $(TST_SRC_PATH)*.cpp)
TST_BIN = $(patsubst $(TST_SRC_PATH)%.cpp,$(TST_BIN_PATH)%,$(TST_SRC))
LIBS_SRC = $(wildcard $(LIB_PATH)*.cpp)
LIBS_OBJ = $(patsubst $(LIB_PATH)%.cpp,$(OBJ_PATH)%.o,$(LIBS_SRC))
EXT_OBJ=$(wildcard $(EXT_LIB_PATH)*.o)
# GENERATOR MAKE FUNCTIONS
all : all_msg libs bins tests
all_no_msg : bin_dirs $(LIBS_OBJ) $(MAIN_BIN) $(TST_BIN)
all_msg :

init : src_dirs init_msg
init_msg :
	@echo
	@echo Project init
	@echo Creating Source directories
	@echo $(LIB_PATH) $(TST_SRC_PATH) $(MAIN_SRC_PATH)
	@echo Add your library source files here eg: lib.cpp lib.h > $(LIB_PATH)/readme.ini
bin_dirs :
	@mkdir -p $(OBJ_PATH) $(TST_BIN_PATH) $(MAIN_BIN_PATH)
src_dirs :
	@mkdir -p $(LIB_PATH) $(TST_SRC_PATH) $(MAIN_SRC_PATH)


bins : bin_msg bin_dirs $(MAIN_BIN)
bin_msg :
	@echo [BINS]
	@echo - Src Path: $(MAIN_SRC_PATH)
	@echo - Bin Path: $(MAIN_BIN_PATH)
	@echo - Sources: $(MAIN_SRC)
	@echo - Files: $(MAIN_BIN)
	
libs : libs_msg bin_dirs $(LIBS_OBJ)
libs_msg :
	@echo [LIBS]
	@echo - Path: $(LIB_PATH)
	@echo - Files: $(LIBS_OBJ)

tests : tests_msg bin_dirs $(TST_BIN)
tests_msg :
	@echo [TESTS]
	@echo - Path: $(TST_BIN_PATH)
	@echo - Files: $(TST_BIN)

clean:
	@rm -rf $(OBJ_PATH) $(TST_BIN_PATH) $(MAIN_BIN_PATH)
clean_tests:
	@rm -rf $(TST_BIN_PATH)
# GENERATOR RULES -COMPILING

# -libraries
$(OBJ_PATH)%.o : $(LIB_PATH)%.cpp
	@$(CC_CPP) $(FLG) -c $< -o $@ -I $(EXT_LIB_PATH)

# -tests
$(TST_BIN_PATH)% : $(TST_SRC_PATH)%.cpp $(LIBS_OBJ)
	@$(CC_CPP) $(FLG) -o $@ $^ $(EXT_OBJ) -I $(LIB_PATH) -I $(EXT_LIB_PATH)

# -main
$(MAIN_BIN_PATH)% : $(MAIN_SRC_PATH)%.cpp $(LIBS_OBJ)
	@$(CC_CPP) $(FLG) -o $@ $^ $(EXT_OBJ) -I $(LIB_PATH) -I $(EXT_LIB_PATH)
