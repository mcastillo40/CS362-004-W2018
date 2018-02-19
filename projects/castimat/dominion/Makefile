CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard1.out: dominion.o rngs.o 
	echo "RESULT FOR RUNNING COUNCIL ROOM RANDOM TEST:" > randomtestcard1.out
	
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtest -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtest >> randomtestcard1.out
	gcov randomtestcard1.c -b >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out
	cat randomtestcard1.out

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtest2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestcard2.out: dominion.o rngs.o randomtest2
	echo "RESULT FOR RUNNING SMITHY RANDOM TEST:" > randomtestcard2.out
	
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtest2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtest2 >> randomtestcard2.out
	gcov randomtestcard2.c -b >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out
	cat randomtestcard2.out

randomtest3: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtest3 -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: dominion.o rngs.o randomtest3
	echo "RESULT FOR RUNNING ADVENTURER RANDOM TEST:" > randomtestadventurer.out
	
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtest3 -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtest3 >> randomtestadventurer.out
	gcov randomtestadventurer.c -b >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	cat randomtestadventurer.out

all: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
