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
	//printf("%s() - \n", __func__);
        FILE *fp;
	float yVal;
	float noise = 0.0;
	float minValue = 1;
	int   slopeStart = 0.1 * self->numberOfSamples; // start of slope condition, 10% of max number of samples
	int   slopeEnd = 0; // end slope value

        float *ar = (float *)malloc(sizeof(float) * self->numberOfSamples);    
        fp = fopen("ramp_samples.txt", "w");

        Common__fprintProperties(fp, self);


	// calculate where the slopa shall start
	switch(self->rampSlopeType)
	{
	    case RAMP1: slopeEnd = slopeStart + 10;
		        break;
	    case RAMP2: slopeEnd = slopeStart + 30;
		        break;
	    case RAMP3: slopeEnd = slopeStart + 50;
		        break;
	    case RAMP4: slopeEnd = slopeStart + 70;
		        break;
            default: slopeEnd = 200;
		     break;
	}

	// generate samples before slope starts
        for (int i=0; i<slopeStart; i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }

	    fprintf(fp, "%.4f\n", minValue + noise);
	    ar[i] = minValue + noise;
	    //printf("%s(1) - ar[%d]: %.4f, slopeStart: %d, slopeEnd: %d\n", __func__, i, ar[i], slopeStart, slopeEnd);
	}


	// calculate the slope
        for (int i=0; i<slopeEnd; i++)
	{
	    float x1 = slopeStart;
	    float y1 = 0;

	    float x2 = slopeEnd;
	    float y2 = self->amplitude;

            float k = (y2-y1) / (x2-x1);
	    yVal = k*i;

	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }

	    fprintf(fp, "%.4f\n", yVal + minValue + noise);
	    ar[i+slopeStart] = yVal + minValue + noise;
	    //printf("%s(2) - ar[%d]: %.4f, slopeEnd: %d, slopeStart: %d\n", __func__, i+slopeStart, ar[i+slopeStart], slopeEnd, slopeStart);
	}

        // go back to original level
        //for (int i=slopeEnd+1; i<self->numberOfSamples; i++)
        for (int i=0; i<(self->numberOfSamples - (slopeStart+slopeEnd)); i++)
	{
	    if (self->enableNoise == NOISE_ON)
	    {
                noise = Common__gen_noise(self) / 4;
	    }

	    fprintf(fp, "%.4f\n", (yVal + minValue));
	    ar[i+slopeStart+slopeEnd] = yVal + minValue + noise;
	    //printf("%s(3) - ar[%d]: %.4f\n", __func__, i+slopeStart+slopeEnd, ar[i+slopeStart+slopeEnd]);
	}

	fclose(fp);

	printf("'ramp_samples.txt' created with slope type: %s\n", ENUM2STRING(self->rampSlopeType));

	return ar;
}

