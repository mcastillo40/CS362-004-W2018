CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestresult: randomtestadventurer randomtestcard1 randomtestcard2
	echo "Result for running Assignment 4 Dominion tests - randomtestadventurer:" > randomtestadventurer.out
	
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	echo "randomtestadventurer.c Coverage: " >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	echo "randomtestadventurer.c Branch Coverage: " >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	echo "randomtestadventurer.c Not Covered: " >> randomtestadventurer.out
	grep '####' dominion.c.gcov >> randomtestadventurer.out
	echo -e "END unittest1.c \n\n" >> randomtestadventurer.out
	
	echo "Result for running Assignment 4 Dominion tests - randomtestcard1:" > randomtestcard1.out

	echo "randomtestcard1.c:" >> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	echo "randomtestcard1.c Coverage: " >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	echo "randomtestcard1.c Branch Coverage: " >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	echo "randomtestcard1.c Not Covered: " >> randomtestcard1.out
	grep '####' dominion.c.gcov >> randomtestcard1.out
	echo -e "END unittest1.c \n\n" >> randomtestcard1.out

	echo "Result for running Assignment 4 Dominion tests - randomtestcard2:" > randomtestcard2.out

	echo "randomtestcard2.c:" >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	echo "randomtestcard2.c Coverage: " >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	echo "randomtestcard2.c Branch Coverage: " >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	echo "randomtestcard2.c Not Covered: " >> randomtestcard2.out
	grep '####' dominion.c.gcov >> randomtestcard2.out
	echo -e "END unittest1.c \n\n" >> randomtestcard2.out
	
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)	

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)	

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)	
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	
unittestresult.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Result for running Assignment 3 Dominion tests:" > unittestresult.out
	
	echo "unittest1.c:" >> unittestresult.out
	./unittest1 >> unittestresult.out
	echo "unittest1.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "unittest1.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "unittest1.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END unittest1.c \n\n" >> unittestresult.out
	
	echo "unittest2.c:" >> unittestresult.out
	./unittest2 >> unittestresult.out
	echo "unittest2.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "unittest2.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "unittest2.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END unittest2.c \n\n" >> unittestresult.out
	
	echo "unittest3.c:" >> unittestresult.out
	./unittest3 >> unittestresult.out
	echo "unittest3.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "unittest3.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "unittest3.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END unittest3.c \n\n" >> unittestresult.out
	
	
	echo "unittest4.c:" >> unittestresult.out
	./unittest4 >> unittestresult.out
	echo "unittest4.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "unittest4.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "unittest4.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END unittest4.c \n\n" >> unittestresult.out
	
	echo "cardtest1.c:" >> unittestresult.out
	./cardtest1 >> unittestresult.out
	echo "cardtest1.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "cardtest1.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "cardtest1.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END cardtest1.c \n\n" >> unittestresult.out
	
	echo "cardtest2.c:" >> unittestresult.out
	./cardtest2 >> unittestresult.out
	echo "cardtest2.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "cardtest2.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "cardtest2.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END cardtest2.c \n\n" >> unittestresult.out
	
	echo "cardtest3.c:" >> unittestresult.out
	./cardtest3 >> unittestresult.out
	echo "cardtest3.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "cardtest3.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "cardtest3.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END cardtest3.c \n\n" >> unittestresult.out
	
	echo "cardtest4.c:" >> unittestresult.out
	./cardtest4 >> unittestresult.out
	echo "cardtest4.c Coverage: " >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	echo "cardtest4.c Branch Coverage: " >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	echo "cardtest4.c Not Covered: " >> unittestresult.out
	grep '####' dominion.c.gcov >> unittestresult.out
	echo -e "END cardtest4.c \n\n" >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer randomtestcard1 randomtestcard2 unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
