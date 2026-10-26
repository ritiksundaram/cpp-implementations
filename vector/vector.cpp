#include <iostream>
#include <cstddef>
#include <utility>

template <typename T>

class Vector{
    private:
    T* buf;
    size_t cap;
    size_t cur = 0;;

    public:
    explicit Vector(size_t capacity) : cap(capacity) {
        buf = new T[capacity];
    }

    void push_back(const T& value){
        if (cur == cap){
            grow();
        }
        buf[cur] = value;
        cur++;
    }
    Vector(const Vector& other){
        buf = new T[other.cap];
        for (size_t i=0; i<other.cur; i++){
            buf[i] = other.buf[i];
        }
        cap = other.cap;
        cur = other.cur;
    }
    ~Vector(){
        delete[] buf;
    }
    Vector(Vector&& other) noexcept{
        buf = other.buf;
        cap = other.cap;
        cur = other.cur;
        other.buf = nullptr;
        other.cap = 0;
        other.cur = 0;
    }
    Vector& operator=(const Vector& other){
        if (this == &other){
            return *this;
        }
        
        T* newData = new T[other.cap];
        for (size_t i=0; i<other.cur; i++){
            newData[i] = other.buf[i];
        }
        delete[] buf;
        buf = newData;
        cur = other.cur;
        cap = other.cap;
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept{
        if (this == &other){
            return *this;
        }
        delete[] buf;
        buf = other.buf;
        cap = other.cap;
        cur = other.cur;
        other.buf = nullptr;
        other.cur = 0;
        other.cap = 0;
        return *this;
    }
    void grow(){
         if (cap==0) cap = 1;
         else{
            cap = cap * 2;
         }
         T* newData = new T[cap];
         for (size_t i = 0; i<cur; i++){
            newData[i] = buf[i];
         }
         delete[] buf;
         buf = newData;
    }
    size_t size() const{
        return cur;
    }
    size_t capacity() const{
        return cap;
    }
};

int main(){
        Vector<int> v(4);
        for (int i=0; i<10; i++){
        v.push_back(i);
        std::cout << v.size() << " " << v.capacity() << "\n";
    }
    Vector<int> w = v;
    w.push_back(99);
    std::cout << v.size() << " " << w.size() << "\n";
    Vector<int> m = std::move(w);
    std::cout << m.size() << " " << w.size() << "\n";
    Vector<int> a(2);
    a.push_back(7);
    a = v;
    std::cout << a.size() << " " << v.size() << "\n";
    a.push_back(100);
    std::cout << a.size() << " " << v.size() << "\n";
    Vector<int> b(2);
    b.push_back(5);
    b = std::move(a);
    std::cout << b.size() << " " << a.size() << "\n";
}