NAME1=sort
NAME2=equal
CXX=g++
CXX_FLAGS=-std=c++11
CXX_EXT=.cxx

.PHONY: all clean

all: clean $(NAME1) $(NAME2)

$(NAME1):
	$(CXX) $(CXX_FLAGS) $(NAME1)$(CXX_EXT) -o $(NAME1)

$(NAME2):
	$(CXX) $(CXX_FLAGS) $(NAME2)$(CXX_EXT) -o $(NAME2)

clean:
	rm -f $(NAME1)
	rm -f $(NAME2)
