#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;

class LRUCache{
    private:
    size_t cap;
    list<pair<int, int>> order;
    unordered_map<int, list<pair<int, int>>::iterator> index;

    public:
    LRUCache(size_t capacity) : cap(capacity) {}

    int get(int key){
        auto it = index.find(key);
        if (it == index.end()){
            return -1;
        }
        auto node = it->second;
        order.splice(order.begin(), order, node);
        return node->second;
    }
    void put(int key, int val){
        auto it = index.find(key);
        if (it != index.end()){
            it->second->second = val;
            order.splice(order.begin(), order, it->second);
        }
        else{
            if (order.size()==cap){
                index.erase(order.back().first);
                order.pop_back();
            }
            order.push_front({key, val});
            index[key] = order.begin();
        }
    }
};

int main(){
    LRUCache cache(3);
    cache.put(5, 2);
    cache.put(8, 3);
    cache.put(8, 2);
    cache.put(9, 3);
    cout << cache.get(4) << "\n";
    cache.get(8);
    cache.put(3,5);
    cache.put(3,9);
    cout << cache.get(3) << "\n";
    cout << cache.get(5) << "\n";
}
