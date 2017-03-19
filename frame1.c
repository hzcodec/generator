/*
    Auther       : Heinz Samuelsson
    Date         : 2017-03-19
    File         : frame1.c
    Reference    : -
    Description  : -
	           gcc  frame1.c -lm -o frame
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "frame1.h"
#include "sinus_generator.h"
#include "counter_generator.h"
#include "ramp_generator.h"

void Generator__printProperties(struct Generator* self)
{
        printf(DELIMITER);

        printf("Type: %s\n", ENUM2STRING(self->type));

	if (self->type != COUNTER)
	{
                printf("Amplitude: %.4f\n", self->amplitude);
	}
	else
	{
                printf("Amplitude: NOT_APPLICABLE\n");
	}
        printf("Number of samples: %d\n", self->numberOfSamples);
        printf("Noise enabled: %s\n", ENUM2STRING(self->enableNoise));

        if(self->enableNoise == NOISE_ON)
	{
                printf("Min Noise level: %.4f\n", self->minNoiseValue);
                printf("Max Noise level: %.4f\n", self->maxNoiseValue);
	}
	else
	{
                printf("Min Noise level: NOT_APPLICABLE\n");
                printf("Max Noise level: NOT_APPLICABLE\n");
	}

        printf("Ramp type: %s\n", ENUM2STRING(self->rampSlopeType));
        printf(DELIMITER);
}

// Allocation + initialization
struct Generator* Generator__create(struct Generator* gen)
{
	struct Generator* result = malloc((sizeof(struct Generator)));
	printf("%s() - result:%p, type:%s, amplitude:%.2f\n", __func__, result, ENUM2STRING(gen->type), gen->amplitude);

	switch (gen->type)
	{
	        case SINUS:
	             result->gen = Sinus_generator__generate_sinus;
	             break;
	        case RAMP:
	             result->gen = Ramp_generator__generate_ramp;
	             break;
	        case COUNTER:
	             result->gen = Counter_generator__generate_counter;
	             break;
	        default:
	             result->gen = Sinus_generator__generate_sinus;
	             break;
	}
        result->type = gen->type;
        result->amplitude = gen->amplitude;
        result->numberOfSamples = gen->numberOfSamples;
        result->enableNoise = gen->enableNoise;
        result->minNoiseValue = gen->minNoiseValue;
        result->maxNoiseValue = gen->maxNoiseValue;
        result->rampSlopeType = gen->rampSlopeType;

	return result;
}

void Generator__run(struct Generator* self)
{
	//printf("%s() -\n", __func__);
        Generator__printProperties(self);

        float* array;  // array holding sample values
        array = self->gen(self);
}

void Generator__destroy(struct Generator* gen) 
{
	//printf("%s() - \n", __func__);
        if (gen)
	{
                free(gen);
        }
}


int main(int argc, char *argv[])
{
	// setup default parameters for sinus generator
	struct Generator sinGenerator = {SINUS, 
	                                 8.0,           // amplitude, 
				         256,           // number of samples 
				         NOISE_OFF,     // disable noise
				         0.1,           // min noise level
				         0.3,           // max noise level
					 NOT_APPLICABLE
				        };

	struct Generator counter = {COUNTER, 
	                            0,              // amplitude, 
				    64,             // number of samples 
				    NOISE_ON,       // enable noise
				    0.1,            // min noise level
				    0.3,            // max noise level
				    NOT_APPLICABLE
				   };

	struct Generator ramp = {RAMP, 
	                         0,              // amplitude, 
				 128,            // number of samples 
				 NOISE_OFF,      // enable noise
				 0.1,            // min noise level
				 0.3,            // max noise level
				 1               // ramp type
				};

        struct Generator *pSinusGenerator = Generator__create(&sinGenerator);
        Generator__run(pSinusGenerator);

        struct Generator *pCounterGenerator = Generator__create(&counter);
        Generator__run(pCounterGenerator);

        struct Generator *pRampGenerator = Generator__create(&ramp);
        Generator__run(pRampGenerator);

        Generator__destroy(pSinusGenerator); 
        Generator__destroy(pCounterGenerator); 
        Generator__destroy(pRampGenerator); 

	return 0;
}

