#include <iostream>
#include <pthread.h>

// Structure to hold data for the thread function
struct ThreadData {
    int num1;
    int num2;
    int result;
};

// Function for addition
void* add(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->result = data->num1 + data->num2;
    pthread_exit(NULL);
}

// Function for subtraction
void* subtract(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->result = data->num1 - data->num2;
    pthread_exit(NULL);
}

int main() {
    pthread_t add_thread, sub_thread;
    ThreadData add_data, sub_data;

    // Input numbers
    std::cout << "Enter two numbers: ";
    std::cin >> add_data.num1 >> add_data.num2;
    sub_data.num1 = add_data.num1;
    sub_data.num2 = add_data.num2;

    // Create threads
    pthread_create(&add_thread, NULL, add, (void*)&add_data);
    pthread_create(&sub_thread, NULL, subtract, (void*)&sub_data);

    // Wait for threads to finish
    pthread_join(add_thread, NULL);
    pthread_join(sub_thread, NULL);

    // Output results
    std::cout << "Addition result: " << add_data.result << std::endl;
    std::cout << "Subtraction result: " << sub_data.result << std::endl;

    return 0;
}
