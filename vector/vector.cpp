#include <cstddef>
#include <iostream>

template <typename T>
class Vector {
private:
    T* data;
    size_t cap;
    size_t cur = 0;
public:
    explicit Vector(size_t capacity) : cap(capacity){
        data = new T[capacity];
    }
    ~Vector(){
        delete[] data;
    }
    Vector(const Vector&);
    Vector& operator=(const Vector&);
    Vector(Vector&&) noexcept;
    Vector& operator=(Vector&&) noexcept;

    void push_back(const T& value){
        if (cur == cap){
            grow();
        }
        data[cur] = value;
        cur++;
    }
    void pop_back();
    T& operator[](size_t);
    const T& operator[](size_t) const;
    size_t size() const{
        return cur;
    }
    size_t capacity() const{
        return cap;
    }
    bool empty() const;
    void reserve(size_t);
    void shrink_to_fit();
    void clear();
private:
    void grow(){
        if (cap==0) cap = 1;
        else {
            cap = cap * 2;
        }
        T* newData = new T[cap];
        for (size_t i=0; i<cur; i++){
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
};

int main(){
    Vector<int> v(0);
    for (int i=0; i<10; i++){
        v.push_back(i);
        std::cout << v.size() << " " << v.capacity() << "\n";
    }
}
