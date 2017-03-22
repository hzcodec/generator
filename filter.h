#ifndef _FILTER_H_
#define _FILTER_H_

void Filter__filter(float *ar, struct Generator *gen, char *s);
void Filter__find_max_input_value(struct TriggerPoint *tp, float val, int n);
void Filter__find_max_filter_value(struct TriggerPoint *tp, float val, int n);

#endif
