#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

typedef struct {
    char* key;
    int value;
} MapNode;

typedef struct {
    MapNode* table;
    int capacity;
    int size;
} Map;

Map* createMap() {
    Map* map = (Map*)malloc(sizeof(Map));
    map->capacity = CAPACITY;
    map->size = 0;
    map->table = (MapNode*)malloc(map->capacity * sizeof(MapNode));
    return map;
}

void put(Map* map, const char* key, int value) {
    if (map->size >= map->capacity) {
        return;
    }
    map->table[map->size].key = strdup(key);
    map->table[map->size].value = value;
    map->size++;
}

int get(Map* map, const char* key) {
    for (int i = 0; i < map->size; i++) {
        if (strcmp(map->table[i].key, key) == 0) {
            return map->table[i].value;
        }
    }
    return -1; // Value not found
}

void freeMap(Map* map) {
    for (int i = 0; i < map->size; i++) {
        free(map->table[i].key);
    }
    free(map->table);
    free(map);
}

int main() {
    Map* map = createMap();
    put(map, "key1", 10);
    put(map, "key2", 20);

    printf("key1 -> %d\n", get(map, "key1"));
    printf("key2 -> %d\n", get(map, "key2"));

    freeMap(map);
    return 0;
}
