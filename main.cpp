#include <iostream>
using namespace std;

class Kqueues{
  public:
    int* arr;
    int n;
    int k;
    int* front;
    int*rear;
    int* next;
    int freeSpot;
  public:
    Kqueues(int n, int k){
      this->n = n;
      this->k = k;
      arr = new int[n];
      front = new int[k];
      rear = new int[k];
      
      // initializing front and rear with -1
      for(int i = 0; i < k; i++){
        front[i] = rear[i] = -1;
      }

      // marking every free spot
      next = new int[n];
      for(int i = 0; i < n; i++){
        next[i] = i+1;
      }
      next[n-1] = -1;
      freeSpot = 0;
    }

    bool enqueue(int data, int qn){
      // check for overflow
      if(freeSpot == -1){
        cout<<"No empty space is present"<<endl;
        return false;
      }

      int index = freeSpot;
      freeSpot = next[index];

      // 1st element
      if(front[qn - 1] == -1){
        front[qn - 1] = index;
      }
      else{
        // link new element to the previous element
        next[rear[qn - 1]] = index;
      }

      // update next
      next[index] = -1;

      // update rear
      rear[qn - 1] = index;

      // push
      arr[index] = data;

      return true;
    }

    int dequeue(int qn){
      // check for underflow
      if(front[qn - 1] == -1){
        cout<<"No element is present"<<endl;
        return -1;
      }

      // index find
      int index = front[qn - 1];

      // update front
      front[qn - 1] = next[index];

      // update next
      next[index] = freeSpot;
      freeSpot = index;

      return arr[index];
    }

};

int main() {
  Kqueues q(10, 3);
  cout<<q.enqueue(10, 1)<<endl;
  q.enqueue(15, 1);
  q.enqueue(20, 2);
  q.enqueue(25, 1);
  cout<<q.dequeue(1)<<endl;
  cout<<q.dequeue(2)<<endl;
  cout<<q.dequeue(1)<<endl;
  q.enqueue(30, 1);
}