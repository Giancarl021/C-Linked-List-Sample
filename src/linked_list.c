#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    struct _Node *next;
    struct _Node *prev;
    int id;
    char *name;
    int age;
} Node;

typedef struct _IndexedNode {
    Node *node;
    int index;
} IndexedNode;

Node* create_node(int id, char *name, int age) {
    Node *node = (Node*)malloc(sizeof(Node));

    char *copy_name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(copy_name, name);

    node->id = id;
    node->name = copy_name;
    node->age = age;

    node->next = NULL;
    node->prev = NULL;

    return node;
}

Node* get_node(Node *head, int index) {
    int i;
    Node *current = head;

    for (i = 0; i < index; i++) {
        current = current->next;
        if (current == NULL) return NULL;
    }

    return current;
}

void insert_on_tail(Node *head, Node *element) {
    Node *current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = element;
    element->prev = current;
}

Node* find_node(Node *head, int id) {
    Node *current = head;

    while (current != NULL) {
        if (current->id == id) return current;
        current = current->next;
    }

    return NULL;
}

int find_index(Node *head, int id) {
    Node *current = head;
    int i = 0;

    while (current != NULL) {
        if (current->id == id) return i;
        current = current->next;
        i++;
    }

    return -1;
}

IndexedNode* find_node_and_index(Node *head, int id) {
    Node *current = head;
    IndexedNode* indexed_node = (IndexedNode*)malloc(sizeof(IndexedNode));
    int i = 0;

    while (current != NULL) {
        if (current->id == id) {
            indexed_node->node = current;
            indexed_node->index = i;

            return indexed_node;
        }
        current = current->next;
        i++;
    }

    return NULL;
}

Node* delete_node(Node* head, int index) {
    Node *element = get_node(head, index),
        *new_head = head;

    if (element == NULL) return;

    Node *prev = element->prev;
    Node *next = element->next;

    if (prev != NULL) prev->next = next;
    if (next != NULL) next->prev = prev;

    free(element->name);
    free(element);

    if (index == 0) new_head = next;

    return new_head;
}

void edit_node(Node *head, int index, int id, char *name, int age) {
    Node *current = get_node(head, index);

    if (current == NULL) return;

    char *copy_name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(copy_name, name);

    current->id = id;
    current->name = copy_name;
    current->age = age;
}

void free_list(Node* head) {
    Node *current = head,
        *next;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    int i = 0;

    printf("[PERSON LIST]\n");
    while (current != NULL) {
        printf("  Index: %d\n  ID: %d\n  Name: %s\n  Age: %d\n", i++, current->id, current->name, current->age);
        current = current->next;
    }
}