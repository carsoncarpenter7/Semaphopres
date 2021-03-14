#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

// moved the semaphores here so it can be shared
// between threads
sem_t mutex, mutex2, mutex3;

void *protect_critical_region(void *n)
{
    int i = 0, thread_num = (int)(long)n;
    bool finished = false;

    while (!finished)
    {
        // TODO: FILL IN THIS LINE
        sem_wait(&mutex); // locking the 1st semaphore
        for (int j = 0; j < thread_num; ++j)
        {
            printf("\t\t\t");
        }
        printf("CRITICAL(T%d)\n", thread_num);
        // TODO: FILL IN THIS LINE
        sem_post(&mutex); // releasing the 1st semaphore

        sleep(2);

        // TODO: FILL IN THIS LINE
        sem_wait(&mutex2); // locking the 2nd semaphore
        for (int j = 0; j < thread_num; ++j)
        {
            printf("\t\t\t");
        }
        printf("out of CRITICAL(T%d)\n", thread_num);
        // TODO: FILL IN THIS LINE
        sem_post(&mutex2); // releasing the 2nd semaphore

        finished = i++ > 3;

        // TODO: FILL IN THIS LINE
        sem_wait(&mutex3); // locking the 3rd semaphore
        for (int j = 0; j < thread_num; ++j)
        {
            printf("\t\t\t");
        }
        printf("into non-critical(T%d)\n", thread_num);
        // TODO: FILL IN THIS LINE
        sem_post(&mutex3); // releasing the 3rd semaphore
    }
    return NULL;
}

#define N_THREADS 3

int main(int argc, const char *argv[])
{
    // initializing the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&mutex3, 0, 1);

    pthread_t tid[N_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    for (int i = 0; i < N_THREADS; ++i)
    {
        pthread_create(&tid[i], &attr, protect_critical_region, (void *)(long)i);
    }

    for (int i = 0; i < N_THREADS; ++i)
    {
        pthread_join(tid[i], NULL);
    }
    printf("\nall %d threads joined", N_THREADS);
    printf("\n\nEnd of program\n");

    return 0;
}
 
//========================================================================
// EXAMPLE OUTPUT (your output will vary)
//========================================================================
//
// 			CRITICAL(T1)
// CRITICAL(T0)
// 						CRITICAL(T2)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						out of CRITICAL(T2)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
// 			out of CRITICAL(T1)
// 						out of CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// CRITICAL(T0)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						out of CRITICAL(T2)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						out of CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 			CRITICAL(T1)
// 						into non-critical(T2)
// 						CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// 			out of CRITICAL(T1)
// 			into non-critical(T1)
// 						out of CRITICAL(T2)
// 						into non-critical(T2)
//
// all 3 threads joined
//
// End of program
// Program ended with exit code: 0
//
//========================================================================


//========================================================================
// MY OUTPUT
//========================================================================
// CRITICAL(T0)
//                                                 CRITICAL(T2)
//                         CRITICAL(T1)
//                         out of CRITICAL(T1)
//                         into non-critical(T1)
//                         CRITICAL(T1)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
//                                                 out of CRITICAL(T2)
//                                                 into non-critical(T2)
//                                                 CRITICAL(T2)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
//                                                 out of CRITICAL(T2)
//                                                 into non-critical(T2)
//                                                 CRITICAL(T2)
//                         out of CRITICAL(T1)
//                         into non-critical(T1)
//                         CRITICAL(T1)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
//                                                 out of CRITICAL(T2)
//                                                 into non-critical(T2)
//                                                 CRITICAL(T2)
//                         out of CRITICAL(T1)
//                         into non-critical(T1)
//                         CRITICAL(T1)
// out of CRITICAL(T0)
// into non-critical(T0)
// CRITICAL(T0)
//                                                 out of CRITICAL(T2)
//                                                 into non-critical(T2)
//                                                 CRITICAL(T2)
//                         out of CRITICAL(T1)
//                         into non-critical(T1)
//                         CRITICAL(T1)
// out of CRITICAL(T0)
// into non-critical(T0)
//                                                 out of CRITICAL(T2)
//                                                 into non-critical(T2)
//                         out of CRITICAL(T1)
//                         into non-critical(T1)

// all 3 threads joined

// End of program