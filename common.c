/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-19
    File         : common.c
    Reference    : -
    Description  : -
*/ 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "frame1.h"

static bool swap = false;  // swap noise offset
 
float rand_interval(float min, float max)
{
    int r;
    const float range = 1 + max - min;
    const float buckets = RAND_MAX / range;
    const float limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

// generate noise
float Common__gen_noise(struct Generator* gen)
{
        float noise = rand_interval(gen->minNoiseValue, gen->maxNoiseValue);

	// alternate offset for noise
      	if (swap == true)
      	{
      	        noise = noise * (-1.0);
      	}

      	swap = !swap;
	return noise;
}

void Common__printProperties(struct Generator* gen)
{
        printf(DELIMITER);

        printf("Type: %s\n", ENUM2STRING(gen->type));

	if (gen->type != COUNTER)
	{
                printf("Amplitude: %.4f\n", gen->amplitude);
	}
	else
	{
                printf("Amplitude: -\n");
	}
        printf("Number of samples: %d\n", gen->numberOfSamples);
        printf("Noise enabled: %s\n", ENUM2STRING(gen->enableNoise));

        if(gen->enableNoise == NOISE_ON)
	{
                printf("Min Noise level: %.4f\n", gen->minNoiseValue);
                printf("Max Noise level: %.4f\n", gen->maxNoiseValue);
	}
	else
	{
                printf("Min Noise level: -\n");
                printf("Max Noise level: -\n");
	}

	printf("Alpha: %.4f\n", gen->alpha);
	printf("Rise time: %.4f\n", gen->riseTime);
	printf("Delay time: %.4f\n", gen->delayTime);

        printf(DELIMITER);
}

void Common__fprintProperties(FILE *fp, struct Generator* gen)
{
	fprintf(fp, "%s", DELIMITER);

        fprintf(fp, "Type: %s\n", ENUM2STRING(gen->type));

	if (gen->type != COUNTER)
	{
                fprintf(fp, "Amplitude: %.4f\n", gen->amplitude);
	}
	else
	{
                fprintf(fp, "Amplitude: -\n");
	}
        fprintf(fp, "Number of samples: %d\n", gen->numberOfSamples);
        fprintf(fp, "Noise enabled: %s\n", ENUM2STRING(gen->enableNoise));

        if(gen->enableNoise == NOISE_ON)
	{
                fprintf(fp, "Min Noise level: %.4f\n", gen->minNoiseValue);
                fprintf(fp, "Max Noise level: %.4f\n", gen->maxNoiseValue);
	}
	else
	{
                fprintf(fp, "Min Noise level: -\n");
                fprintf(fp, "Max Noise level: -\n");
	}

	fprintf(fp, "Alpha: %.4f\n", gen->alpha);
	fprintf(fp, "Rise time: %.4f\n", gen->riseTime);
	fprintf(fp, "Delay time: %.4f\n", gen->delayTime);

        fprintf(fp, "%s", DELIMITER);
}
