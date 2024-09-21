#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

typedef struct {
    char* key;
} SetNode;

typedef struct {
    SetNode** table;
    int capacity;
} Set;

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % CAPACITY;
}

Set* createSet() {
    Set* set = (Set*)malloc(sizeof(Set));
    set->capacity = CAPACITY;
    set->table = (SetNode**)malloc(set->capacity * sizeof(SetNode*));
    for (int i = 0; i < set->capacity; i++) {
        set->table[i] = NULL;
    }
    return set;
}

void add(Set* set, const char* key) {
    unsigned long hash = hashFunction(key);
    SetNode* node = (SetNode*)malloc(sizeof(SetNode));
    node->key = strdup(key);
    set->table[hash] = node;
}

int contains(Set* set, const char* key) {
    unsigned long hash = hashFunction(key);
    if (set->table[hash] != NULL && strcmp(set->table[hash]->key, key) == 0) {
        return 1; // Found
    }
    return 0; // Not found
}

void freeSet(Set* set) {
    for (int i = 0; i < set->capacity; i++) {
        if (set->table[i]) {
            free(set->table[i]->key);
            free(set->table[i]);
        }
    }
    free(set->table);
    free(set);
}

int main() {
    Set* set = createSet();
    add(set, "key1");
    add(set, "key2");

    printf("Contains key1: %d\n", contains(set, "key1"));
    printf("Contains key3: %d\n", contains(set, "key3"));

    freeSet(set);
    return 0;
}
