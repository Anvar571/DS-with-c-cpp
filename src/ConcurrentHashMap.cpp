#include <iostream>
#include <vector>
#include <list>
#include <shared_mutex>
#include <utility>

template <typename K, typename V>
class ConcurrentHashMap {
private:
    std::vector<std::list<std::pair<K, V>>> table;
    int capacity;
    std::vector<std::shared_mutex> locks;

    int hashFunction(K key) {
        return std::hash<K>()(key) % capacity;
    }

public:
    ConcurrentHashMap(int cap = 10) : capacity(cap) {
        table.resize(capacity);
        locks.resize(capacity);
    }

    void put(K key, V value) {
        int hashValue = hashFunction(key);
        std::unique_lock<std::shared_mutex> lock(locks[hashValue]);
        for (auto& kv : table[hashValue]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        table[hashValue].push_back({key, value});
    }

    bool get(K key, V& value) {
        int hashValue = hashFunction(key);
        std::shared_lock<std::shared_mutex> lock(locks[hashValue]);
        for (auto& kv : table[hashValue]) {
            if (kv.first == key) {
                value = kv.second;
                return true;
            }
        }
        return false;
    }

    void remove(K key) {
        int hashValue = hashFunction(key);
        std::unique_lock<std::shared_mutex> lock(locks[hashValue]);
        table[hashValue].remove_if([key](const std::pair<K, V>& kv) {
            return kv.first == key;
        });
    }
};
