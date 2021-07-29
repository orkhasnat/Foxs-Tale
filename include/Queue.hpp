#ifndef QUEUE_H
#define QUEUE_H

#include "Platform.hpp"

class Queue
{
protected:
    int Size, Front, Count;
    Platform **ara;

    void extend();

public:
    Queue();
    Queue(int);

    void enqueue(Platform* platform);
    void dequeue();
    Platform* front();
    Platform* back();
    Platform* operator[](int);
    unsigned size();
    bool isEmpty();
};

#endif
