#include <bits/stdc++.h>
using namespace std;

class Template <T> RingBuffer{

private:
    size_t tail = 0;
    size_t head = 0;
    size_t count = 0;
    vector<T> buf;

public:
RingBuffer(size_t capacity) : buf(capacity); {}

int size(){
    return count;
}

bool empty(){
    return count == 0;
}

bool full(){
    return count == buf.size();
}

bool push(T& item){
     if (full()){
        return false;
     }
     buf[tail] = item; 
     tail = (tail + 1) % buf.size();
     return true;
}

optional<T> pop(){
    if (empty()){
        return nullopt;
    }
    T item = buf[head];
    head = (head+1) % buf.size();
    return item;
}

optional<T> peak(){
    if (empty()){
    return nullopt;
    }
    T item = buf[head];
    return item;
}


    
