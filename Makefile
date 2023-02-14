hard: vocab.c
	clear;cc -o vocab -std=c99 -Wall -Werror vocab.c

easy: vocab.c
	clear;cc -g -o vocab -std=c99 vocab.c

valgrind: ./vocab
	clear;valgrind -s ./vocab

purgecore:
	rm vgcore*

clean: $(HOME)/.local/bin/vocab
	rm $(HOME)/.local/bin/vocab

install: ./vocab
	cc -o vocab -std=c99 -Wall -Werror vocab.c
	cp ./vocab $(HOME)/.local/bin/vocab
