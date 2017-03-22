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
	        // printf("%s() - ar[%d]: %.4f\n", __func__, n, ar[n]);
                new = ar[n];
                //new = last + gen->alpha*(new - last);
                new = last + 0.01*(new - last);

                fprintf(fp, "%.4f\n", new);
                last = new;
        }

	fclose(fp);
}

 
