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

#define OFFS 50
 
float* Ramp_generator__generate_ramp(struct Generator* self)
{
        FILE *fp;
	float yVal = 0.0;
	float noise = 0.0;
	float minValue = 0;

	int sampleRiseTime = (int)(self->riseTime/SAMPLE_TIME*1000);
	int sampleDelayTime = (int)(self->delayTime/SAMPLE_TIME*1000);

        float *ar = (float *)malloc(sizeof(float) * self->numberOfSamples);    
        fp = fopen("ramp_samples.txt", "w");

	// calculate the slope
        for (int i=0; i<sampleRiseTime; i++)
	{
	    float x1 = 0;
	    float y1 = 0;

	    float x2 = sampleRiseTime;
	    float y2 = self->amplitude;

            float k = (y2-y1) / (x2-x1);
	    yVal = k*i;

	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }

	    fprintf(fp, "%.4f\n", yVal + minValue + noise);
	    ar[i] = yVal + minValue + noise;
	    //printf("%s(2) - ar[%d]: %.4f, sampleRiseTime: %d, sampleDelayTime: %d\n", __func__, i, ar[i], sampleRiseTime, sampleDelayTime);
	}

        // top level
        for (int i=0; i<sampleDelayTime; i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }

	    fprintf(fp, "%.4f\n", (yVal + minValue + noise));
	    ar[i+sampleRiseTime] = yVal + minValue + noise;
	    //printf("%s(3) - ar[%d]: %.4f\n", __func__, i+sampleRiseTime, ar[i+sampleRiseTime]);
	}

        // go back to original level
        for (int i=0; i<self->numberOfSamples-(sampleRiseTime+sampleDelayTime); i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }

	    fprintf(fp, "%.4f\n", (minValue + noise));
	    ar[i+(sampleRiseTime+sampleDelayTime)] = minValue + noise;
	    //printf("%s(3) - ar[%d]: %.4f\n", __func__, i+sampleRiseTime+sampleDelayTime, ar[i+sampleRiseTime+sampleDelayTime]);
	}

	fclose(fp);

	printf("'ramp_samples.txt' created\n");

	return ar;
}

