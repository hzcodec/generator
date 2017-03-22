/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-22
    File         : filter.c
    Reference    : -
    Description  : -
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "frame1.h"

static float new = 0.0;
static float last = 0.0;
 
void Filter__filter(float *ar, struct Generator *gen)
{
        FILE *fp;
        fp = fopen("filter.txt", "w");

        for(int n=0; n<gen->numberOfSamples; n++)
        {
	        //printf("%s() - alpha: %.4f, ar[%d]: %.4f\n", __func__, gen->alpha, n, ar[n]);
                new = ar[n];
                new = last + gen->alpha*(new - last);

                fprintf(fp, "%.4f\n", new);
                last = new;
        }

	fclose(fp);
}

 
