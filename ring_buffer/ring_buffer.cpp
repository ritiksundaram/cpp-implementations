#include <vector>
#include <optional>
#include <iostream>
using namespace std;
template <typename T>
class RingBuffer{
    private:
    size_t head = 0;
    size_t tail = 0;
    size_t current = 0;
    vector<T> buf;
    
    public:
    explicit RingBuffer(size_t capacity) : buf(capacity) {}
    
    size_t size() const{
        return current;
    }
    bool empty() const{
        if (current==0){
            return true;
        }
        else{
            return false;
        }
    }
    bool full() const{
        if (current == buf.size()){
            return true;
        }
        else{
            return false;
        }
    }
    bool push(const T& item){
        if (full()){
            return false;
        }
        buf[tail] = item;
        tail = (tail+1) % buf.size();
        current++;
        return true;
    }
    optional<T> pop(){
        if (empty()){
            return nullopt;
        }
        T item = buf[head];
        head = (head+1) % buf.size();
        current--;
        return item;
    }
    optional<T> peek() const{
        if (empty()){
            return nullopt;
        }
        return buf[head];
    }
};

int main(){
    RingBuffer<int> rb(3);
    rb.push(3);
    rb.push(5);
    rb.push(7);
    cout << rb.full() << "\n";
    cout << rb.empty() << "\n";
    cout << rb.push(9) << "\n";
    cout << *rb.pop() << " " << rb.size() << "\n";
    auto x = rb.pop();
    cout << (x ? "has value" : "empty") << "\n";

}
