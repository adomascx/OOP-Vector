CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -fdiagnostics-color=always -g -std=c++20 -Iinclude -mconsole
DLLFLAGS=-shared -Wl,--out-implib,$(OUT_LIB)

OUT_DIR=build
OOP3_DIR=tests/OOP3

OUT_OBJ = $(OUT_DIR)/Vector.o
OUT_DLL = $(OUT_DIR)/Vector.dll
OUT_LIB = $(OUT_DIR)/Vector.a

TEST_UNIT = $(OUT_DIR)/vector/unit_test.exe
TEST_PUSHBACK = $(OUT_DIR)/vector/pushback_test.exe

TEST_TIME_STD = $(OUT_DIR)/std/time.exe
TEST_TIME_CUSTM = $(OUT_DIR)custm/time.exe
MAIN_STD = $(OUT_DIR)/std/OOP3.exe
MAIN_CUSTM = $(OUT_DIR)/custm/OOP3.exe

all: $(OUT_DIR) $(OUT_DLL) $(TEST_UNIT) $(TEST_PUSHBACK)

main: std custm

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(OUT_DLL): src/Vector.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(DLLFLAGS) -DBUILDING_VECTOR -o $(OUT_DLL) src/Vector.cpp

$(TEST_UNIT): tests/vector_tests.cpp tests/catch_amalgamated.cpp $(OUT_DLL) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_UNIT) tests/vector_tests.cpp tests/catch_amalgamated.cpp -L$(OUT_DIR) -lVector

$(TEST_PUSHBACK): $(OOP3_DIR)/pushback_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) $(OUT_DLL) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_PUSHBACK) $(OOP3_DIR)/pushback_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) -L$(OUT_DIR) -lVector


std: $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) std_test | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(MAIN_STD) $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp)

std_test: $(OOP3_DIR)/time_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_TIME_STD) $(OOP3_DIR)/time_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp)

custm: $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) $(OUT_DLL) custm_test | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -DUSE_CUSTOM_VECTOR -o $(MAIN_CUSTM) $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) -L$(OUT_DIR) -lVector

custm_test: $(OOP3_DIR)/time_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) $(OUT_DLL) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -DUSE_CUSTOM_VECTOR -o $(TEST_TIME_CUSTM) $(OOP3_DIR)/time_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) -L$(OUT_DIR) -lVector

clean:
	if exist "$(OUT_DIR)" rmdir /S /Q "$(OUT_DIR)"