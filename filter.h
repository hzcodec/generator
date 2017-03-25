#ifndef _FILTER_H_
#define _FILTER_H_

struct TriggerPoint {
  	float maxValue;
	int   idx;
};

struct Gen_properties {
        float amplitude;
	int   numberOfSamples;
	int   enableNoise;
	float alpha;
	float riseTime;   // [ms]
	float delayTime;  // [ms]
};

void Filter__filter(float *ar, struct Generator *gen, char *s);
void Filter__find_max_input_value(struct TriggerPoint *tp, float val, int n);
void Filter__find_max_filter_value(struct TriggerPoint *tp, float val, int n);
void Filter__filter_real_data(struct Gen_properties *gen);

#endif
