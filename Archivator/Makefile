export profile?=F
.NOTPARALLEL:

# defining variables
BUILD_TOOL = g++
ARCHIVE_TOOL = ar

COMPILE_FLAGS = -c -Wall -Werror
PROFILE_FLAGS = 
ifeq ($(profile) ,yes)
PROFILE_FLAGS = -pg
endif

STORE_EXE_NAME = StoreFolderLauncher
STORE_EXE_SOURCES_DIR = ./src/$(STORE_EXE_NAME)/

RESTORE_EXE_NAME = RestoreFolderLauncher
RESTORE_EXE_SOURCES_DIR = ./src/$(RESTORE_EXE_NAME)/

FS_LIB_NAME = FolderSnapshotLib
FS_LIB_SOURCES_DIR = ./src/$(FS_LIB_NAME)/
FS_HEADER_DIR = $(FS_LIB_SOURCES_DIR)/

BW_LIB_NAME = BurrowsWheelerLib
BW_LIB_SOURCES_DIR = ./src/$(BW_LIB_NAME)/
BW_HEADER_DIR = $(BW_LIB_SOURCES_DIR)/h/

FS_TEST_NAME = FolderSnapshotTest
FS_TEST_SOURCES_DIR = ./test/$(FS_TEST_NAME)/

BW_TEST_NAME = BurrowsWheelerTest
BW_TEST_SOURCES_DIR = ./test/$(BW_TEST_NAME)/

OBJ_DIR = ./obj/

ADD_LIBRARIES_DIR = -L./lib/
#ADD_LIBRARIES = -lgtest_main
ADD_LIBRARIES = -lgmock_main

ADD_HEADERS_DIR = ./include/

BOOST_INCLUDE_DIR = ./../boost/include/
BOOST_LIBRARIES_DIR = ./../boost/lib/
ADD_BOOST_LIBRARIES = -lboost_filesystem -lboost_system -lboost_program_options

# FolderSnapshotLib objects
FS_LIB_SOURCES = $(wildcard $(FS_LIB_SOURCES_DIR)*.cpp)
FS_LIB_OBJECTS = $(subst $(FS_LIB_SOURCES_DIR),$(OBJ_DIR),$(FS_LIB_SOURCES:%.cpp=%.o))
FS_LIB_FILENAMES = $(subst $(FS_LIB_SOURCES_DIR),,$(FS_LIB_SOURCES:%.cpp=%))

# BurrowsWheelerLib objects
BW_LIB_SOURCES = $(wildcard $(BW_LIB_SOURCES_DIR)*.cpp)
BW_LIB_OBJECTS = $(subst $(BW_LIB_SOURCES_DIR),$(OBJ_DIR),$(BW_LIB_SOURCES:%.cpp=%.o))
BW_LIB_FILENAMES = $(subst $(BW_LIB_SOURCES_DIR),,$(BW_LIB_SOURCES:%.cpp=%))

# BW tests objects
BW_TEST_SOURCES = $(wildcard $(BW_TEST_SOURCES_DIR)*.cpp)
BW_TEST_OBJECTS = $(subst $(BW_TEST_SOURCES_DIR),$(OBJ_DIR),$(BW_TEST_SOURCES:%.cpp=%.o))
BW_TEST_FILENAMES = $(subst $(BW_TEST_SOURCES_DIR),,$(BW_TEST_SOURCES:%.cpp=%))

# FS tests objects
FS_TEST_SOURCES = $(wildcard $(FS_TEST_SOURCES_DIR)*.cpp)
FS_TEST_OBJECTS = $(subst $(FS_TEST_SOURCES_DIR),$(OBJ_DIR),$(FS_TEST_SOURCES:%.cpp=%.o))
FS_TEST_FILENAMES = $(subst $(FS_TEST_SOURCES_DIR),,$(FS_TEST_SOURCES:%.cpp=%))

# Store Folder objects
STORE_EXE_SOURCES = $(wildcard $(STORE_EXE_SOURCES_DIR)*.cpp)
STORE_EXE_OBJECTS = $(subst $(STORE_EXE_SOURCES_DIR),$(OBJ_DIR),$(STORE_EXE_SOURCES:%.cpp=%.o))
STORE_EXE_FILENAMES = $(subst $(STORE_EXE_SOURCES_DIR),,$(STORE_EXE_SOURCES:%.cpp=%))

# Restore Folder objects
RESTORE_EXE_SOURCES = $(wildcard $(RESTORE_EXE_SOURCES_DIR)*.cpp)
RESTORE_EXE_OBJECTS = $(subst $(RESTORE_EXE_SOURCES_DIR),$(OBJ_DIR),$(RESTORE_EXE_SOURCES:%.cpp=%.o))
RESTORE_EXE_FILENAMES = $(subst $(RESTORE_EXE_SOURCES_DIR),,$(RESTORE_EXE_SOURCES:%.cpp=%))

# labels definition
all: clean $(BW_LIB_NAME) $(FS_LIB_NAME) $(BW_TEST_NAME) $(FS_TEST_NAME) run_BW_tests run_FS_tests $(STORE_EXE_NAME) $(RESTORE_EXE_NAME)
.PHONY: all $(BW_LIB_NAME) $(FS_LIB_NAME) $(BW_TEST_NAME) $(FS_TEST_NAME) run_BW_tests run_FS_tests $(STORE_EXE_NAME) $(RESTORE_EXE_NAME)

clean:
	rm -r -f $(OBJ_DIR)
	mkdir $(OBJ_DIR)

#building BurrowsWheelerLib
$(BW_LIB_NAME): $(BW_LIB_FILENAMES) build_BW_lib

$(BW_LIB_FILENAMES):
	$(BUILD_TOOL) -I$(BW_HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(BW_LIB_SOURCES_DIR)$@.cpp $(PROFILE_FLAGS)

build_BW_lib:
	$(ARCHIVE_TOOL) rcs $(OBJ_DIR)lib$(BW_LIB_NAME).a $(BW_LIB_OBJECTS)

#building FolderSnapshotLib
$(FS_LIB_NAME): $(FS_LIB_FILENAMES) build_FS_lib

$(FS_LIB_FILENAMES):
	$(BUILD_TOOL) -I$(FS_HEADER_DIR) -I$(BOOST_INCLUDE_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(FS_LIB_SOURCES_DIR)$@.cpp $(PROFILE_FLAGS)

build_FS_lib:
	$(ARCHIVE_TOOL) rcs $(OBJ_DIR)lib$(FS_LIB_NAME).a $(FS_LIB_OBJECTS)

#building BW tests
$(BW_TEST_NAME): $(BW_TEST_FILENAMES) build_BW_tests

$(BW_TEST_FILENAMES):
	$(BUILD_TOOL) -I$(ADD_HEADERS_DIR) -I$(BW_HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(BW_TEST_SOURCES_DIR)$@.cpp $(PROFILE_FLAGS)

build_BW_tests:
	$(BUILD_TOOL) -lpthread -o $(OBJ_DIR)$(BW_TEST_NAME) $(BW_TEST_OBJECTS) $(ADD_LIBRARIES_DIR) $(ADD_LIBRARIES) -L$(OBJ_DIR) -l$(BW_LIB_NAME) $(PROFILE_FLAGS)

#execute tests
run_BW_tests:
	$(OBJ_DIR)$(BW_TEST_NAME)
	#gprof $(OBJ_DIR)$(BW_TEST_NAME) gmon.out > profileBWReport.txt

#building FS tests
$(FS_TEST_NAME): $(FS_TEST_FILENAMES) build_FS_tests

$(FS_TEST_FILENAMES):
	$(BUILD_TOOL) -I$(ADD_HEADERS_DIR) -I$(FS_HEADER_DIR) -I$(BOOST_INCLUDE_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)$@.o $(FS_TEST_SOURCES_DIR)$@.cpp $(PROFILE_FLAGS)

build_FS_tests:
	$(BUILD_TOOL) -lpthread -o $(OBJ_DIR)$(FS_TEST_NAME) $(FS_TEST_OBJECTS) $(ADD_LIBRARIES_DIR) $(ADD_LIBRARIES) -L$(OBJ_DIR) -L$(BOOST_LIBRARIES_DIR) $(ADD_BOOST_LIBRARIES) -l$(FS_LIB_NAME) $(PROFILE_FLAGS)

#execute tests
run_FS_tests:
	$(OBJ_DIR)$(FS_TEST_NAME)
	#gprof $(OBJ_DIR)$(FS_TEST_NAME) gmon.out > profileFSReport.txt

#build StoreFolderLauncher
$(STORE_EXE_NAME): 
	$(BUILD_TOOL) -I$(BOOST_INCLUDE_DIR) -I$(FS_HEADER_DIR) -I$(BW_HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)main.o $(STORE_EXE_SOURCES_DIR)main.cpp $(PROFILE_FLAGS)
	$(BUILD_TOOL) -lpthread -o $(OBJ_DIR)$(STORE_EXE_NAME) $(STORE_EXE_OBJECTS) -L$(OBJ_DIR) -L$(BOOST_LIBRARIES_DIR) -l$(BW_LIB_NAME) -l$(FS_LIB_NAME) $(ADD_BOOST_LIBRARIES) $(PROFILE_FLAGS)

#build RestoreFolderLauncher
$(RESTORE_EXE_NAME):
	$(BUILD_TOOL) -I$(BOOST_INCLUDE_DIR) -I$(FS_HEADER_DIR) -I$(BW_HEADER_DIR) $(COMPILE_FLAGS) -o $(OBJ_DIR)main.o $(RESTORE_EXE_SOURCES_DIR)main.cpp $(PROFILE_FLAGS)
	$(BUILD_TOOL) -lpthread -o $(OBJ_DIR)$(RESTORE_EXE_NAME) $(RESTORE_EXE_OBJECTS) -L$(OBJ_DIR) -L$(BOOST_LIBRARIES_DIR) -l$(BW_LIB_NAME) -l$(FS_LIB_NAME) $(ADD_BOOST_LIBRARIES) $(PROFILE_FLAGS)
