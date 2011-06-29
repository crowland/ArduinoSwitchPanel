#ifndef _QUEUE_H_
#define _QUEUE_H

template<typename T, int MAX_ITEMS>
class Queue
{
  private:
    T queueData[MAX_ITEMS];
    T *queuePtr;
    int top;
    
  public:  
    Queue();
    ~Queue() { }
    
    T pop();
    void push(const T& item);
    
    int empty() const { return top == -1; }
    int full() const { return top == MAX_ITEMS - 1; }    
    int size() const { return top+1; }
};

template<typename T, int N>
Queue<T, N>::Queue():top(-1) 
{
  queuePtr = &queueData[0];
}

template<typename T, int N>
void Queue<T, N>::push(const T& item) 
{
  if (!full()) 
  {
    queuePtr[++top] = item;
  }
}

template<typename T, int N>
T Queue<T, N>::pop() 
{
  if (!empty()) 
  {
    return queuePtr[top--];
  }
  else 
  {
    queuePtr[0];
  }
}

#endif
