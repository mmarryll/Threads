#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <mutex>
#define ll long long
//#define cin fin
//#define cout fout
using namespace std;
//ifstream fin("/Users/iisuos/Desktop/Test/Hello World/Hello World/ input.txt");
//ofstream fout("/Users/iisuos/Desktop/Test/Hello World/Hello World/output.txt");
bool STOP = false;
mutex m;
void Answer(vector<int>& vec, size_t k) {
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (k & (1 << i)) {
            cout << vec[i] << " ";
        }
    }
}

int main() {
    int n = 0;
    cin >> n;
    vector <int> a(n / 2);
    vector <int> b(n / 2 + n % 2);
    unordered_map <ll, int> s;
    for (size_t i = 0; i < n / 2; i++)
    {
        cin >> a[i];
    }
    for (size_t i = 0; i < n / 2 + n % 2; i++)
    {
        cin >> b[i];
    }
    cout << endl;
    cout << "Enter count of threads: ";
    int sz;
    cin >> sz;
    vector <thread> th;
    // распараллеливание создания всех сумм
    for (size_t k = 1; k <= sz; k++)
    {
        th.emplace_back([&s, &a, sz, k]() {
            for (size_t i = k; i < (1 << a.size()); i += k)
            {
                ll temp = 0;
                for (int j = 0; j < a.size(); j++) {
                    if (i & (1 << j)) {
                        temp += a[j];
                    }
                }
                s.insert(make_pair(temp, i));
            }
            });
    }
    // для хранения потоков будем использовать один и тот же вектор
    for (int i = 0; i < sz; i++)
    {
        th[i].join();
    }
    th.clear();
    if (s.count(0)) {
        Answer(a, s[0]);
        cout << endl;
        return 0;
    }
    // перебор сумм во втором массиве
    for (size_t k = 1; k <= sz; k++)
    {
        th.emplace_back([&s, &b, &a, sz, k]() {
            for (size_t i = k; i < (1 << b.size()); i += k) {
                ll temp = 0;
                for (int j = 0; j < b.size(); j++) {
                    if (i & (1 << j)) {
                        temp += b[j];
                    }
                }
                if (temp == 0) {
                    unique_lock<mutex> guard(m);
                    if (STOP) return;
                    STOP = true;
                    guard.unlock();
                    Answer(b, i);
                    cout << endl;
                    break;
                }
                if (s.count(temp * -1)) {
                    unique_lock<mutex> guard(m);
                    if (STOP) return;
                    STOP = true;
                    guard.unlock();
                    Answer(a, s[temp * -1]);
                    Answer(b, i);
                    cout << endl;
                    break;
                }
            }});
    }
    for (int i = 0; i < sz; i++) {
        th[i].join();
    }
    th.clear();
    cout << "NO" << endl;
}