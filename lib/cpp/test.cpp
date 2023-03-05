#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "debug.hpp"

using namespace std;
using namespace __gnu_pbds;

struct sct {
    int a = 1;
    string s = "hello";
};

struct sct2 {
    sct s;
    vector<sct> v = {{2, "a"}, {3, "b"}};
};

STRUCT_DBG(sct, &sct::a, &sct::s);
STRUCT_DBG(sct2, &sct2::s, &sct2::v);

int main() {
    int i = 1;
    float f = 5;
    string s = "123";
    pair<int, string> p = {1, "hello"};
    tuple<int, float, string> t = {1, 2, "a"};
    int arr[] = {1, 5, 2};
    dbg(i, f, s, p, t, arr);

    array<int, 3> arrc = {1};
    vector<int> vec = {4, 5, 6};
    deque<int> dq = {};
    forward_list<int> fl = {3};
    list<int> l = {4, 5, 6};
    dbg(arrc, vec, dq, fl, l);

    stack<int> st;
    st.push(5);
    st.push(2);
    queue<int> qu;
    qu.push(7);
    qu.push(3);
    priority_queue<int> pq;
    pq.push(8);
    pq.push(2);
    pq.push(5);
    dbg(st, qu, pq);

    set<int> ss = {4, 6, 8};
    multiset<int> ms = {4, 4, 8};
    map<int, float> mm = {{4, (float)5}, {7, (float)2.0}};
    multimap<int, string> mum = {{4, "asdf"}, {4, "asdf"}};
    dbg(ss, ms, mm, mum);

    unordered_set<int> uss = {4, 6, 8};
    unordered_multiset<int> ums = {4, 4, 8};
    unordered_map<int, float> umm = {{4, (float)5}, {7, (float)2.0}};
    unordered_multimap<int, string> umum = {{4, "asdf"}, {4, "asdf"}};
    dbg(uss, ums, umm, umum);

    bitset<5> bs;
    bs[0] = 1;
    bs[3] = 1;
    dbg(bs);

    tree<int, null_type, less<int>, rb_tree_tag,
         tree_order_statistics_node_update>
        iss;
    iss.insert(4);
    iss.insert(6);
    gp_hash_table<int, int> ght;
    ght[1] = 2;
    dbg(iss, ght);

    sct obj;
    sct2 obj2;
    dbg(obj, obj2);

    dbg();
}