.PHONY: all, val, clean, test

a.out: snp.c
	gcc -O0 -g snp.c

val: a.out
	export PATH=\$PATH:`pwd`
	valgrind a.out 15

clean:
	rm a.out

test: a.out
	./a.out 15
