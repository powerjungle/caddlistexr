#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROPER_FORMAT "Example: ./caddlistexr 2 + 2\n"
 
// Used for getting the numbers from the characters
// and the other way around, using the ASCII table.
const char ascii_offset = 48;

void print_arguments_error(int got) {
        printf("Got arguments amount: %d\n", got);
        printf("Required 3!\n");
        printf(PROPER_FORMAT);
}

void print_invalid_format() {
        printf("The format of your command is invalid.\n");
        printf(PROPER_FORMAT);
}

// The doubly linked list node data structure.
typedef struct node {
        char digit;
        struct node* next;
        struct node* prev;
} node_t;

// Set the first node of the doubly linked list.
node_t* init_linked_list(char init_char) {
        node_t* new_node = (node_t*)malloc(sizeof(node_t));
        if (new_node == NULL) {
                printf("Initialization of linked list returned NULL, exiting.\n");
                exit(0);
        }
        new_node->digit = init_char;
        new_node->next = NULL;
        new_node->prev = NULL;
        return new_node;
}

// Make a new "tail" for the doubly linked list.
// a.k.a. add a new last node.
node_t* add_new_element_end(node_t* tail, char new_char) {
        tail->next = (node_t*)malloc(sizeof(node_t));
        if (tail->next == NULL) {
                printf("Filling of linked list returned NULL, at char:%c exiting.\n", new_char);
                exit(0);
        }
        tail->next->prev = tail;
        tail = tail->next;
        tail->digit = new_char;
        tail->next = NULL;
        return tail;
}

// Setup the whole linked list from a string.
// ref_head and ref_tail must already be declared with
// the node_t* pointer type in another function and their
// addresses need to be set as arguments to this function,
// so that the new proper addresses can be set to them.
void init_and_fill_linked_list(char* arr, node_t** ref_head, node_t** ref_tail) {
        char first_char = *arr;
        node_t* head = init_linked_list(first_char);
        node_t* new_tail = head;
        arr++; 
        while (*arr != '\0') {
                new_tail = add_new_element_end(new_tail, *arr);
                arr++;
        }
        *ref_head = head;
        *ref_tail = new_tail;
}

// Prints the whole linked list in one line.
// direction = 'f', reads forwards
// direction = 'b', reads backwards
void print_linked_list(node_t* ptr, char* format, char direction) {
        while (ptr != NULL) {
                printf(format, ptr->digit);
                if (direction == 'f') {
                        ptr = ptr->next;
                } else if (direction == 'b') {
                        ptr = ptr->prev;
                } else {
                        printf("No proper direction chosen for print_linked_list()");
                        break;
                }
        }
        printf("\n");
}

// Free up the whole linked list's allocated memory.
// This needs to be done on every list creation,
// otherwise memory will be leaked.
// direction = 'f', reads forwards
// direction = 'b', reads backwards
void free_list(node_t* ptr, char direction) {
        node_t* tmp;
        while (ptr != NULL) {
                tmp = ptr;
                if (direction == 'f') {
                        ptr = ptr->next;
                } else if (direction == 'b') {
                        ptr = ptr->prev;
                } else {
                        printf("No proper direction chosen for free_list()");
                        break;
                }
                free(tmp);
        }
}

// Remove the last "character" from the list
// and return the new address of the new last node.
node_t* remove_last_node(node_t* tail) {
        node_t* ret = tail->prev;
        ret->next = NULL;
        free(tail);
        return ret;
}

// n1ptr and n2ptr must be two already created lists,
// preferably using init_and_fill_linked_list().
// reverse = 0, means read both lists from their "tails" or last nodes
// to their beginnings or "head" nodes.
// reverse = 1, means read the first list only from head to tail
// reverse = 2, means the same as 1 for the second list only
// reverse = 3, means the same for both,
// the reason for this argument is when the result is used again
// as an argument, it can be read in reverse, because the function itself
// returns the last element, and instead of reversing a huge list which is expensive,
// we just read it in reverse.
node_t* add_two_lists(node_t* n1ptr, node_t* n2ptr, char reverse) {  
        node_t* result = init_linked_list('0');
        char digit_result, buffer;
        while (n1ptr != NULL || n2ptr != NULL) {
                if (n2ptr != NULL && n1ptr != NULL) {
                        buffer = (n1ptr->digit - ascii_offset) +
                                (n2ptr->digit - ascii_offset) +
                                (result->digit - ascii_offset);
                } else if (n1ptr != NULL) {
                        buffer = (n1ptr->digit-ascii_offset) + (result->digit-ascii_offset);
                } else if (n2ptr != NULL) {
                        buffer = (n2ptr->digit-ascii_offset) + (result->digit-ascii_offset);
                }

                if (buffer > 9) {
                        digit_result = (buffer-9)-1;
                } else {
                        digit_result = buffer;
                }

                result->digit = digit_result+ascii_offset;

                if (n1ptr != NULL) {
                        if (reverse == '0' || reverse == '2') {
                                n1ptr = n1ptr->prev;
                        } else if (reverse == '1' || reverse == '3') {
                                n1ptr = n1ptr->next;
                        }
                }

                if (n2ptr != NULL) {
                        if (reverse == '0' || reverse == '1') {
                                n2ptr = n2ptr->prev;
                        } else if (reverse == '2' || reverse == '3') {
                                n2ptr = n2ptr->next;
                        }
                }
 
                //printf("result-pre: %c\n", result->digit);
                
                if (buffer > 9) {
                        result = add_new_element_end(result, '1');
                } else {
                        result = add_new_element_end(result, '0');
                }

                //printf("digit_result: %d\n", digit_result);
                //printf("buffer: %d\n", buffer);
                //printf("result-post: %c\n", result->digit);
        }

        if (result->digit == '0')
                result = remove_last_node(result);

        return result;
}

int main(int argc, char *argv[]) {
        // Make sure that the input from the user has exactly 3 strings.
        // firstNumber commandCharacter secondNumber
        if (argc-1 != 3) {
                print_arguments_error(argc-1);
                return 1;
        }

        // Make sure that the commandCharacter is exactly 1 character
        // long, because it can be interpreted easier this way.
        if (strlen(argv[2]) > 1) {
                print_invalid_format();
                return 1;
        }

        // Directly address the first character in the string.
        // No need to iterate through the string, because this
        // is the command character.
        char command_char = *argv[2];

        // Initialise the needed pointers, because the functions
        // will not be able to return both addresses another way.
        node_t* list_head_num1;
        node_t* list_tail_num1;
        node_t* list_head_num2;
        node_t* list_tail_num2;

        // "Convert" the firstNumber and secondNumber strings to doubly linked lists.
        // We could just iterate through the strings as normal arrays, but
        // I wanted to have an universal function which accepts only
        // linked lists for processing.
        init_and_fill_linked_list(argv[1], &list_head_num1, &list_tail_num1);
        init_and_fill_linked_list(argv[3], &list_head_num2, &list_tail_num2);

        /*
        print_linked_list(list_head_num1, "%c", 'f');
        print_linked_list(list_head_num2, "%c", 'f');
        print_linked_list(list_tail_num1, "%c", 'b');
        print_linked_list(list_tail_num2, "%c", 'b');
        */

        switch(command_char) {
                case '+':
                        // Add the two inputs of the user together, the length doesn't matter.
                        node_t* result = add_two_lists(list_tail_num1, list_tail_num2, '0');
                        // The result is printed in reverse, because when adding the lists,
                        // a new node gets added to the end of the list "result", so we
                        // have only the last node, but in this case it's not a problem.
                        print_linked_list(result, "%c", 'b');
                        // Never forget to free up your memory, to avoid leaks!
                        // All memory leaks checked with the tool "valgrind".
                        free_list(result, 'b');
                        break;
                default:
                        // Tell the user, that the wrong character has been used.
                        print_invalid_format();
        }

        free_list(list_head_num1, 'f');
        free_list(list_head_num2, 'f');
}

