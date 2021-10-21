#ifndef QUEUE_H
#define QUEUE_H

template<typename T> class Queue
{
protected:
    int Size, Front, Count;
    T *ara;

    void extend();

public:
    Queue();
    Queue(int);

    void enqueue(T t);
    void dequeue();
    T front();
    T back();
    T operator[](int);
    unsigned size();
    bool isEmpty();
};

#include "../src/Queue.cpp"

#endif
