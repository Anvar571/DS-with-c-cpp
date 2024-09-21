#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

typedef struct {
    char* key;
    int value;
} HashNode;

typedef struct {
    HashNode** table;
    int capacity;
} HashMap;

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % CAPACITY;
}

HashMap* createHashMap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->capacity = CAPACITY;
    map->table = (HashNode**)malloc(map->capacity * sizeof(HashNode*));
    for (int i = 0; i < map->capacity; i++) {
        map->table[i] = NULL;
    }
    return map;
}

void put(HashMap* map, const char* key, int value) {
    unsigned long hash = hashFunction(key);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    map->table[hash] = node;
}

int get(HashMap* map, const char* key) {
    unsigned long hash = hashFunction(key);
    if (map->table[hash] != NULL && strcmp(map->table[hash]->key, key) == 0) {
        return map->table[hash]->value;
    }
    return -1; // Value not found
}

void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        if (map->table[i]) {
            free(map->table[i]->key);
            free(map->table[i]);
        }
    }
    free(map->table);
    free(map);
}

int main() {
    HashMap* map = createHashMap();
    put(map, "key1", 10);
    put(map, "key2", 20);

    printf("key1 -> %d\n", get(map, "key1"));
    printf("key2 -> %d\n", get(map, "key2"));

    freeHashMap(map);
    return 0;
}
