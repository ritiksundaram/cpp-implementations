#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

class TrackStore{
    private:
    map<int, int> ivs;

    public:
    bool query(int t) const{
        auto it = ivs.upper_bound(t);
        if (it==ivs.begin()){
            return false;
        }
        --it;
        if (it->second < t){
            return false;
        }
        return true;
    }
    void add(int start, int end){
        auto it = ivs.lower_bound(start);
        if (it!=ivs.begin()){
            auto peek = it;
            --peek;
            if (start<=peek->second){
                it=peek;
            }
        }
        while (it != ivs.end() && it->first <= end){
            start = min(it->first, start);
            end = max(it->second, end);
            it = ivs.erase(it);
        }
        ivs[start] = end;
    }
    vector<pair<int, int>> intervals() const{
        vector<pair<int, int>> result;
        for (auto [k, v] : ivs){
            result.push_back({k, v});
        }
        return result;
    }
};

int main(){
    TrackStore ts;
    ts.add(1,3);
    ts.add(6,9);
    ts.add(12,15);
    ts.add(2,5);
    auto ivs = ts.intervals();
    for (auto [k, v] : ivs){
            cout << k << " " << v << "\n";
    }
    bool a = ts.query(7);
    bool b = ts.query(13);
    cout << a << " " << b << "\n";
}
