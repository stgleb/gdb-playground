#include<stdio.h>
#include<stdlib.h>

struct node{
    int val;
    struct node *left;
    struct node *right;
};

typedef struct node* nsp;
nsp root;

nsp make_node(int x) {
    nsp tmp;
    tmp = (nsp)malloc(sizeof(struct node));
    tmp->val = x;
    tmp->left = tmp->right = 0;
    return tmp;
}

void insert(nsp* btp, int x) {
    nsp tmp = *btp;

    if(*btp == 0) {
        *btp = make_node(x);
        return;
    }

    while(1) {
        if(x < tmp->val) {
            if(tmp->left != 0) {
                tmp = tmp->left;
            } else {
                tmp->left = make_node(x);
                break;
            }
        } else {
            if(tmp->right != 0) {
                tmp = tmp->right;
            } else {
                tmp->right = make_node(x);
                break;
            }
        }
    }
}

void print_tree(const nsp bt) {
    if(bt == 0)return;
    print_tree(bt->left);
    printf("%d\n", bt->val);
    print_tree(bt->right);
}

int main(int argc, char *argv[]){
    int i;
    root = 0;

    for(i = 1;i < argc; i++){
        insert(&root, atoi(argv[i]));
    }
    print_tree(root);
}