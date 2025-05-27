# Compilation variables
CXX = g++
CXXFLAGS = -Wall -Wextra -fdiagnostics-color=always -g -std=c++20 -Iinclude -mconsole -static-libgcc -static-libstdc++
DLLFLAGS = -shared -Wl,--out-implib,$(OUT_LIB)

# Directories
OUT_DIR = build
OOP3_DIR = tests/OOP3
DIST_DIR = dist

# DLL build destinations
OUT_OBJ  = $(OUT_DIR)/Vector.o
OUT_DLL  = $(OUT_DIR)/Vector.dll
OUT_LIB  = $(OUT_DIR)/Vector.a

# Tests' build destinations
TEST_UNIT     = $(OUT_DIR)/unit_test.exe
TEST_PUSHBACK = $(OUT_DIR)/pushback_test.exe

# Implementation build destinations
TEST_TIME_STD   = $(OUT_DIR)/time_std.exe
TEST_TIME_CUSTM = $(OUT_DIR)/time_custm.exe
MAIN_STD        = $(OUT_DIR)/OOP3_std.exe
MAIN_CUSTM      = $(OUT_DIR)/OOP3_custm.exe

# Distributable build destination
DIST = $(DIST_DIR)/OOP3.exe


all: $(OUT_DIR) $(OUT_DLL) $(TEST_UNIT) $(TEST_PUSHBACK)

main: custm std 


# Distributable building

$(DIST_DIR)/manifest:
	mkdir -p $(DIST_DIR)/manifest

$(DIST_DIR)/manifest/admin.res: $(DIST_DIR)/manifest/admin.rc | $(DIST_DIR)/manifest
	windres $< -O coff -o $@

dist: $(OUT_DIR) $(OUT_DLL) $(OOP3_DIR)/OOP3.cpp $(OOP3_DIR)/lib/*.cpp $(DIST_DIR)/manifest/admin.res
	$(CXX) $(CXXFLAGS) -DUSE_CUSTOM_VECTOR -o $(DIST) $(OOP3_DIR)/OOP3.cpp $(OOP3_DIR)/lib/*.cpp $(DIST_DIR)/manifest/admin.res -L$(OUT_DIR) -lVector


# Main DLL building ( + Unit Tests)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DLL): src/Vector.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(DLLFLAGS) -DBUILDING_VECTOR -o $(OUT_DLL) src/Vector.cpp

$(TEST_UNIT): tests/vector_tests.cpp tests/catch_amalgamated.cpp $(OUT_DLL) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_UNIT) tests/vector_tests.cpp tests/catch_amalgamated.cpp -L$(OUT_DIR) -lVector

$(TEST_PUSHBACK): $(OOP3_DIR)/pushback_test.cpp $(OOP3_DIR)/lib/*.cpp $(OUT_DLL) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_PUSHBACK) $(OOP3_DIR)/pushback_test.cpp $(OOP3_DIR)/lib/*.cpp -L$(OUT_DIR) -lVector


# Implementations (std vs custm) building

std: $(OOP3_DIR)/OOP3.cpp $(OOP3_DIR)/lib/*.cpp std_test | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(MAIN_STD) $(OOP3_DIR)/OOP3.cpp $(OOP3_DIR)/lib/*.cpp

std_test: $(OOP3_DIR)/time_test.cpp $(OOP3_DIR)/lib/*.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_TIME_STD) $(OOP3_DIR)/time_test.cpp $(OOP3_DIR)/lib/*.cpp

custm: $(OOP3_DIR)/OOP3.cpp $(OOP3_DIR)/lib/*.cpp $(OUT_DLL) custm_test | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -DUSE_CUSTOM_VECTOR -o $(MAIN_CUSTM) $(OOP3_DIR)/OOP3.cpp $(OOP3_DIR)/lib/*.cpp -L$(OUT_DIR) -lVector

custm_test: $(OOP3_DIR)/time_test.cpp $(OOP3_DIR)/lib/*.cpp $(OUT_DLL) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -DUSE_CUSTOM_VECTOR -o $(TEST_TIME_CUSTM) $(OOP3_DIR)/time_test.cpp $(OOP3_DIR)/lib/*.cpp -L$(OUT_DIR) -lVector


# Clean all build results

clean:
	rm -rf $(OUT_DIR) $(DIST) $(DIST_DIR)/Output $(DIST_DIR)/manifest/admin.res