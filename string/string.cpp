#include <cstring>
#include <iostream>
#include <utility>

using namespace std;

class String{
    private:
    char* data;
    size_t len;

    public:
    String(const char* s) : len(strlen(s)) {
        data = new char[len+1];
        memcpy(data, s, len + 1);
    }
    String(const String& other) : len(other.len){
        data = new char[len+1];
        memcpy(data, other.data, len + 1);
    }
    String& operator= (const String& other){
        if (this == &other){
            return *this;
        }
        delete[] data;
        len = other.len;
        data= new char[other.len+1];
        memcpy(data, other.data, len+1);
        return *this;
    }
    String(String&& other) noexcept : data(other.data), len(
        other.len){
            other.data = nullptr;
            other.len = 0;
    }
    String& operator=(String&& other) noexcept{
        if (this==&other){
            return *this;
        }
        delete[] data;
        data = other.data;
        len = other.len;
        other.data = nullptr;
        other.len = 0;
        return *this;
    }
    ~String(){
        delete[] data;
    }
    size_t size() const{
        return len;
    }

    const char* c_str() const{
        return data;
    }
};

int main(){
    String a("heybro");
    cout << a.c_str() << " " << a.size() << "\n";
    String b = a;
    cout << b.c_str() << "\n";
    String c("x"); c = a;
    cout << c.c_str();
    String d = std::move(a);
    cout << "\n" << d.c_str() << " " << a.size() << "\n";
    String e("y"); e = std::move(d);
    cout << e.c_str() << " " << d.size() << "\n";
}
