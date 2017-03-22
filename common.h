#ifndef _COMMON_H_
#define _COMMON_H_

#define SAMPLE_TIME 83.3333 // 83.3 us

float Common__gen_noise(struct Generator* gen);
void Common__printProperties(struct Generator* gen);
void Common__fprintProperties(FILE *fp, struct Generator* gen);

#endif
