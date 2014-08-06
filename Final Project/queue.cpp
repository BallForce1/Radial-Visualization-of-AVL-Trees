#pragma once
#include <iostream>
using namespace std;
const int MSIZE = 1000;

class point {
 private:
  int x; int y;

 public:

  point(int p, int q) {
	  x = p; y = q;
    }

  int getx() {
	return x;
   }

  int gety() {
	return y;
   }
 };

class queue {

 private:
  point* Q[MSIZE];

  int front, rear, size;

 public:
  queue() {
   // initialize an empty queue
   front = 0; rear = 0; size = 0;
   for (int j=0; j < MSIZE; ++j)
    Q[j] = 0;
 }

  void insert(point* x) {
   if (size != MSIZE) {
	 front++; size++;
	 if (front == MSIZE) front = 0;
	 Q[front] = x;
    }
 }

 point del() {
  if (size != 0) {
	rear++; if (rear == MSIZE) rear = 0;
	point temp(Q[rear]->getx(), Q[rear]->gety());
	size--;
	return temp;
   }
 }

void print() {
 for (int j = 1; j <= size; ++j) {
   int i = front - j + 1;
   cout << "x = " << Q[i]->getx() << " y = " << Q[i]->gety() << endl;
   }
 cout << "end of queue" << endl;
 }

 bool isEmpty() {
  return (size == 0);
 }
};

