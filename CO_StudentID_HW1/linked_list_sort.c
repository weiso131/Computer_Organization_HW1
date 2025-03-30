#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Split the linked list into two parts
void splitList(Node *head, Node **firstHalf, Node **secondHalf)
{
    //asm
    Node *l = head, *slow = head->next, *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        l = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    *firstHalf = head;
    *secondHalf = slow;
    l->next = NULL;
    //asm
}

// Merge two sorted linked lists
Node *mergeSortedLists(Node *a, Node *b)
{
    
    Node *result = NULL;
    Node *tail = NULL;

    //asm
    Node **indir = &result;
    if (!a)
        return b;
    if (!b)
        return a;
    for (;;) {
        if (a->data < b->data) {
            *indir = a;
            a = a->next;
            indir = &(*indir)->next;
            if (a == NULL) {
                *indir = b;
                break;
            }
        }
        else {
            *indir = b;
            b = b->next;
            indir = &(*indir)->next;
            if (b == NULL) {
                *indir = a;
                break;
            }
        }
    }
    //asm

    return result;
}

// Merge Sort function for linked list
Node *mergeSort(Node *head)
{
    if (!head || !head->next)
        return head; // Return directly if there is only one node

    Node *firstHalf, *secondHalf;
    splitList(head, &firstHalf,
              &secondHalf); // Split the list into two sublists

    firstHalf = mergeSort(firstHalf);   // Recursively sort the left half
    secondHalf = mergeSort(secondHalf); // Recursively sort the right half

    return mergeSortedLists(firstHalf, secondHalf); // Merge the sorted sublists
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    int list_size;
    fscanf(input, "%d", &list_size);
    Node *head = (list_size > 0) ? (Node *)malloc(sizeof(Node)) : NULL;
    Node *cur = head;
    for (int i = 0; i < list_size; i++) {
        fscanf(input, "%d", &(cur->data));
        if (i + 1 < list_size)
            cur->next = (Node *)malloc(sizeof(Node));
        cur = cur->next;
    }
    fclose(input);

    // Linked list sort
    head = mergeSort(head);

    cur = head;
    while (cur) {
        printf("%d ", cur->data);
        //asm
        cur = cur->next;
        //asm
    }
    printf("\n");
    return 0;
}
