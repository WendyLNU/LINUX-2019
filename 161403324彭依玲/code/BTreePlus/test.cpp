//
//  main.c
//  BPlusTree
//
//  Created by Wuyixin on 2017/8/4.
//  Copyright ? 2017ƒÍ Coding365. All rights reserved.
//
 
#include <stdio.h>
#include <time.h>
#include "BTreePlus1.h"
 
int main(int argc, const char * argv[]) {
    int i;
    BPlusTree T;
    T = Initialize();
    
    clock_t c1 = clock();
    i = 100;
    while (i > 0)
        T = Insert(T, i--);
   /* i = 5000001;
    while (i < 10000000)
       T = Insert(T, i++);
    */
    i = 100;
    while (i > 20)
        T = Remove(T, i--);
    Travel(T);
    TravelData(T);
    Destroy(T);
    
    clock_t c2 = clock();
    
    printf("\n”√ ±£∫ %lu√Î\n",(c2 - c1)/CLOCKS_PER_SEC);
	return 0;
}
