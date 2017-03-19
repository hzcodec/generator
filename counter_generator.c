#include <stdio.h>
#include <stdlib.h>
#include "frame1.h"
#include "common.h"

float* Counter_generator__generate_counter(struct Generator* self)
{
	//printf("%s() -\n", __func__);

        FILE *fp;
	float counter = 1.0;
	float noise = 0.0;

        fp = fopen("counter_samples.txt", "w");
        
        float *ar = (float *)malloc(sizeof(float) * self->numberOfSamples);    

        for (int i=0; i<self->numberOfSamples; i++)
        {
	        if (self->enableNoise == NOISE_ON)
	        {
                    noise = Common__gen_noise(self);
	        }
                fprintf(fp, "%.4f\n", noise + counter++);
                ar[i] = counter + noise;
        }

	fclose(fp);

	printf("'counter_samples.txt' created\n");

        return ar;
}
