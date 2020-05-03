all:
	gcc -c catcher.c -Wall -Wextra
	gcc -o catcher catcher.c -lm
	gcc catcher.c -o catcher -lm

catcher: 
	gcc -c catcher.c -Wall -Wextra
	gcc -o catcher catcher.c -lm
	gcc catcher.c -o catcher -lm
clean: 
	rm catcher catcher.o