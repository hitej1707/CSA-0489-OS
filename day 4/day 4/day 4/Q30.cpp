#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int data = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *producer(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        data = i;
        printf("Produced: %d\n", data);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        while (data == 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Consumed: %d\n", data);
        data = 0;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
