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
	int   idx1;

        float *ar = (float *)malloc(sizeof(float) * self->numberOfSamples);    
        fp = fopen("ramp_samples.txt", "w");

	char *str = "Ramp ";
	char c = self->rampSlopeType + '0';
	size_t len = strlen(str);
        char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
        strcpy(str2, str);
        str2[len] = c;
        str2[len + 1] = '\0';

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
	    case 1: idx1 = (int)(0.05*(float)self->numberOfSamples);
	            part = 0.05; // 5%
		    break;
	    case 2: idx1 = (int)(0.25*(float)self->numberOfSamples);
	            part = 0.25; // 25%
		    break;
	    case 3: idx1 = (int)(0.50*(float)self->numberOfSamples);
	            part = 0.50; // 50%
		    break;
	    case 4: idx1 = (int)(0.75*(float)self->numberOfSamples);
	            part = 0.75; // 75%
		    break;
            default: idx1 = 200;
	             part = 0.05;
		     break;
	}

        for (int i=rampStartValue; i<rampStartValue+idx1; i++)
	{
            float k = (self->amplitude-minValue)/(float)((rampStartValue+idx1) - rampStartValue);
	    yVal = k*(i-rampStartValue) + minValue;
	    if (self->enableNoise == NOISE_ON)
	    {
                //noise = rand_interval(self->minNoise, self->maxNoise);
	    }
	    fprintf(fp, "%.4f\n", yVal + noise);
	    ar[i] = yVal + noise;
	}

        for (int i=rampStartValue+idx1; i<self->numberOfSamples; i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                //noise = rand_interval(self->minNoise, self->maxNoise);
	    }
	    fprintf(fp, "%.4f\n", self->amplitude + noise);
	    ar[i] = self->amplitude + noise;
	}

	fclose(fp);

	printf("'ramp_samples.txt' created\n");

	return ar;
}

