CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)

prog: testme
	./testme &> unittestresult.out
	gcov testme.c -b >> unittestresult.out
	cat testme.c.gcov >> unittestresult.out
		
clean:
	rm prog

cleanall: 
	rm prog 