#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define READER_COUNT 5
#define WRITER_COUNT 2
#define READ_TIMES 3
#define WRITE_TIMES 2

int account_balance = 2000;
int active_readers = 0;

pthread_mutex_t lock_access;
sem_t writer_control;

void* sync_reader(void* arg) {
    int id = *(int*)arg;
    free(arg);

    for (int i = 0; i < READ_TIMES; i++) {
        pthread_mutex_lock(&lock_access);
        active_readers++;
        if (active_readers == 1) {
            sem_wait(&writer_control);
        }
        pthread_mutex_unlock(&lock_access);

        printf("[SYNC READER-%d] Current Balance: $%d\n", id, account_balance);
        usleep(400000);

        pthread_mutex_lock(&lock_access);
        active_readers--;
        if (active_readers == 0) {
            sem_post(&writer_control);
        }
        pthread_mutex_unlock(&lock_access);

        usleep(500000);
    }
    return NULL;
}

void* sync_writer(void* arg) {
    int id = *(int*)arg;
    free(arg);

    for (int i = 0; i < WRITE_TIMES; i++) {
        sem_wait(&writer_control);

        int amount = (id * 25) + 50;
        account_balance += amount;

        printf("[SYNC WRITER-%d] Updated Balance: $%d (+$%d)\n", id, account_balance, amount);
        usleep(900000);

        sem_post(&writer_control);
        usleep(500000);
    }
    return NULL;
}

void* unsync_reader(void* arg) {
    int id = *(int*)arg;
    free(arg);

    for (int i = 0; i < READ_TIMES; i++) {
        printf("[UNSYNC READER-%d] Balance: $%d\n", id, account_balance);
        usleep(400000);
    }
    return NULL;
}

void* unsync_writer(void* arg) {
    int id = *(int*)arg;
    free(arg);

    for (int i = 0; i < WRITE_TIMES; i++) {
        int amount = (id * 35) + 40;
        account_balance += amount;

        printf("[UNSYNC WRITER-%d] Balance Changed: $%d (+$%d)\n", id, account_balance, amount);
        usleep(800000);
    }
    return NULL;
}

void run_sync() {
    pthread_t readers[READER_COUNT], writers[WRITER_COUNT];

    pthread_mutex_init(&lock_access, NULL);
    sem_init(&writer_control, 0, 1);

    for (int i = 0; i < READER_COUNT; i++) {
        int* reader_id = (int*)malloc(sizeof(int));  // Cast the void* to int*
        *reader_id = i + 1;
        pthread_create(&readers[i], NULL, sync_reader, reader_id);
    }

    for (int i = 0; i < WRITER_COUNT; i++) {
        int* writer_id = (int*)malloc(sizeof(int));  // Cast the void* to int*
        *writer_id = i + 1;
        pthread_create(&writers[i], NULL, sync_writer, writer_id);
    }

    for (int i = 0; i < READER_COUNT; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < WRITER_COUNT; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&lock_access);
    sem_destroy(&writer_control);
}

void run_unsync() {
    pthread_t readers[READER_COUNT], writers[WRITER_COUNT];

    for (int i = 0; i < READER_COUNT; i++) {
        int* reader_id = (int*)malloc(sizeof(int));  // Cast the void* to int*
        *reader_id = i + 1;
        pthread_create(&readers[i], NULL, unsync_reader, reader_id);
    }

    for (int i = 0; i < WRITER_COUNT; i++) {
        int* writer_id = (int*)malloc(sizeof(int));  // Cast the void* to int*
        *writer_id = i + 1;
        pthread_create(&writers[i], NULL, unsync_writer, writer_id);
    }

    for (int i = 0; i < READER_COUNT; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < WRITER_COUNT; i++) {
        pthread_join(writers[i], NULL);
    }
}

int main() {
    printf("Choose Mode: 1 Synchronized 2 Unsynchronized\nPlease enter the choice (1/2): ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nRunning Synchronized Execution...\n");
            run_sync();
            printf("\nSynchronized Execution Completed!\n");
            break;
        case 2:
            printf("\nRunning Unsynchronized Execution...\n");
            run_unsync();
            printf("\nUnsynchronized Execution Completed!\n");
            break;
        default:
            printf("\nInvalid Choice! Please restart the program.\n");
    }
    return 0;
}
