#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <cmath>
#include <algorithm>

template<class T>
class Hashtable {
private:
  int count;
  std::vector<std::vector<T>> buckets;
public:
  //Create a hash table with 101 initial buckets (a prime number)
  Hashtable() : Hashtable(101) { }

  Hashtable(const int &buckets) : count(0) {
    this->buckets.resize(std::max(1, buckets));
  }

  void insert(const T t) {
    //Fetch the correct vector from our buckets
    std::vector<T> &v = buckets[hash(t)];
    //Check if the value already exists
    if (std::find(v.begin(), v.end(), t) != v.end()) return;
    //Value does not exist, add it ...
    v.push_back(t);
    //Rehash if necessary
    if (++count > buckets.size()) rehash();
  }

  void remove(const T t) {
    //Fetch the correct vector from our buckets
    std::vector<T> &v = buckets[hash(t)];
    //Check if the value exists
    auto pos = std::find(v.begin(), v.end(), t);
    if (pos == v.end()) return;
    //Erase the value
    v.erase(pos);
    --count;
  }

  int size() { return count; }

private:
  void rehash() {
    std::vector<T> temp;
    //Collect all entries in hashtable
    for (auto &v : buckets) for (auto t : v) temp.push_back(t);
    //Remove them all
    for (auto t : temp) remove(t);
    //Resize our buckets
    buckets.resize(buckets.size() * 2);
    //Repopulate hashtable
    for (auto t : temp) insert(t);
  }

  inline int hash(const T &t) { return t % buckets.size(); }
};

#endif