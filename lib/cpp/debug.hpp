#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include "json.hpp"

template <typename T,
          typename = std::decay_t<decltype(json::JSON(std::declval<T>()))>>
json::JSON _serialize(const T &obj);

template <typename K, typename V>
json::JSON _serialize(const std::pair<K, V> &p);

template <typename... Args>
json::JSON _serialize(const std::tuple<Args...> &t);

template <typename T, std::size_t N>
json::JSON _serialize(T (&arr)[N]);

template <typename T,
          typename = std::decay_t<decltype(*std::begin(std::declval<T>()))>,
          typename = std::enable_if_t<!std::is_same_v<T, std::string>>>
json::JSON _serialize(const T &obj);

template <class T>
json::JSON _serialize(const std::queue<T> &q);

template <class T>
json::JSON _serialize(const std::stack<T> &s);

template <class T>
json::JSON _serialize(const std::priority_queue<T> &q);

template <std::size_t N>
json::JSON _serialize(const std::bitset<N> &b);

std::vector<std::string> _split_function_args(const std::string &s);

template <typename T, typename... Args>
json::JSON _serialize_struct_members(const T &obj,
                                     const std::vector<std::string> &members,
                                     Args... args);

template <typename T,
          typename = std::decay_t<decltype(json::JSON(std::declval<T>()))>>
json::JSON _serialize(const T &obj) {
    return json::JSON(obj);
}

template <typename K, typename V>
json::JSON _serialize(const std::pair<K, V> &p) {
    json::JSON json_obj = json::JSON::Make(json::JSON::Class::Array);
    json_obj.append(_serialize(p.first), _serialize(p.second));
    return json_obj;
}

template <typename... Args>
json::JSON _serialize(const std::tuple<Args...> &t) {
    json::JSON json_obj = json::JSON::Make(json::JSON::Class::Array);
    std::apply(
        [&json_obj](const auto &...args) {
            ((json_obj.append(_serialize(args))), ...);
        },
        t);
    return json_obj;
}

template <typename T, std::size_t N>
json::JSON _serialize(T (&arr)[N]) {
    return _serialize(std::vector<typename std::remove_const<T>::type>(
        std::begin(arr), std::end(arr)));
}

template <typename T,
          typename = std::decay_t<decltype(*std::begin(std::declval<T>()))>,
          typename = std::enable_if_t<!std::is_same_v<T, std::string>>>
json::JSON _serialize(const T &obj) {
    json::JSON json_obj = json::JSON::Make(json::JSON::Class::Array);
    for (auto it = std::begin(obj); it != std::end(obj); it++) {
        json_obj.append(_serialize(*it));
    }
    return json_obj;
}

template <class T>
json::JSON _serialize(const std::queue<T> &q) {
    std::queue<T> obj(q);
    std::vector<T> t;
    while (!obj.empty()) t.push_back(obj.front()), obj.pop();
    return _serialize(t);
}

template <class T>
json::JSON _serialize(const std::stack<T> &s) {
    std::stack<T> obj(s);
    std::vector<T> t;
    while (!obj.empty()) t.push_back(obj.top()), obj.pop();
    std::reverse(t.begin(), t.end());
    return _serialize(t);
}

template <class T>
json::JSON _serialize(const std::priority_queue<T> &q) {
    std::priority_queue<T> obj(q);
    std::vector<T> t;
    while (!obj.empty()) t.push_back(obj.top()), obj.pop();
    return _serialize(t);
}

template <std::size_t N>
json::JSON _serialize(const std::bitset<N> &b) {
    json::JSON json_obj = json::JSON::Make(json::JSON::Class::Array);
    for (std::size_t i = 0; i < N; ++i) {
        json_obj[i] = _serialize(b[i] ? 1 : 0);
    }
    return json_obj;
}

std::vector<std::string> _split_function_args(const std::string &s) {
    int f = 0, q = 0;
    std::vector<std::string> args = {""};
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == ',' && !q && !f) {
            args.push_back("");
            i++;
            continue;
        }
        args.back().push_back(s[i]);
        if (s[i] == '\\') {
            args.back().push_back(s[++i]);
            args.back().push_back(s[++i]);
        }
        if (s[i] == '\"') q = !q;
        if (s[i] == '(' && !q) f++;
        if (s[i] == ')' && !q) f--;
    }
    return args;
}

template <typename T, typename... Args>
json::JSON _serialize_struct_members(const T &obj,
                                     const std::vector<std::string> &members,
                                     Args... args) {
    int count = 0;
    json::JSON json_obj = json::JSON::Make(json::JSON::Class::Array);
    (((json_obj.append(json::JSON(
          {"id", members[count].substr(members[count].find("::") + 2), "value",
           _serialize(obj.*args)}))),
      count++),
     ...);
    return json_obj;
}

#define STRUCT_DBG(struct_obj, ...)                                \
    json::JSON _serialize(const struct_obj &obj) {                 \
        return _serialize_struct_members(                          \
            obj, _split_function_args(#__VA_ARGS__), __VA_ARGS__); \
    }

bool print_on_exit = false;
json::JSON debug_data;

#define dbg(...)                                                          \
    [](const auto &...x) {                                                \
        json::JSON obj({"line", __LINE__, "content", json::JSON()});      \
        std::vector<std::string> vs = _split_function_args(#__VA_ARGS__); \
        int ind = 0;                                                      \
        ((obj["content"].append(                                          \
             json::JSON({"id", vs[ind++], "value", (_serialize(x))}))),   \
         ...);                                                            \
        debug_data.append(obj);                                           \
        if (!print_on_exit)                                               \
            std::atexit([]() { std::cerr << debug_data << "\n"; }),       \
                print_on_exit = true;                                     \
    }(__VA_ARGS__)
