CFLAGS= -Wall -g -fpic -coverage -lm -std=c99

test: testme.c
	gcc -o testme testme.c $(CFLAGS)

runtest: test
	./testme &> testresults.out


all: test runtest 

clean:
	rm -f *.o testme.exe  *.gcov *.gcda *.gcno *.so *.out
