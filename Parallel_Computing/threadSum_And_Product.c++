#include <stdio.h>
#include <iostream>
#include <pthread.h>


struct thread_data{
    int num1;
    int num2;
    int result;
};


void *sum(void *args){
    thread_data* d1 = (thread_data *) args;
    d1->result = d1->num1 + d1->num2;
    printf("%d: Addition done\n",d1->result);
    return NULL;

};

void *sub(void *args){
    thread_data* d1 = (thread_data *) args;
    d1->result = d1->num1 - d1->num2;
    printf("%d: Subtraction done\n",d1->result);
    return NULL;

};

void *product(void *args){
    thread_data* d1 = (thread_data *) args;
    d1->result = d1->num1 * d1->num2;
    printf("%d: Multiplication done\n",d1->result);
    return NULL;

};

void *division(void *args){
    thread_data* d1 = (thread_data *) args;
    d1->result = d1->num1 / d1->num2;
    printf("%d: Division done\n",d1->result);
    return NULL;

};

int main(){
    pthread_t t1,t2,t3,t4;
    thread_data data;
    std::cout << "Enter the numbers for calculations: \n";
    std::cin >> data.num1 >> data.num2;
    pthread_create(&t1,NULL,sum,(void *)&data);
    pthread_create(&t2,NULL,sub,(void *)&data);
    pthread_create(&t3,NULL,product,(void *)&data);
    pthread_create(&t4,NULL,division,(void *)&data);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    printf("All threads done\n");
    return 0;
}