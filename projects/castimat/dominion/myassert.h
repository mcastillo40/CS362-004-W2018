#include <stdlib.h>
#include <stdio.h>

void myAssert(int numA, int numB, int *passed) {
	if (numA != numB) {
        *passed = 0; 
    }
}

