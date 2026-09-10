#include <iostream>
#include <queue>
#include <mutex>
#include <optional>
#include <condition_variable>
#include <thread>
using namespace std;

template <typename T>

class ThreadSafeQueue{
    private:
    queue<T> q;
    mutex mtx;
    condition_variable cv;

    public: 
    void push(const T& item){
        lock_guard<mutex> lock(mtx);
        q.push(item);
        cv.notify_one();
    }
    
    optional<T> try_pop(){
        lock_guard<mutex> lock(mtx);
        if (q.empty()){
            return nullopt;
        }
        T item = q.front();
        q.pop();
        return item;
    }

    size_t size(){
        lock_guard<mutex> lock(mtx);
        size_t cursize = q.size();
        return cursize;
    }

    bool empty(){
        lock_guard<mutex> lock(mtx);
        return q.size() == 0;
    }
    T pop(){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]{return !q.empty();});
        T item = q.front();
        q.pop();
        return item;
    }
};

int main() {
    ThreadSafeQueue<int> tq;
    thread producer([&]{ for (int i = 0; i < 5; i++) tq.push(i); });
    thread consumer([&]{ for (int i = 0; i < 5; i++) cout << tq.pop() << " "; });
    producer.join();
    consumer.join();
    cout << "\n";
}
