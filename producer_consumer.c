#include <stdio.h>

#define SIZE 2

int buffer[SIZE];
int in = 0, out = 0;

int mutex = 1;
int empty = SIZE;
int full = 0;

void producer(int id, int item)
{
    if(empty == 0)
    {
        printf("Producer %d waiting, buffer FULL\n", id);
        return;
    }

    empty--;
    buffer[in] = item;

    printf("Producer %d produced\n", id);

    in = (in + 1) % SIZE;
    full++;
}

void consumer(int id)
{
    if(full == 0)
    {
        printf("Consumer %d waiting, buffer EMPTY\n", id);
        return;
    }

    full--;
    int item = buffer[out];

    printf("Consumer %d consumed\n", id);

    out = (out + 1) % SIZE;
    empty++;
}

int main()
{
    consumer(1);

    producer(1, 10);
    producer(2, 20);

    producer(3, 30);

    consumer(2);
    consumer(3);

    return 0;
}
