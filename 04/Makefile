.PHONY: clean all
	
all: a.out

a.out: tea.c
	gcc tea.c

clean:
	rm -f a.out
	rm -f results.txt

golden: golden.txt

golden.txt:
	rm -f golden.txt
	cp results.txt golden.txt

test: results.txt a.out
	
results.txt: test.sh
	./test.sh > results.txt

diff: golden.txt results.txt
	diff golden.txt results.txt
