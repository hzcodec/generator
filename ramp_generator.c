/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-19
    File         : ramp_generator.c
    Reference    : -
    Description  : -
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frame1.h"
#include "common.h"
 
float* Ramp_generator__generate_ramp(struct Generator* self)
{
	printf("%s() - \n", __func__);
        FILE *fp;
	float yVal;
	float noise = 0.0;
	float part;
	float minValue = 1;
	int   rampStartValue = 0.1 * self->numberOfSamples; // start condition 10% of max samples
	int   idx;

        float *ar = (float *)malloc(sizeof(float) * self->numberOfSamples);    
        fp = fopen("ramp_samples.txt", "w");

        for (int i=0; i<rampStartValue; i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                //noise = rand_interval(self->minNoise, self->maxNoise);
	    }
	    fprintf(fp, "%.4f\n", minValue + noise);
	    ar[i] = minValue + noise;
	}

	switch(self->rampSlopeType)
	{
	    case 0: idx = (int)(0.25*(float)self->numberOfSamples);
	            printf("%s() - Ramp type:%d, idx:%d\n", __func__, self->rampSlopeType, idx);
		    break;
	    case 1: idx = (int)(0.25*(float)self->numberOfSamples);
		    break;
	    case 2: idx = (int)(0.50*(float)self->numberOfSamples);
		    break;
	    case 3: idx = (int)(0.75*(float)self->numberOfSamples);
		    break;
            default: idx = 200;
		     break;
	}

        for (int i=rampStartValue; i<rampStartValue+idx; i++)
	{
	    float x1 = rampStartValue;
	    float y1 = 0;

	    float x2 = rampStartValue + (float)idx;
	    float y2 = self->amplitude;

            float k = (y2-y1) / (x2-x1);
	    yVal = k*(rampStartValue+i) + minValue;
	    printf("x1:%.4f, y1:%.4f, x2:%.4f, y2:%.4f, rampStartValue:%d, minValue:%.4f, k:%.4f, yVal:%.4f\n", x1, y1, x2, y2, rampStartValue, minValue, k, yVal);

	    if (self->enableNoise == NOISE_ON)
	    {
                //noise = rand_interval(self->minNoiseValue, self->maxNoiseValue);
	    }
	    fprintf(fp, "%.4f\n", yVal + noise);
	    ar[i] = yVal + noise;
	}

        for (int i=rampStartValue+idx; i<self->numberOfSamples; i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                //noise = rand_interval(self->minNoiseValue, self->maxNoiseValue);
	    }
	    fprintf(fp, "%.4f\n", (yVal + minValue));
	    ar[i] = self->amplitude + noise;
	}

	fclose(fp);

	printf("'ramp_samples.txt' created\n");

	return ar;
}

