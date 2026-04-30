#include <cassert>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue{
private: 
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;

public:
    void push(T value){
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        cv_.notify_one();
    }
    bool pop(T& value){
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()){
            return false;
        }
        value = queue_.front();
        queue_.pop();
        return true;
    }

    void wait_and_pop(T& value){
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] {return !queue_.empty();});
        value = queue_.front();
        queue_.pop();
    }

    bool empty() const{
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    size_t size() const{
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }
};   

int main(){
    ThreadSafeQueue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    int val;
    q.pop(val);
    assert(val==1);
    q.pop(val);
    assert(val==2);
    q.pop(val);
    assert(val==3);
    assert(q.empty());
};