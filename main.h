//
// Created by Andrew on 1/26/2017.
//

#ifndef WORDTREE_MAIN_H
#define WORDTREE_MAIN_H
/*
 * A struct definition for a single node in our binary tree.
 */
struct node {
    char* word;
    int count;
    struct node* left_child;
    struct node* right_child;
};
int searchForWord(char*, struct node*);
void in_order_traverse(struct node*,FILE*);
void delete_tree(struct node*);
#endif //WORDTREE_MAIN_H
