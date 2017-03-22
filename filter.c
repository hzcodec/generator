/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-22
    File         : filter.c
    Reference    : -
    Description  : -
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "frame1.h"
#include "common.h"
#include "filter.h"


void Filter__find_max_filter_value(struct TriggerPoint *tp, float val, int n)
{
 	if (val > tp->maxValue)
	{
		tp->maxValue = val;
		tp->idx = n;
		//printf("%s() - max:%.2f, idx:%d\n", __func__, tp->maxValue, tp->idx);
	}
}

void Filter__find_max_input_value(struct TriggerPoint *tp, float val, int n)
{
 	if (val > tp->maxValue)
	{
		tp->maxValue = val;
		tp->idx = n;
		//printf("%s() - max:%.2f, idx:%d\n", __func__, tp->maxValue, tp->idx);
	}
}

void Filter__filter(float *ar, struct Generator *gen, char *s)
{
        FILE *fp;

        float new = 0.0;
        float last = 0.0;
	struct TriggerPoint inputTp = {0.0, 0};
	struct TriggerPoint filterTp = {0.0, 0};
 
        fp = fopen(s, "w");

        Common__fprintProperties(fp, gen);

        for(int n=0; n<gen->numberOfSamples; n++)
        {
	        //printf("%s() - alpha: %.4f, ar[%d]: %.4f, new: %.4f\n", __func__, gen->alpha, n, ar[n], new);

		Filter__find_max_input_value(&inputTp, ar[n], n);
                new = ar[n];
                new = last + gen->alpha*(new - last);
		Filter__find_max_filter_value(&filterTp, new, n);

                fprintf(fp, "%.4f\n", new);
                last = new;
        }

        //float trigLevel = tp.maxValue * 0.75;
	printf("'%s' created, Max input value: %.1f at index: %d, Max filter value: %.1f at index: %d\n", s, inputTp.maxValue, inputTp.idx, filterTp.maxValue, filterTp.idx);

	fclose(fp);
}

 
