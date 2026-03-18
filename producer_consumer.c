#include <stdio.h>

int readcount = 0;
int writecount = 0;

int mutex = 1;      // controls readcount
int resource = 1;   // shared resource
int readTry = 1;    // used to block readers when writer comes

void wait(int *s)
{
    while(*s <= 0);   // wait
    (*s)--;           // enter
}

void signal(int *s)
{
    (*s)++;           // leave
}

void reader(int id)
{
    wait(&readTry);       // check if writer waiting
    wait(&mutex);
    readcount++;

    if(readcount == 1)
        wait(&resource);  // first reader locks resource

    signal(&mutex);
    signal(&readTry);

    printf("Reader %d is reading\n", id);

    wait(&mutex);
    readcount--;

    if(readcount == 0)
        signal(&resource); // last reader releases resource

    signal(&mutex);
}

void writer(int id)
{
    wait(&readTry);      // block readers
    wait(&resource);     // get resource

    printf("Writer %d is writing\n", id);

    signal(&resource);
    signal(&readTry);    // allow readers again
}

int main()
{
    reader(1);
    reader(2);
    writer(1);
    reader(3);
    writer(2);

    return 0;
}
