#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define M 500  // Rows of A and C
#define N 500  // Columns of A, Rows of B
#define P 500  // Columns of B and C
#define NUM_THREADS 4  // Number of threads

int A[M][N], B[N][P], C[M][P];  // Matrices
pthread_t threads[NUM_THREADS];  // Thread handles

// Struct to pass arguments to threads
typedef struct {
    int start_row;
    int end_row;
} ThreadData;

// Function to initialize matrices with random values
void initialize_matrices() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10; // Random numbers between 0-9
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = rand() % 10; // Random numbers between 0-9
        }
    }
}

// Sequential matrix multiplication
void sequential_multiplication() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function executed by each thread
void *thread_multiply(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    struct timeval start, end;
    
    gettimeofday(&start, NULL); // Start time

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL); // End time
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    
    printf("Thread processing rows %d to %d took %f seconds\n", data->start_row, data->end_row, time_taken);
    
    pthread_exit(NULL);
}

// Parallel matrix multiplication using threads
void parallel_multiplication() {
    ThreadData thread_data[NUM_THREADS];
    int rows_per_thread = M / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == NUM_THREADS - 1) ? M : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, thread_multiply, (void *)&thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

// Main function
int main() {
    struct timeval start, end;
    
    initialize_matrices();

    // Sequential execution
    gettimeofday(&start, NULL);
    sequential_multiplication();
    gettimeofday(&end, NULL);
    double seq_time = (end.tv_sec - start.tv_sec) * 1e6;
    seq_time = (seq_time + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Sequential execution took %f seconds\n", seq_time);

    // Parallel execution
    gettimeofday(&start, NULL);
    parallel_multiplication();
    gettimeofday(&end, NULL);
    double par_time = (end.tv_sec - start.tv_sec) * 1e6;
    par_time = (par_time + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Parallel execution took %f seconds\n", par_time);

    return 0;
}

