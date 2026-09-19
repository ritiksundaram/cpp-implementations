#include <bits/stdc++.h>
using namespace std;

struct Detection {
    long long timestamp;
    string contactId;
    double range;
};

vector<string> confirmedContacts(const vector<Detection>& detections, int k) {
    // your code
    vector<pair<long long, string>> temp; 
    unordered_map<string, pair<int, long long>> seen;
    vector<string> result;
    for (int i=0; i<detections.size(); i++){
        const auto& det = detections[i];
        auto it = seen.find(det.contactId);
        if (it == seen.end()){
            seen[det.contactId] = {1, det.timestamp};
        }
        else{
            it->second.first++; 
            it->second.second = min(it->second.second, det.timestamp);
        }
    }
    for (auto [id, val] : seen){
        if (val.first >= k){
                temp.push_back({val.second, id});
        }
    }
    sort(temp.begin(), temp.end());
    for (auto s : temp){
        result.push_back(s.second);
    }
    return result;

}

int main() {
    vector<Detection> d = {
        {100, "C1", 850}, {101, "C2", 1200}, {102, "C1", 845},
        {103, "C3", 400}, {104, "C1", 840}, {105, "C2", 1190},
    };
    for (auto& id : confirmedContacts(d, 2)) cout << id << " ";
    cout << "\n";
}
