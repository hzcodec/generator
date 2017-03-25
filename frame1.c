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
#include "common.h"


void print_usage()
{
    printf("Usage: -a [0.0->] -s [64-12288] -n [0|1] -r [0.0 ->] -d [0.0 ->] -f [0.0->]\n");
    printf("       -a : amplitude\n");
    printf("       -s : number of samples\n");
    printf("       -n : enable noise\n");
    printf("       -r : rise time\n");
    printf("       -d : delay time\n");
    printf("       -f : alpha value for filter\n");
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
        generatorObject->alpha         = gen->alpha;
        generatorObject->riseTime      = gen->riseTime;
        generatorObject->delayTime      = gen->delayTime;

	return generatorObject;
}

float* Generator__run(struct Generator* self)
{
        float* array;  // array holding sample values

	//printf("%s() -\n", __func__);
        Common__printProperties(self);

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

void Generator__populate_object(struct Generator *self, struct Generator *gp)
{
	if (gp->numberOfSamples < (int)(gp->riseTime/SAMPLE_TIME*1000))
	{
		printf("***\n");
		printf("Warning! You must increase number of samples. Minumum is %d\n", (int)(gp->riseTime/SAMPLE_TIME*1000));
		printf("***\n");
		exit(-1);
	}

	self->amplitude = gp->amplitude;
	self->numberOfSamples = gp->numberOfSamples;
	self->enableNoise = gp->enableNoise;
	self->alpha = gp->alpha;
	self->riseTime = gp->riseTime;
	self->delayTime = gp->delayTime;
}


int main(int argc, char *argv[])
{
        int option = 0;
        int select = 1;
	int noise  = NOISE_OFF;   // noise off
	int rt     = RAMP1;       // ramp type 1
        float* squareArray;       // array holding sample values
        float* rampArray;         // array holding sample values
        float* sinusArray;        // array holding sample values

	//struct Gen_properties gp;
	struct Generator gp;

	// default values
	gp.amplitude = 1.0; 
	gp.numberOfSamples = 256; 
	gp.enableNoise = NOISE_OFF;
	gp.alpha = 0.01;
	gp.riseTime = 5.0;
	gp.delayTime = 1.0;

        while ((option = getopt(argc, argv,"a:s:n:r:d:f:h")) != -1)
	{
            switch (option) {
                              case 'a' : gp.amplitude = atof(optarg);
                                         break;
                              case 's' : gp.numberOfSamples = atoi(optarg);
                                         break;
                              case 'n' : noise = atoi(optarg);
			                 gp.enableNoise = noise ? NOISE_ON : NOISE_OFF; 
                                         break;
                              case 'r' : gp.riseTime= atof(optarg);
                                         break;
                              case 'd' : gp.delayTime= atof(optarg);
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

	struct Generator ramp = {RAMP,           // signal type
	                         2.0,            // amplitude, 
				 128,            // number of samples 
				 NOISE_OFF,      // enable noise
				 0.1,            // min noise level
				 0.3,            // max noise level
				 0.01,           // alpha value for filter
				 1.0,             // rise time
				 2.0              // delay time
				};

	// setup default parameters for sinus generator
	struct Generator sin = {SINUS,            // signal type
	                        1.0,             // amplitude, 
				256,             // number of samples 
				NOISE_OFF,       // disable noise
				0.1,             // min noise level
				0.3,             // max noise level
				0.01,            // alpha value for filter
				NOT_APPLICABLE,  
				NOT_APPLICABLE   
			       };

	struct Generator counter = {COUNTER,        // signal type
	                            0,              // amplitude, 
				    64,             // number of samples 
				    NOISE_ON,       // enable noise
				    0.1,            // min noise level
				    0.3,            // max noise level
				    0.01,           // alpha value for filter
				    NOT_APPLICABLE,  
				    NOT_APPLICABLE   
				   };


	struct Generator square = {SQUARE,         // signal type
	                           2.0,            // amplitude, 
				   1024,           // number of samples 
				   NOISE_ON,       // enable noise
				   0.1,            // min noise level
				   0.3,            // max noise level
				   0.01,           // alpha value for filter
				   NOT_APPLICABLE,  
				   NOT_APPLICABLE   
				  };

        Generator__populate_object(&ramp, &gp);
        Generator__populate_object(&sin, &gp);
        Generator__populate_object(&counter, &gp);
        Generator__populate_object(&square, &gp);

        struct Generator *pRampGenerator = Generator__create(&ramp);
        rampArray = Generator__run(pRampGenerator);

        struct Generator *pSinusGenerator = Generator__create(&sin);
        sinusArray = Generator__run(pSinusGenerator);

        struct Generator *pCounterGenerator = Generator__create(&counter);
        Generator__run(pCounterGenerator);

        struct Generator *pSquareGenerator = Generator__create(&square);
        squareArray = Generator__run(pSquareGenerator);

        Filter__filter(rampArray, pRampGenerator, "filtered_ramp.txt");
        Filter__filter(sinusArray, pSinusGenerator, "filtered_sinus.txt");
        Filter__filter(squareArray, pSquareGenerator, "filtered_square.txt");

        Filter__filter_real_data(&gp);

        Generator__destroy(pRampGenerator); 
        Generator__destroy(pSinusGenerator); 
        Generator__destroy(pCounterGenerator); 
        Generator__destroy(pSquareGenerator); 

	// start python script using matplotlib
	system("python plot.py &");
	//system("python plot.py 2&");

	return 0;
}

