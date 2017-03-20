#ifndef _FRAME_H_
#define _FRAME_H_

#define DELIMITER "---------------------------------------------------\n"

#define ENUM2STRING(_str) _str == SINUS ? "Sinus" : \
                          _str == RAMP ? "Ramp" : \
                          _str == SQUARE ? "Square" : \
                          _str == COUNTER ? "Counter" : \
                          _str == POWER2 ? "Power2" : \
                          _str == NOISE_ON ? "NOISE_ON" : \
                          _str == NOISE_OFF ? "NOISE_OFF" : \
                          _str == RAMP1 ? "RAMP1" : \
                          _str == RAMP2 ? "RAMP2" : \
                          _str == RAMP3 ? "RAMP3" : \
                          _str == RAMP4 ? "RAMP4" : \
                          _str == NOT_APPLICABLE ? "NOT_APPLICABLE" : "UNKNOWN"

enum generator_properties {
	SINUS = 0,
	RAMP,
        SQUARE,
	COUNTER,
	POWER2,
        NOISE_ON,
	NOISE_OFF,
	RAMP1,
	RAMP2,
	RAMP3,
	RAMP4,
	NOT_APPLICABLE,
};


struct Generator{
   int    type;                      // type of generated signal
   float  amplitude;                 // amplitude level of signal
   int    numberOfSamples;           // number of samples
   int    enableNoise;               // noise enable flag
   float  minNoiseValue;             // minimum noise level
   float  maxNoiseValue;             // maximum noise level
   int    rampSlopeType;             // ramp slope type
   float* (*gen)(struct Generator*);
   char   name[20];                  // filename of logfile
};

#endif
