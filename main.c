#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


int main(int argc, char** argv) {
    // Buffer for input.
    char input_buffer[512];
    // Pointer to the input file.
    FILE *input;
    // Pointer to the output file.
    FILE *output;
    char output_name[64] = "myoutput";
    char txt[] = ".txt";
    // Check for correct number of arguments.
    if (argc == 1 || argc > 2){
        printf("Incorrect number of arguments. Please supply a single filename argument.\n");
        exit(0);
    }else {
        printf("Attempting to open %s\n",argv[1]);
        // Open the file in read mode.
        input = fopen(argv[1],"r");
        // Check if file open was successful
        if (input == NULL){
            printf("Failed to open file \'%s\', please check that the file exists.\n",argv[1]);
            exit(0);
        }else{
            printf("Successfully opened file \'%s\'.\n",argv[1]);
            char num[32];
            char* current = argv[1];
            // Skip the non-numeric characters of the filename
            while(*current < 48 || *current > 57) {
                ++current;
            }
            // Add each number character onto the end of the number string.
            while(*current > 47 && *current < 58){
                if(strlen(num) < 32-1){
                    num[strlen(num)] = *current;
                    num[strlen(num)+1] = '\0';
                    ++current;
                }else{
                    printf("Input file number exceeds 32 digit limit.\n Why would you use an input file with a number this long?\n");
                    break;
                }
            }
            // Construct the output filename.
            strcat(output_name,num);
            strcat(output_name,txt);

            printf("Attempting to open \'%s\' for writing.\n",output_name);
            output = fopen(output_name,"w");
            if(output == NULL){
                printf("Failed to open \'%s\' for writing.\n",output_name);
                exit(0);
            }else{
                printf("Successfully opened \'%s\' for writing.\n",output_name);
            }
        }
    }

    // Create Head node for binary tree.
    struct node* head = (struct node*) malloc(sizeof(struct node));
    // We read the first line and use this information to create the head node.
    if(fscanf(input,"%s",input_buffer) != EOF){
        head->word = malloc(sizeof(input_buffer));
        strcpy(head->word,input_buffer);
        head->count = 1;
        head->left_child = NULL;
        head->right_child = NULL;
    }
    // Loop through the rest of the file.
    while(fscanf(input,"%s",input_buffer) != EOF){
        printf("%s\n",input_buffer);
        searchForWord(input_buffer,head);
    }

    printf("Starting In-Order Traversal.\n");
    in_order_traverse(head,output);

    // Memory cleanup.
    delete_tree(head);

    // Close files.
    fclose(input);
    fclose(output);
}
int searchForWord(char* word, struct node* search_node){
    // This is the word we want.
    if(strcmp(word,search_node->word) == 0){
        search_node->count = search_node->count+1;
        printf("Word \'%s\' already exists",word);
        printf(", the count is now %d\n",search_node->count);
    }
    // Word is less, so go left.
    else if(strcmp(word,search_node->word) < 0){
        if (search_node->left_child == NULL){
            // Allocate space for the node structure.
            search_node->left_child = (struct node*)malloc(sizeof(struct node));
            // Allocate space for the char*
            search_node->left_child->word = (char*)malloc(sizeof(word));
            // Copy the word into the char*
            strcpy(search_node->left_child->word,word);
            // Set count to 1.
            search_node->left_child->count = 1;

            // Set both children to NULL
            search_node->left_child->left_child = NULL;
            search_node->left_child->right_child = NULL;
            printf("Added new word \'%s\'.\n",word);
        }else {
            searchForWord(word, search_node->left_child);
        }
    }
    // Word is greater, so go right.
    else {
        if(search_node->right_child == NULL){
            // Allocate space for node structure
            search_node->right_child = (struct node*)malloc(sizeof(struct node));
            // Allocate space for char*
            search_node->right_child->word = (char*)malloc(sizeof(word));
            // Copy word into the char*
            strcpy(search_node->right_child->word,word);
            // Set count to 1.
            search_node->right_child->count = 1;

            // Set both children to NULL
            search_node->right_child->left_child = NULL;
            search_node->right_child->right_child = NULL;
            printf("Added new word \'%s\'.\n",word);
        }else {
            searchForWord(word, search_node->right_child);
        }
    }
    return 0;
}
void in_order_traverse(struct node* start, FILE *output){
    // If node is NULL, we're done in this branch, just return.
    if(start == NULL){
        return;
    }else{
        // Recursive transit of left children.
        in_order_traverse(start->left_child,output);
        // Print each word and its count.
        printf("Word: \'%s\'\n", start->word);
        printf("Count: %d\n",start->count);
        fprintf(output,"Word: \'%s\'\n", start->word);
        fprintf(output,"Count: %d\n",start->count);
        // Recursive transit of right children.
        in_order_traverse(start->right_child,output);
    }
}

void delete_tree(struct node* start){
    if (start != NULL){
        delete_tree(start->left_child);
        delete_tree(start->right_child);
        printf("Deleting \'%s\'.\n",start->word);
        free(start->word);
        free(start);
    }
}