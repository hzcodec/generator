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

