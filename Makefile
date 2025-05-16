CXX = g++
CXXFLAGS = -Wall -Wextra -fdiagnostics-color=always -g -Os -std=c++20 -Iinclude -mconsole
OUT_DIR=build
OUT_DLL=$(OUT_DIR)/Vector.dll
OUT_LIB=$(OUT_DIR)/Vector.lib
OUT_TEST=$(OUT_DIR)/tests.exe
OOP3_DIR=OOP3
DLLFLAGS=-shared -static-libgcc -static-libstdc++ -Wl,--out-implib,$(OUT_LIB)

all: $(OUT_DIR) $(OUT_DLL) test_unit test_time

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(OUT_DIR)/Vector.o: src/Vector.cpp include/Vector.hpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR)/Vector.o

$(OUT_DLL): $(OUT_DIR)/Vector.o | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(DLLFLAGS) $(OUT_DIR)/Vector.o -o $(OUT_DLL)

test_unit: tests/catch_amalgamated.cpp tests/vector_tests.cpp $(OUT_LIB) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) tests/catch_amalgamated.cpp tests/vector_tests.cpp $(OUT_LIB) -o $(OUT_TEST)

main_std: $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o build/OOP3_std.exe $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp)

main_vector: $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o build/OOP3_vector.exe $(OOP3_DIR)/OOP3.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp)

test_time: $(OOP3_DIR)/time_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) $(OUT_LIB) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o build/time_test.exe $(OOP3_DIR)/time_test.cpp $(wildcard $(OOP3_DIR)/lib/*.cpp) $(OUT_LIB)

clean:
	if exist "$(OUT_DIR)" rmdir /S /Q "$(OUT_DIR)"