/*
 * Copyright (C) 2009-2014 dubin(db@dubin.me). All rights reserved.
 *
 *
 * changed log:
 *      date: 2014-04-09 clean code.
 *      
 *      可以优化的地方: 在每一轮移动队首元素中，ls 数组可以不用重复产生。
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
description: 对1...COUNT 的全排列.

0              1
1             21  (12)
2            321   (231 213)
3          4321 3421  3241 3214
4	    54321 45321 ....
5 	  654321 564321 ....
6     7654321 6754321 ....
7    87654321 78654321 ....	

*/

static long int g_insert_cnt = 0;

static void clean(int *ls, int len) {
    int i = 0;
    for (; i < len; i++) 
        ls[i] = 0;
}

static void display(char *msg, int *ls, int len) {
    int i = 0;
    printf("%s ", msg);
    for (; i < len; i++) {
        printf("%d ", ls[i]);
    }
    printf("\n");

}

static void insert(int *ls, int len, int pos, int value) {
    int i = len - 1;
    for (; i >= pos; i--) {
        ls[i+1] = ls[i];
    }
    ls[pos] = value;

    g_insert_cnt ++;
}

static int test_continue(int *steps) {
    return steps[0] == 0 ? 0 : 1; 
}

static int incr_step(int *steps, int pos) {
    if (pos == 0) {
        steps[0] = 1;   
        return;
    }
    
    int intge;
    int i = pos;
    for (; i > 0; i--) {
        steps[i]++;
        intge = steps[i] / (i+1);
        steps[i] = steps[i] % (i+1);
        if (intge == 0) break;
    }

    if (intge != 0) {
        steps[0] = 1;
    }
}

static void get_list(int *ls, int len, int *steps, int p) {
    int i = 1;

    clean(ls, len);
    ls[0] = 1;
    if(p == 0) {
    } else {
        for(; i <= p; i++) {
            insert(ls, len, steps[i], i + 1);
        }
    }
}

static int compute(int limited) {
    if (limited <= 0 ) {
        printf("Max number must greater than 0.\n");
        return -1;
    }

    int *ls = (int*)malloc(sizeof(int) * (limited + 1));
    if (NULL == ls) return -2;  
    
    int *steps = (int *)malloc(sizeof(int) * (limited + 1));
    if (NULL == steps) {
        free(ls);
        return -2;
    }

    int cnt = 0;
    clean(steps, limited);
    while(test_continue(steps) == 0) {
        get_list(ls, limited, steps, limited - 1);
        display("", ls, limited);
        incr_step(steps, limited - 1);
        cnt ++;
    }
    
    free(ls);
    free(steps);
    return cnt;
}

static int cals(int limit)
{
    if (limit == 1) return limit;
    return cals(limit - 1) * limit;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Error: please give a limited number.\n");
        return 0;
    }

    int limited = atoi(argv[1]);
    int total_line = 0;
    if ((total_line = compute(limited)) >= 0) {
        printf("\nExpect line:%d\n", cals(limited));
        printf("Real   line:%d\n", total_line);
        printf("Real insert counts:%d\n", g_insert_cnt);
    }

    return 0;
}
