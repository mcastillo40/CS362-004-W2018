CFLAGS = -Wall -fpic -coverage -lm

default: prog

prog:
	gcc -o testme testme.c -g $(CFLAGS)
	#./testme >> unittestresult.out
	#gcov testme.c -b >> unittestresult.out
	#cat testme.c.gcov >> unittestresult.out
		
clean:
	rm prog

cleanall: 
	rm prog 