CXX=g++
CXX_EXT=cxx
LDFLAGS=$(shell Magick++-config --ldflags --libs)
CXXFLAGS=-g -std=c++11 -Wall -pedantic -O2 $(shell Magick++-config --cxxflags --cppflags)
BIN_EN=encr
BIN_DE=decr
SRC_EN=$(BIN_EN).$(CXX_EXT)
SRC_DE=$(BIN_DE).$(CXX_EXT)

.PHONY: all, clean

all: $(BIN_EN) $(BIN_DE)

$(BIN_DE):
	$(CXX) $(CXXFLAGS) $(SRC_DE) $(LDFLAGS) -o $(BIN_DE)

$(BIN_EN):
	$(CXX) $(CXXFLAGS) $(SRC_EN) $(LDFLAGS) -o $(BIN_EN)

clean:
	rm -f $(BIN_EN)
	rm -f $(BIN_DE)
