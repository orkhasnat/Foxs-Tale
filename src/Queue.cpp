#include "Queue.hpp"

#ifndef QUEUE_T
#define QUEUE_T

template<typename T> Queue<T>::Queue(int s): Size(s>0? s: 1), Front(0), Count(0)
{
    ara=new T[Size];
}

template<typename T> Queue<T>::Queue(): Size(1), Front(0), Count(0)
{
    ara=new T[Size];
}

template<typename T> void Queue<T>::extend()
{
    int i;
    T temp[Count];
    for(i=0; i<Count; ++i) temp[i]=ara[(i+Front)%Size];
    Front=0;

    delete[] ara;
    Size*=2;
    ara=new T[Size];
    for(i=0; i<Count; ++i) ara[i]=temp[i];
}

template<typename T> void Queue<T>::enqueue(T t)
{
    int Back=Front+Count;
    if(Count==Size) extend();
    Back%=Size;
    ara[Back]=t;
    Count++;
}

template<typename T> void Queue<T>::dequeue()
{
    if(!Count) return;

    Front++;
    Front%=Size;
    Count--;
}

template<typename T> T Queue<T>::front()
{
    return ara[Front];
}

template<typename T> T Queue<T>::back()
{
    return ara[(Front+Count-1)%Size];
}

template<typename T> T Queue<T>::operator[](int i)
{
    if(i<Count) return ara[(i+Front)%Size];
    return 0;
}

template<typename T> unsigned Queue<T>::size()
{
    return Count;
}

template<typename T> bool Queue<T>::isEmpty()
{
    return !Count;
}

#endif
