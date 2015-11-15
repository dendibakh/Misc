export profile?=F
.NOTPARALLEL:

# defining variables
BUILD_TOOL = clang++
ARCHIVE_TOOL = ar

COMPILE_FLAGS = -c -Wall -std=c++11
PROFILE_FLAGS = 
ifeq ($(profile) ,yes)
PROFILE_FLAGS = -pg
endif

LIB_NAME = taskSolution
LIB_SOURCES_DIR = ./src/
HEADER_DIR = -I$(LIB_SOURCES_DIR)/ -I./include/

TEST_NAME = taskTest
TEST_SOURCES_DIR = ./test/

OBJ_DIR = ./obj/

ADD_LIBRARIES_DIR = -L./lib/
#ADD_LIBRARIES = -lgtest_main
ADD_LIBRARIES = -lgmock_main -lcryptopp
ADD_HEADERS_DIR = ./include/

# BurrowsWheelerLib objects
LIB_SOURCES = $(wildcard $(LIB_SOURCES_DIR)*.cpp)
LIB_OBJECTS = $(subst $(LIB_SOURCES_DIR),$(OBJ_DIR),$(LIB_SOURCES:%.cpp=%.o))
LIB_FILENAMES = $(subst $(LIB_SOURCES_DIR),,$(LIB_SOURCES:%.cpp=%))

# tests objects
TEST_SOURCES = $(wildcard $(TEST_SOURCES_DIR)*.cpp)
TEST_OBJECTS = $(subst $(TEST_SOURCES_DIR),$(OBJ_DIR),$(TEST_SOURCES:%.cpp=%.o))
TEST_FILENAMES = $(subst $(TEST_SOURCES_DIR),,$(TEST_SOURCES:%.cpp=%))

# labels definition
all: clean taskLib tests run_tests

.PHONY: all taskLib tests clean run_tests

clean:
	rm -r -f $(OBJ_DIR)
	rm -r -f ./gmon.out
	rm -r -f ./profileReport.txt
	mkdir $(OBJ_DIR)

#building taskLib
taskLib: $(LIB_FILENAMES) build_lib

$(LIB_FILENAMES):
	$(BUILD_TOOL) $(HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(LIB_SOURCES_DIR)$@.cpp $(PROFILE_FLAGS)

build_lib:
	$(ARCHIVE_TOOL) rcs $(OBJ_DIR)lib$(LIB_NAME).a $(LIB_OBJECTS) 

#building tests
tests: $(TEST_FILENAMES) build_tests

$(TEST_FILENAMES):
	$(BUILD_TOOL) $(HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(TEST_SOURCES_DIR)$@.cpp $(PROFILE_FLAGS)

build_tests:
	$(BUILD_TOOL) -o $(OBJ_DIR)$(TEST_NAME) $(ADD_LIBRARIES_DIR) -L$(OBJ_DIR) -lpthread $(TEST_OBJECTS) -l$(LIB_NAME) $(ADD_LIBRARIES) $(PROFILE_FLAGS) 
		
#execute tests
run_tests:
	$(OBJ_DIR)$(TEST_NAME)
	gprof $(OBJ_DIR)$(TEST_NAME) gmon.out > profileReport.txt
