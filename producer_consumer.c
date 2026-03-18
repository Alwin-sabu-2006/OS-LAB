#include <stdio.h>

#define SIZE 2

int buffer[SIZE];
int in = 0, out = 0;

int mutex = 1;
int empty = SIZE;
int full = 0;

void wait(int *s)
{
    while(*s <= 0);
    (*s)--;
}

void signal(int *s)
{
    (*s)++;
}

void producer(int id, int item)
{
    if(empty == 0)
        printf("Producer %d waiting, buffer FULL\n", id);

    wait(&empty);
    wait(&mutex);

    buffer[in] = item;
    printf("Producer %d produced item %d\n", id, item);

    in = (in + 1) % SIZE;

    signal(&mutex);
    signal(&full);
}

void consumer(int id)
{
    if(full == 0)
        printf("Consumer %d waiting, buffer EMPTY\n", id);

    wait(&full);
    wait(&mutex);

    int item = buffer[out];
    printf("Consumer %d consumed item %d\n", id, item);

    out = (out + 1) % SIZE;

    signal(&mutex);
    signal(&empty);
}

int main()
{
    consumer(1);   // shows waiting

    producer(1, 10);
    producer(2, 20);

    producer(3, 30);  // shows buffer full waiting

    consumer(2);
    consumer(3);

    return 0;
}
