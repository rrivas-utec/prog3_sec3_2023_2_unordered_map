#include <iostream>
#include <unordered_map>
#include <functional>
using namespace std;

void ejemplo_1() {
    unordered_map<int, char> um1 {
        {10, 'A'},
        {5, 'B'},
        {18, 'Z'},
        {11, 'C'},
        {1, 'D'}};
    cout << size(um1) << endl;
    cout << um1.bucket_count() << endl;
    cout << um1[18] << endl;
    cout << um1[5] << endl;

    unordered_map<int, char, hash<int>, equal_to<>> um2;
}

template <typename T>
struct point {
    T x;
    T y;
    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }
};

// Functor del tipo hash
template <typename T>
struct point_hash {
    size_t operator()(const point<T>& p) const {
        // Prehashing
        hash<T> fun_pre_hashing;
        auto phv = fun_pre_hashing(p.x) ^ fun_pre_hashing(p.y) + 1;
        return phv;
    }
};

struct persona {
    string name;
};

void ejemplo_2() {
    unordered_map<int, string> um1;
    unordered_map<point<int>, persona, point_hash<int>> um2;
    um2.insert( {{1, 1}, {"Jose"}});
    um2.insert( {{2, 2}, {"Rosa"}});

    auto it = um2.find({2, 2});
    if (it != end(um2))
        cout << it->second.name; // En el it->first se encuentra el key {2, 2}
}

void ejemplo_3() {
    unordered_map<int, string> um1;
    auto hash_lambda = [](auto p) {
        hash<int> fun_pre_hashing;
        auto phv = fun_pre_hashing(p.x) ^ fun_pre_hashing(p.y) + 1;
        return phv;
    };
    unordered_map<point<int>, persona, decltype(hash_lambda)> um2(13, hash_lambda);
    um2.insert( {{1, 1}, {"Jose"}});
    um2.insert( {{2, 2}, {"Rosa"}});

    auto it = um2.find({2, 2});
    if (it != end(um2))
        cout << it->second.name; // En el it->first se encuentra el key {2, 2}
}

void ejemplo_4() {
    hash<int> fun_ph_int;
    hash<string> fun_ph_string;
    // Convertir un string a numero
    auto phv = fun_ph_string("Jose");
    cout << phv << " " << "jose" << endl;
    auto phv1 = fun_ph_int(123);
    cout << phv1 << " " << 123 << endl;
    auto phv2 = fun_ph_int(-123);
    cout << phv2 << " " << -123 << endl;

}

int main() {
//    ejemplo_1();
//    ejemplo_2();
    ejemplo_3();
    return 0;
}
