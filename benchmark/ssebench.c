#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#define USE_AVX
#define LONG long long

#ifdef USE_AVX
#define ADD_COUNT 8
#else
#define ADD_COUNT 4
#endif

float a[8] asm ("a")__attribute__((aligned(16))) ={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
float b[8] asm ("b")__attribute__((aligned(16))) =
	{0.000001,0.000002,0.000003,0.000004,0.000005,0.000006,0.000007,0.000008};
LONG num = 500 * 1000 * 1000;


double getTimeStamp()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((double)(tv.tv_sec) + (double)(tv.tv_usec) * 0.000001);
}

void loop_vaddps()
{
	LONG i;
	float c[8] __attribute__((aligned(32))) ={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

	asm("VMOVAPS a, %ymm0");
	asm("VMOVAPS b, %ymm1");
	for(i = 0;i < num;i++) {
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
	}
	asm("VMOVUPS %%ymm0, (%0)"::"r"(&c));
	asm("VMOVAPS %ymm1, b");
	//printf("%f %f %f %f %f %f %f %f\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
}
void loop_addps()
{
	LONG i;
	float c[4] __attribute__((aligned(16))) ={0.0,0.0,0.0,0.0};

	asm("MOVAPS a, %xmm0");
	asm("MOVAPS b, %xmm1");
	for(i = 0;i < num;i++) {
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
	}
	asm("MOVUPS %%xmm0, (%0)"::"r"(&c));
	asm("MOVAPS %xmm1, b");
	printf("%f %f %f %f\n", c[0], c[1], c[2], c[3]);
}


int main()
{
	printf("int => %d\n", sizeof(int));
	printf("long => %d\n", sizeof(long));
	printf("unsigned long => %d\n", sizeof(unsigned long));
	printf("long long => %d\n", sizeof(long long));
	LONG thread_num = 4;
	LONG count_on_thread = 0, i;
	double elpase;
	double start,stop;
	pthread_t* thread_list;
	thread_list = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);

	start = getTimeStamp();
	for(i = 0;i < thread_num;i++) {

#ifdef USE_AVX
		pthread_create(&thread_list[i], NULL, (void *)loop_vaddps, NULL);
#else
		pthread_create(&thread_list[i], NULL, (void *)loop_addps, NULL);
#endif
	}
	for(i = 0;i < thread_num;i++) {
		pthread_join(thread_list[i], NULL);
	}

	stop = getTimeStamp();
	elpase = stop - start;
	count_on_thread = num * 5 * ADD_COUNT;
	printf ( "time :%.3f\n", elpase);
	printf ( "%.3f Mflops\n", count_on_thread / elpase * thread_num / 1000 / 1000);
	printf ( "num = %lld\n", count_on_thread);
	free(thread_list);
	return 0;
}

