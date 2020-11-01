// Inspired from:
// https://gist.github.com/edwintcloud/d547a4f9ccaf7245b06f0e8782acefaa
#include "CircularBuffer.h"

#include<iostream>
#include<memory>

template <class T> 
Circular_Buffer<T>::Circular_Buffer(size_t max_size)
      : buffer(std::unique_ptr<T[]>(new T[max_size])), max_size(max_size){};

template <class T> 
void Circular_Buffer<T>::enqueue(T item) {

    buffer[tail] = item;

    if( ( (tail+1) % max_size) == head){
      head = (head+1) % max_size;
    }
    // increment tail
    tail = (tail + 1) % max_size;
  }
  
template <class T> 
T Circular_Buffer<T>::dequeue() {
   // if buffer is empty, throw an error
    if (is_empty())
      throw std::runtime_error("buffer is empty");

    // get item at head
    T item = buffer[head];

    // set item at head to be empty
    T empty;
    buffer[head] = empty_item;

    // move head foward
    head = (head + 1) % max_size;

    // return item
    return item;
}

template <class T> 
T Circular_Buffer<T>::front(){
  return buffer[head];
}

template <class T> 
bool Circular_Buffer<T>::is_empty() { 
  return head == tail; 
}

template <class T> 
bool Circular_Buffer<T>::is_full() { 
  return tail == (head - 1) % max_size;
}

template <class T> 
size_t Circular_Buffer<T>::size() { 
  if (tail >= head)
    return tail - head;
  return max_size - (head - tail);
}

template <class T> 
T& Circular_Buffer<T>::operator[](int index) {
  if(index > size()){
    throw std::runtime_error("Value of this index is null ");
  }

  if(index > max_size){
    throw std::runtime_error("Invalid index ");
  }

  return buffer[(head+index) % max_size];
}
