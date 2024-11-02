#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Node {
    int key;
    char value[256];
    struct Node* next;
} Node;

typedef struct {
    Node* table[SIZE];
} HashMap;

int hash_function() {}

void insert(HashMap* map, int* key, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
}

int main() {}