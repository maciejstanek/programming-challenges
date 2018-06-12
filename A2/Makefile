NAME=template_sandbox
CXX=g++
CXX_FLAGS=-std=c++11
CXX_EXT=.cxx

.PHONY: all clean

all: clean $(NAME)

$(NAME):
	$(CXX) $(CXX_FLAGS) $(NAME)$(CXX_EXT) -o $(NAME)

clean:
	rm -f $(NAME)
