CXX = g++
CXXFLAGS = -Wall -Wextra -fdiagnostics-color=always -g -Os -std=c++20 -Iinclude -mconsole
OUT_DIR=build
OUT_DLL=$(OUT_DIR)/Vector.dll
OUT_LIB=$(OUT_DIR)/Vector.lib
OUT_TEST=$(OUT_DIR)/tests.exe
DLLFLAGS=-shared -static-libgcc -static-libstdc++ -Wl,--out-implib,$(OUT_LIB)

all: $(OUT_DIR) $(OUT_DLL) $(OUT_TEST)

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(OUT_DIR)/Vector.o: src/Vector.cpp include/Vector.hpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR)/Vector.o

$(OUT_DLL): $(OUT_DIR)/Vector.o | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(DLLFLAGS) $(OUT_DIR)/Vector.o -o $(OUT_DLL)

$(OUT_TEST): tests/catch_amalgamated.cpp tests/vector_tests.cpp $(OUT_LIB) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) tests/catch_amalgamated.cpp tests/vector_tests.cpp $(OUT_LIB) -o $(OUT_TEST)

docs:
	doxygen docs/Doxyfile

clean:
	if exist "$(OUT_DIR)" rmdir /S /Q "$(OUT_DIR)"
