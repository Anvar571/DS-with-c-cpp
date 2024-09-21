#include <iostream>
#include <vector>
#include <list>

template <typename K>
class Set {
private:
    std::vector<std::list<K>> table;
    int capacity;
    int size;

    int hashFunction(K key) {
        return std::hash<K>()(key) % capacity;
    }

public:
    Set(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    void add(K key) {
        int hashValue = hashFunction(key);
        for (auto& k : table[hashValue]) {
            if (k == key) {
                return;
            }
        }
        table[hashValue].push_back(key);
        size++;
    }

    bool contains(K key) {
        int hashValue = hashFunction(key);
        for (auto& k : table[hashValue]) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    void remove(K key) {
        int hashValue = hashFunction(key);
        table[hashValue].remove_if([key](const K& k) {
            return k == key;
        });
    }

    int getSize() {
        return size;
    }
};

int main() {
    Set<std::string> set;
    set.add("key1");
    set.add("key2");

    if (set.contains("key1")) {
        std::cout << "key1 is in the set" << std::endl;
    }
    return 0;
}
