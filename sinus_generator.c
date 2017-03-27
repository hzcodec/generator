/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-19
    File         : sinus_generator.c
    Reference    : -
    Description  : -
*/ 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "frame1.h"
#include "common.h"

float* Sinus_generator__generate_sinus(struct Generator* self)
{
	//printf("%s() - type:%d, amplitude:%.2f, noOfSamples:%d, enableNoise:%d\n", __func__, self->type, self->amplitude, self->numberOfSamples, self->enableNoise);

        FILE *fp;
	float noise = 0.0;

        fp = fopen("sinus_samples.txt", "w");

        float deg = 0.0;
        float value = 0.0;
        float *ar = (float *)malloc(sizeof(float) * self->numberOfSamples);    

        for (int i=0; i<self->numberOfSamples; i++)
        {
	        if (self->enableNoise == NOISE_ON)
	        {
                    noise = Common__gen_noise(self);
	        }
                deg = (float)i*(360.0 / self->numberOfSamples);
                value = self->amplitude * sin(deg * M_PI / 180) + noise;

                fprintf(fp, "%.4f\n", value);
                ar[i] = value;
        }

	fclose(fp);

	printf("'sinus_samples.txt' created\n");
        return ar;
}
 
