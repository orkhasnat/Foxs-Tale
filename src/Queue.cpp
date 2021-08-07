#include "Queue.hpp"

Queue::Queue(int s=1): Size(s>0? s: 1), Front(0), Count(0)
{
    ara=new Platform*[Size];
}

Queue::Queue(): Size(1), Front(0), Count(0)
{
    ara=new Platform*[Size];
}

void Queue::extend()
{
    int i;
    Platform *temp[Count];
    for(i=0; i<Count; ++i) temp[i]=ara[(i+Front)%Size];
    Front=0;

    delete[] ara;
    Size*=2;
    ara=new Platform*[Size];
    for(i=0; i<Count; ++i) ara[i]=temp[i];
}

void Queue::enqueue(Platform* platform)
{
    int Back=Front+Count;
    if(Count==Size) extend();
    Back%=Size;
    ara[Back]=platform;
    Count++;
}

void Queue::dequeue()
{
    if(!Count) return;

    delete ara[Front];
    Front++;
    Front%=Size;
    Count--;
}

Platform* Queue::front()
{
    return ara[Front];
}

Platform* Queue::back()
{
    return ara[(Front+Count-1)%Size];
}

Platform* Queue::operator[](int i)
{
    if(i<Count) return ara[(i+Front)%Size];
    return nullptr;
}

unsigned Queue::size()
{
    return Count;
}

bool Queue::isEmpty()
{
    return !Count;
}
