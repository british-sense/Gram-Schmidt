#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;

template <typename T>
void operator+=(std::vector<T> &lhs, std::vector<T> rhs) {
    for(int i = 0; i < lhs.size(); i++) lhs[i] += rhs[i];
}

template <typename T>
void operator-=(std::vector<T> &lhs, std::vector<T> rhs) {
    for(int i = 0; i < lhs.size(); i++) lhs[i] -= rhs[i];
}

template <typename T1, typename T2>
std::vector<T1> operator*(const T2 value, std::vector<T1> vec) {
    for(auto itr = vec.begin(); itr != vec.end(); itr++) *itr *= value;
    return vec;
}

template <typename T1, typename T2>
std::vector<T1> operator/(std::vector<T1> vec, const T2 value) {
    for(auto itr = vec.begin(); itr != vec.end(); itr++) *itr /= value;
    return vec;
}

// 内積
double inner_product(std::vector<double> A, std::vector<double> B){
    double value = 0;
    if(A.size() != B.size()) std::cerr << "the number of dimension of vector is different." << std::endl;
    for(int i = 0; i < A.size(); i++) value += A[i] * B[i];
    return value;
}

random_device seed;
mt19937 mt(seed()); 

static const int dimension = 3;
static const int num = 3;

void gram_schimidt(vector<vector<double> > vec){

    vector<vector<double> > norm_vec;

    for(int k = 0; k < vec.size(); k++){
        vector<double> sum_vec(dimension, 0);
        for(int i = 0; i < k; i++){
            sum_vec += inner_product(vec[k], norm_vec[i]) * norm_vec[i];
        }
        vec[k] -= sum_vec;
        if(count(vec[k].begin(), vec[k].end(), 0) == dimension){
            vec.erase(vec.begin() + k);
            k--;
            continue;
        } 
        norm_vec.push_back(vec[k] / sqrt(inner_product(vec[k], vec[k])));
    }

    for(auto v : norm_vec){
        for(auto x : v){
            cout << x << " ";
        }
        cout << endl;
    }
}

int main(){

    normal_distribution<> norm(0.0, 1.0);
    vector<vector<double> > vec(num, vector<double>(dimension));
    for(auto v = vec.begin(); v != vec.end(); v++) for(auto x = v->begin(); x != v->end(); x++) *x = norm(mt);
  
    for(auto v : vec){
        for(auto x : v){
            cout << x << " ";
        }
        cout << endl;
    }

    cout << "---orthogonalization---" << endl;
    gram_schimidt(vec);

    return 0;
}
