#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define CAPACITY 10

typedef struct {
    char* key;
    int value;
} HashNode;

typedef struct {
    HashNode** table;
    int capacity;
    pthread_mutex_t* locks;
} ThreadSafeMap;

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % CAPACITY;
}

ThreadSafeMap* createMap() {
    ThreadSafeMap* map = (ThreadSafeMap*)malloc(sizeof(ThreadSafeMap));
    map->capacity = CAPACITY;
    map->table = (HashNode**)malloc(map->capacity * sizeof(HashNode*));
    map->locks = (pthread_mutex_t*)malloc(map->capacity * sizeof(pthread_mutex_t));

    for (int i = 0; i < map->capacity; i++) {
        map->table[i] = NULL;
        pthread_mutex_init(&map->locks[i], NULL);
    }
    return map;
}

void put(ThreadSafeMap* map, const char* key, int value) {
    unsigned long hash = hashFunction(key);
    pthread_mutex_lock(&map->locks[hash]);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    map->table[hash] = node;
    pthread_mutex_unlock(&map->locks[hash]);
}

int get(ThreadSafeMap* map, const char* key) {
    unsigned long hash = hashFunction(key);
    pthread_mutex_lock(&map->locks[hash]);
    if (map->table[hash] != NULL && strcmp(map->table[hash]->key, key) == 0) {
        int value = map->table[hash]->value;
        pthread_mutex_unlock(&map->locks[hash]);
        return value;
    }
    pthread_mutex_unlock(&map->locks[hash]);
    return -1; // Value not found
}

void freeMap(ThreadSafeMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        if (map->table[i]) {
            free(map->table[i]->key);
            free(map->table[i]);
        }
        pthread_mutex_destroy(&map->locks[i]);
    }
    free(map->table);
    free(map->locks);
    free(map);
}

int main() {
    ThreadSafeMap* map = createMap();
   
