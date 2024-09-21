#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the initial capacity of the vector
#define VECTOR_INIT_CAPACITY 4

typedef struct {
    int *data;       // Pointer to the array of elements
    int size;        // Number of elements in the vector
    int capacity;    // Total capacity of the vector
} Vector;

// Function to initialize the vector
void vector_init(Vector *vector) {
    vector->size = 0;
    vector->capacity = VECTOR_INIT_CAPACITY;
    vector->data = (int *)malloc(sizeof(int) * vector->capacity);
}

// Function to resize the vector when it exceeds its capacity
void vector_resize(Vector *vector, int capacity) {
    vector->capacity = capacity;
    vector->data = (int *)realloc(vector->data, sizeof(int) * vector->capacity);
}

// Function to add an element to the end of the vector
void vector_push(Vector *vector, int value) {
    if (vector->size >= vector->capacity) {
        vector_resize(vector, vector->capacity * 2);  // Double the capacity
    }
    vector->data[vector->size] = value;
    vector->size++;
}

// Function to get an element at a given index
int vector_get(Vector *vector, int index) {
    if (index >= 0 && index < vector->size) {
        return vector->data[index];
    }
    printf("Index out of bounds!\n");
    exit(EXIT_FAILURE);
}

// Function to remove and return the last element in the vector
int vector_pop(Vector *vector) {
    if (vector->size == 0) {
        printf("Vector is empty!\n");
        exit(EXIT_FAILURE);
    }
    vector->size--;
    int value = vector->data[vector->size];
    
    // Resize the vector if it's less than a quarter full
    if (vector->size > 0 && vector->size <= vector->capacity / 4) {
        vector_resize(vector, vector->capacity / 2);
    }
    return value;
}

// Function to free the memory used by the vector
void vector_free(Vector *vector) {
    free(vector->data);
    vector->data = NULL;
}

int main() {
    Vector vector;
    vector_init(&vector);

    // Add some elements
    vector_push(&vector, 10);
    vector_push(&vector, 20);
    vector_push(&vector, 30);
    vector_push(&vector, 40);

    // Get and print an element
    printf("Element at index 2: %d\n", vector_get(&vector, 2));

    // Pop and print the last element
    printf("Popped element: %d\n", vector_pop(&vector));

    // Free the vector memory
    vector_free(&vector);

    return 0;
}
