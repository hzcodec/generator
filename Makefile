CC     = gcc
CFLAGS = -std=c99

m1: frame1.c
	$(CC) frame1.c -c
	$(CC) sinus_generator.c -c
	$(CC) counter_generator.c -c
	$(CC) ramp_generator.c -c
	$(CC) common.c -c
	gcc  sinus_generator.o counter_generator.o ramp_generator.o common.o frame1.o -lm -o frame


clean:
	rm -f a.out *.txt *.o frame

