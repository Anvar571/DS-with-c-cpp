#include <iostream>
#include <vector>
#include <list>
#include <utility> // for std::pair

template <typename K, typename V>
class HashMap {
private:
    std::vector<std::list<std::pair<K, V>>> table;
    int capacity;
    int size;

    int hashFunction(K key) {
        return std::hash<K>()(key) % capacity;
    }

public:
    HashMap(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    void put(K key, V value) {
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
        int hashValue = hashFunction(key);
        table[hashValue].remove_if([key](const std::pair<K, V>& kv) {
            return kv.first == key;
        });
    }

    int getSize() {
        return size;
    }
};

int main() {
    HashMap<std::string, int> map;
    map.put("key1", 10);
    map.put("key2", 20);

    int value;
    if (map.get("key1", value)) {
        std::cout << "key1 -> " << value << std::endl;
    }
    return 0;
}
