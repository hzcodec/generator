/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-21
    File         : square_generator.c
    Reference    : -
    Description  : -
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "frame1.h"
#include "common.h"


float* Square_generator__generate_square(struct Generator *self)
{
        FILE *fp;
	float noise = 0.0;
	float out = 0.0;

        fp = fopen("square_samples.txt", "w");

        Common__fprintProperties(fp, self);

        float *ar = (float *)malloc(sizeof(float) * (float)self->numberOfSamples);    
	//float dist = (float)self->ratio/100.0 * (float)self->numberOfSamples;
	float dist = 20.0/100.0 * (float)self->numberOfSamples;
	float start = (float)self->numberOfSamples/2.0 - dist/2.0;
	float stop = (float)self->numberOfSamples/2.0 + dist/2.0;

	for (int i=0; i<((int)start); i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }
            ar[i] = (out + noise) * self->amplitude;
            fprintf(fp, "%.4f\n", (out + noise) * self->amplitude);
	    //printf("%s() - ar[%d]:%.4f\n", __func__, i, ar[i]);
	}

	out = 1.0;
	for (int i=start+1; i<((int)stop); i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }
            ar[i] = (out + noise) * self->amplitude;
            fprintf(fp, "%.4f\n", (out + noise) * self->amplitude);
	    //printf("%s() - ar[%d]:%.4f\n", __func__, i, ar[i]);
	}

	out = 0.0;
	for (int i=stop+1; i<((int)self->numberOfSamples+2); i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }
            ar[i] = (out + noise) * self->amplitude;
            fprintf(fp, "%.4f\n", (out + noise) * self->amplitude);
	    //printf("%s() - ar[%d]:%.4f\n", __func__, i, ar[i]);
	}

	fclose(fp);

	printf("'square_samples.txt' created\n");

        return ar;
}

