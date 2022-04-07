#include <stdio.h>
#include <stdlib.h>
#include "src/linked_list.c"

#define MAX_STRING_SIZE 255

void remove_trailing_newline(char string[]);

int main (int argc, char *argv[]) {
    int option;
    Node *list = NULL;

    do {
        int id, age;
        char name[MAX_STRING_SIZE], confirmation;
        IndexedNode *indexed_node;

        printf("[PERSON REGISTRY]\nWhat operation do you want to perform?\n  [1] - Insert\n  [2] - Delete\n  [3] - Search\n  [4] - Edit\n  [5] - Empty Registry\n  [6] - List\n  [0] - Exit\n\nOption: ");
        scanf("%d", &option);

        printf("\n");

        switch (option) {
            case 1: // Insert
                printf("Insert a new person:\n  ID: ");
                scanf("%d", &id);
                fflush(stdin);
                printf("  Name: ");
                fgets(name, MAX_STRING_SIZE, stdin);
                remove_trailing_newline(name);
                fflush(stdin);
                printf("  Age: ");
                scanf("%d", &age);

                Node *person = create_node(id, name, age);

                if (list == NULL) {
                    list = person;
                } else {
                    insert_on_tail(list, person);
                }
                break;
            case 2: // Delete
                printf("Delete a person:\n  ID: ");
                scanf("%d", &id);

                indexed_node = find_node_and_index(list, id);

                if (indexed_node == NULL) {
                    printf("Person not found\n");
                } else {
                    printf("Person to be deleted:\n  ID: %d\n  Name: %s\n  Age: %d\n", indexed_node->node->id, indexed_node->node->name, indexed_node->node->age);
                    printf("Are you sure you want to delete this person? (y/n): ");
                    fflush(stdin);
                    scanf("%c", &confirmation);
                    if (confirmation == 'y') {
                        list = delete_node(list, indexed_node->index);
                        printf("Person deleted\n");
                    } else {
                        printf("Aborting...\n");
                    }
                }
                break;
            case 3: // Search
                printf("Search a person:\n  ID: ");
                scanf("%d", &id);

                Node *found = find_node(list, id);

                if (found != NULL) {
                    printf("Person found:\n  ID: %d\n  Name: %s\n  Age: %d\n", found->id, found->name, found->age);
                } else {
                    printf("Person not found\n");
                }
                break;
            case 4: // Edit
                printf("Edit a person:\n  ID: ");
                scanf("%d", &id);

                indexed_node = find_node_and_index(list, id);

                if (indexed_node == NULL) {
                    printf("Person not found\n");
                } else {
                    printf("Person to be edited:\n  ID: %d\n  Name: %s\n  Age: %d\n\n", indexed_node->node->id, indexed_node->node->name, indexed_node->node->age);
                    printf("Updated data:\n  ID: ");
                    scanf("%d", &id);
                    fflush(stdin);
                    printf("  Name: ");
                    fgets(name, MAX_STRING_SIZE, stdin);
                    remove_trailing_newline(name);
                    fflush(stdin);
                    printf("  Age: ");
                    scanf("%d", &age);

                    edit_node(list, indexed_node->index, id, name, age);
                }
                break;
            case 5: // Empty Registry
                printf("Emptying registry...\n");
                free_list(list);
                list = NULL;
                printf("Registry empty\n");
                break;
            case 6: // List
                print_list(list);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option\n");
        }
        
        printf("\n");
    } while (option != 0);

    return 0;
}

void remove_trailing_newline(char string[]) {
     int i;
     for (i = 0; i < MAX_STRING_SIZE - 1; i++) {
        if (string[i] == '\n' && string[i + 1] == '\0') {
           string[i] = '\0';
        }
    }
}