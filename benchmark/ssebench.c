#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define USE_AVX

#ifdef USE_AVX
#define ADD_COUNT 8
float a[8] asm ("a")__attribute__((aligned(32))) ={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
float b[8] asm ("b")__attribute__((aligned(32))) =
	{0.000001,0.000002,0.000003,0.000004,0.000005,0.000006,0.000007,0.000008};

#else
#define ADD_COUNT 4
float a[4] asm ("a")__attribute__((aligned(16))) ={0.0,0.0,0.0,0.0};
float b[4] asm ("b")__attribute__((aligned(16))) ={0.000001,0.000002,0.000003,0.000004};
#endif

long num = 400 * 1000 * 1000;
void loop_vaddps()
{
	long i;

	asm("VMOVAPS a, %ymm0");
	asm("VMOVAPS b, %ymm1");
	for(i = 0;i < num;i++) {
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
		asm("VADDPS %ymm1, %ymm0, %ymm0");
	}
	asm("VMOVAPS %ymm0, a");
	asm("VMOVAPS %ymm1, b");
	//printf("%f %f %f %f %f %f %f %f\n", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	//printf("%f %f %f %f %f %f %f %f\n", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
}
void loop_addps()
{
	long i;

	asm("MOVAPS a, %xmm0");
	asm("MOVAPS b, %xmm1");
	for(i = 0;i < num;i++) {
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
		asm("ADDPS %xmm1, %xmm0");
	}
	asm("MOVAPS %xmm0, a");
	asm("MOVAPS %xmm1, b");
	//printf("%f %f %f %f %f %f %f %f\n", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	//printf("%f %f %f %f %f %f %f %f\n", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
}


int main()
{
	int thread_num = 4;
	int i;
	double elpase;
	clock_t t0, t1;
	pthread_t* thread_list;
	thread_list = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);

    t0 = clock();
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

    t1 = clock();
    elpase = (t1 - t0)/(double)CLOCKS_PER_SEC;
    printf ( "time :%f\n", elpase);
    printf ( "%.6f flops\n", num / elpase * 5 * ADD_COUNT * thread_num);
    printf ( "num = %d\n", num);
    free(thread_list);
	return 0;
}

