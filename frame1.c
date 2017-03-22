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
#include <getopt.h>
#include "frame1.h"
#include "sinus_generator.h"
#include "counter_generator.h"
#include "ramp_generator.h"
#include "square_generator.h"
#include "filter.h"

struct Gen_properties {
        float amplitude;
	int   numberOfSamples;
	int   enableNoise;
	int   rampSlopeType;
	float alpha;
};


void print_usage()
{
    printf("Usage: -a [0.0-user def] -s [64-12288] -n [0|1] -r [1-4] -f [0.0-user def]\n");
    printf("       -a : amplitude\n");
    printf("       -s : number of samples\n");
    printf("       -r : ramp type [1 -4]\n");
    printf("       -n : enable noise\n");
    printf("       -f : alpha value for filter\n");
}

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
                printf("Amplitude: -\n");
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
                printf("Min Noise level: -\n");
                printf("Max Noise level: -\n");
	}

	if (self->type == RAMP)
	{
                printf("Ramp type: %s\n", ENUM2STRING(self->rampSlopeType));
	}
	else
	{
                printf("Ramp type: -\n");
	}

	printf("Alpha: %.4f\n", self->alpha);

        printf(DELIMITER);
}

// Allocation + initialization
struct Generator* Generator__create(struct Generator* gen)
{
	struct Generator* generatorObject = malloc((sizeof(struct Generator)));
	//printf("%s() - generatorObject:%p, type:%s, amplitude:%.2f\n", __func__, generatorObject, ENUM2STRING(gen->type), gen->amplitude);

	switch (gen->type)
	{
	        case SINUS:
	             generatorObject->gen = Sinus_generator__generate_sinus;
	             break;
	        case RAMP:
	             generatorObject->gen = Ramp_generator__generate_ramp;
	             break;
	        case COUNTER:
	             generatorObject->gen = Counter_generator__generate_counter;
	             break;
	        case SQUARE:
	             generatorObject->gen = Square_generator__generate_square;
	             break;
	        default:
	             generatorObject->gen = Sinus_generator__generate_sinus;
	             break;
	}
        generatorObject->type = gen->type;
        generatorObject->amplitude = gen->amplitude;
        generatorObject->numberOfSamples = gen->numberOfSamples;
        generatorObject->enableNoise = gen->enableNoise;
        generatorObject->minNoiseValue = gen->minNoiseValue;
        generatorObject->maxNoiseValue = gen->maxNoiseValue;
        generatorObject->rampSlopeType = gen->rampSlopeType;
        generatorObject->alpha         = gen->alpha;

	return generatorObject;
}

float* Generator__run(struct Generator* self)
{
        float* array;  // array holding sample values

	//printf("%s() -\n", __func__);
        Generator__printProperties(self);

        array = self->gen(self);
	return array;
}

void Generator__destroy(struct Generator* gen) 
{
	//printf("%s() - \n", __func__);
        if (gen)
	{
                free(gen);
        }
}

void Generator__populate_object(struct Generator *self, struct Gen_properties *gp)
{
	self->amplitude = gp->amplitude;
	self->numberOfSamples = gp->numberOfSamples;
	self->enableNoise = gp->enableNoise;
	self->rampSlopeType = gp->rampSlopeType;
	self->alpha = gp->alpha;
}


int main(int argc, char *argv[])
{
        int option = 0;
        int select = 1;
	int noise  = NOISE_OFF;   // noise off
	int rt     = RAMP1;       // ramp type 1
        float* squareArray;       // array holding sample values
        float* rampArray;         // array holding sample values

	struct Gen_properties gp;

	// default values
	gp.amplitude = 1.0; 
	gp.numberOfSamples = 128; 
	gp.enableNoise = NOISE_OFF;
	gp.rampSlopeType = RAMP1;
	gp.alpha = 0.01;

        while ((option = getopt(argc, argv,"a:s:n:r:f:h")) != -1)
	{
            switch (option) {
                              case 'a' : gp.amplitude = atof(optarg);
                                         break;
                              case 's' : gp.numberOfSamples = atoi(optarg);
                                         break;
                              case 'n' : noise = atoi(optarg);
			                 gp.enableNoise = noise ? NOISE_ON : NOISE_OFF; 
                                         break;
                              case 'r' : rt = atoi(optarg);
					 switch (rt)
					 {
					     case 1: gp.rampSlopeType = RAMP1; 
					             break;
					     case 2: gp.rampSlopeType = RAMP2; 
					             break;
					     case 3: gp.rampSlopeType = RAMP3; 
					             break;
					     case 4: gp.rampSlopeType = RAMP4; 
					             break;
					     default: gp.rampSlopeType = RAMP1; 
					              break;
					 }
                                         break;
                              case 'f' : gp.alpha= atof(optarg);
                                         break;
                              case 'h' : print_usage();
                                         exit(EXIT_FAILURE);
                                         break;
             default: print_usage(); 
                      exit(EXIT_FAILURE);
            }
        }

	// setup default parameters for sinus generator
	struct Generator sin = {SINUS,            // signal type
	                        1.0,             // amplitude, 
				256,             // number of samples 
				NOISE_OFF,       // disable noise
				0.1,             // min noise level
				0.3,             // max noise level
				NOT_APPLICABLE,
				0.01             // alpha value for filter
			       };

	struct Generator counter = {COUNTER,        // signal type
	                            0,              // amplitude, 
				    64,             // number of samples 
				    NOISE_ON,       // enable noise
				    0.1,            // min noise level
				    0.3,            // max noise level
				    NOT_APPLICABLE,
				    0.01            // alpha value for filter
				   };

	struct Generator ramp = {RAMP,           // signal type
	                         2.0,            // amplitude, 
				 128,            // number of samples 
				 NOISE_OFF,      // enable noise
				 0.1,            // min noise level
				 0.3,            // max noise level
				 RAMP1,          // ramp type
				 0.01            // alpha value for filter
				};

	struct Generator square = {SQUARE,       // signal type
	                           2.0,          // amplitude, 
				   1024,         // number of samples 
				   NOISE_ON,     // enable noise
				   0.1,          // min noise level
				   0.3,          // max noise level
				   RAMP1,        // ramp type
				   0.01          // alpha value for filter
				  };

        Generator__populate_object(&sin, &gp);
        Generator__populate_object(&counter, &gp);
        Generator__populate_object(&ramp, &gp);
        Generator__populate_object(&square, &gp);

        struct Generator *pSinusGenerator = Generator__create(&sin);
        Generator__run(pSinusGenerator);

        struct Generator *pCounterGenerator = Generator__create(&counter);
        Generator__run(pCounterGenerator);

        struct Generator *pRampGenerator = Generator__create(&ramp);
        rampArray = Generator__run(pRampGenerator);

        struct Generator *pSquareGenerator = Generator__create(&square);
        squareArray = Generator__run(pSquareGenerator);

        Filter__filter(rampArray, pSquareGenerator, "filtered_ramp.txt");
        Filter__filter(squareArray, pSquareGenerator, "filtered_square.txt");

        Generator__destroy(pSinusGenerator); 
        Generator__destroy(pCounterGenerator); 
        Generator__destroy(pRampGenerator); 
        Generator__destroy(pSquareGenerator); 

	return 0;
}

