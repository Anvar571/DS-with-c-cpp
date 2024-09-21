#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <mutex>

template <typename K, typename V>
class ThreadSafeMap {
private:
    std::vector<std::list<std::pair<K, V>>> table;
    int capacity;
    int size;
    std::mutex mtx;

    int hashFunction(K key) {
        return std::hash<K>()(key) % capacity;
    }

public:
    ThreadSafeMap(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    void put(K key, V value) {
        std::lock_guard<std::mutex> lock(mtx);
        int hashValue = hashFunction(key);
        for (auto& kv : table[hashValue]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        table[hashValue].push_back({key, value});
        size++;
    }

    bool get(K key, V& value) {
        std::lock_guard<std::mutex> lock(mtx);
        int hashValue = hashFunction(key);
        for (auto& kv : table[hashValue]) {
            if (kv.first == key) {
                value = kv.second;
                return true;
            }
        }
        return false;
    }

    void remove(K key) {
        std::lock_guard<std::mutex> lock(mtx);
        int hashValue = hashFunction(key);
        table[hashValue].remove_if([key](const std::pair<K, V>& kv) {
            return kv.first == key;
        });
    }

    int getSize() {
        std::lock_guard<std::mutex> lock(mtx);
        return size;
    }
};
