#include <iostream>
#include <pthread.h>
#include <vector>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

int array[ARRAY_SIZE];

// Structure to hold data for the thread function
struct ThreadData {
    int thread_id;
    int start_index;
    int end_index;
    long long int partial_sum;
};

// Function for calculating the sum of a portion of the array
void* calculateSum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partial_sum = 0;
    for (int i = data->start_index; i < data->end_index; ++i) {
        data->partial_sum += array[i];
    }
    pthread_exit(NULL);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    std::vector<ThreadData> thread_data(NUM_THREADS);

    // Initialize array with random values
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % 100;
    }

    // Calculate workload for each thread
    int workload_per_thread = ARRAY_SIZE / NUM_THREADS;
    int extended_workload = ARRAY_SIZE % NUM_THREADS;

    // Create threads and distribute workload
    int start_index = 0;
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].thread_id = i;
        thread_data[i].start_index = start_index;
        thread_data[i].end_index = start_index + workload_per_thread;
        if (i < extended_workload) {
            thread_data[i].end_index++;
        }
        pthread_create(&threads[i], NULL, calculateSum, (void*)&thread_data[i]);
        start_index = thread_data[i].end_index;
    }

    // Wait for threads to finish
    long long int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    // Output total sum
    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}
