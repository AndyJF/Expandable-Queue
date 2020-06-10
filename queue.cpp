/*	cs515 Assignment 4P
File: queue.cpp
Name: Andrew Fischer
Section: 01
Date: 6/9/20
Collaboration Declaration: assistance received from Prof. Plumlee.
*/

#include "queue.h"

// Circular array implementation of queue
queue::queue(int capacity)
: _capacity(capacity) {
    _front = 0;  // Index of front element in queue.
	_arr = new TYPE[_capacity];
	_size = 0;  // Amount of elements in queue.
}

// Enqueues values into an expandable circular array.
void queue::enqueue(int data){
	// Expand the queue when queue is full.
	if ((_front + _size) >= _capacity && _size >= _capacity) {
		int new_capacity = _capacity * 2;
		TYPE* _doubledArr = new TYPE[new_capacity];
		for (int i = 0; i < _capacity; i++) {
			_doubledArr[i] = _arr[i];
		}
		delete [] _arr;
		_arr = _doubledArr;
		_size++;
		_capacity = new_capacity;
		_arr[(_front + _size - 1) % _capacity] = data;
	} else {
	_size++;
    _arr[(_front + _size - 1) % _capacity] = data;
	}
}

// Remove element from front of queue.
int queue::dequeue(){
	if (_size == 0) {
		throw EmptyQueueException();
	}
	_size--;
    return _arr[_front++ % _capacity];
}

// Outputs elements in queue from queue
// front to queue end.
void queue::dump(ostream &os){
	if (_front > ((_front + _size - 1) % _capacity)) {
		for(int i = _front; i <= _capacity-1; i++) {
			os<<_arr[i]<<" ";
		}
		for(int i = 0; i <= ((_front + _size - 1) % _capacity); i++) {
			os<<_arr[i]<<" ";
		}
	} else {
		for(int i = _front; i <= ((_front + _size - 1) % _capacity); i++) {
			os<<_arr[i]<<" ";
		}
	}
	os<<"\n";
}

int queue::size(){
    return _size;
}

bool queue::empty(){
	if (size() == 0) {
		return true;
	} else {
		return false;
	}
}

// access the element at queue front; does not remove the element
TYPE& queue::front() {
	if (_size == 0) {
		throw EmptyQueueException();
	} else {
	return _arr[_front];
	}
}

// return the current capacity of the queue
int  queue::capacity() {
	return _capacity;
}

// Destructor
// Frees up dynamically allocated memory.
// Simply delete variables initialized with "new".
queue::~queue() {
	delete []_arr;
}

// Copy constructor
// Creates a new dynamic array using deep copy
// with same values as previous array.
queue::queue(const queue& q)
: _front(q._front), _size(q._size), _capacity(q._capacity)
{
	_arr = new TYPE[_capacity];
	for (int i = 0; i < _capacity; i++) {
		_arr[i] = q._arr[i];
	}
}

// Assignment operator
// Takes values from old array and overwrites
// values of already existing new array.
queue& queue::operator = (const queue& q) {
	if (this == &q) {
		return *this;
	}
	delete []_arr;
	_front = q._front; _size = q._size; _capacity = q._capacity; 
	// If queue is not empty, allocate and copy
	// from original array like copy constructor.
	if (_size > 0) {
		_arr = new TYPE[_capacity];
		for (int i = 0; i < _capacity; i++) {
			_arr[i] = q._arr[i];
		}
	}
	return *this;
}