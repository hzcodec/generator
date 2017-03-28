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
#include "frame1.h"


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

        float trigLevel = inputTp.maxValue * 0.75;
	if (filterTp.maxValue > trigLevel)
	{
	        printf("%s%sMax level reached: %.1f%s\n", BOLD, RED, trigLevel, NRM);
	}

	printf("'%s' created\n", s);
	printf("Max input value: %.1f at index: %d, Max filter value: %.1f at index: %d\n", inputTp.maxValue, inputTp.idx, filterTp.maxValue, filterTp.idx);

	fclose(fp);
}

#define NUMBER_OF_SAMPLES 512
void Filter__filter_real_data(int sel, struct Generator *gen)
{
        FILE *fpIn;
        FILE *fpOut;
        float ar[NUMBER_OF_SAMPLES];  // array holding sample values
        char fileText[10];
	int idx = 0;
        float new = 0.0;
        float last = 0.0;

	switch (sel)
	{
		case 1:
                	fpIn = fopen("realdata.txt", "r");
                        printf("realdata.txt opened\n");
			break;
		case 2:
                	fpIn = fopen("forceA1001_StuckDeadRope50kg.txt", "r");
                        fpOut = fopen("filtered_StuckDeadRope50kg.txt", "w");
                        printf("forceA1001_StuckDeadRope50kg.txt opened\n");
			break;
		case 3:
                	fpIn = fopen("forceA1001_StuckDeadRope150kg.txt", "r");
                        fpOut = fopen("filtered_StuckDeadRope150kg.txt", "w");
                        printf("forceA1001_StuckDeadRope150kg.txt opened\n");
			break;
		default:
                	fpIn = fopen("realdata.txt", "r");
			break;
	}

        while(fgets(fileText, 10, fpIn) != NULL)
        {
            ar[idx] = atof(fileText);
            idx++;
        }

        printf("\n*** %d numbers of Real indata read ***\n", idx);
	gen->type = REAL;

        Common__fprintProperties(fpOut, gen);

        for(int n=0; n<NUMBER_OF_SAMPLES; n++)
        {
                new = ar[n];
                new = last + gen->alpha*(new - last);

                fprintf(fpOut, "%.4f\n", new);
                last = new;
        }

	printf("'Filtered data created with alpha. %.4f\n", gen->alpha);

	fclose(fpIn);
	fclose(fpOut);
}
