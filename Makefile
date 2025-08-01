C = /opt/homebrew/opt/llvm/bin/clang
SDK_PATH = $(shell xcrun --show-sdk-path)
CXXFLAGS = -std=c++20 -fsanitize=address,leak -shared-libasan -g -isysroot $(SDK_PATH) -stdlib=libc++

disas:
	$(C) -o disassemble ./disassembler/disassembler.c

test_no_debug:
	$(CXX) -std=c++20 -g -o testcode testcode.cpp

tutorial:
	$(CXX) -std=c++20 -g -o tutorial tutorial.cpp
