#ifndef _CIRCULARBUFFER_H_
#define _CIRCULARBUFFER_H_

#include<iostream>
#include<memory>

template <class T> class Circular_Buffer {
private:

  std::unique_ptr<T[]> buffer; 
  size_t head = 0;             
  size_t tail = 0;
  size_t max_size;
  T empty_item; // we will use this to clear data

public:

    Circular_Buffer<T>(size_t max_size);
    void enqueue(T item);
    T dequeue();
    T front();
    bool is_empty();
    bool is_full();
    size_t size();
    T& operator[](int index);
};

#include "CircularBuffer.cpp"
#endif 