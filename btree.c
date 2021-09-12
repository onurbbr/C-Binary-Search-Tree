#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node BTREE;

BTREE *new_node(int data) {
    BTREE *p = (BTREE *) malloc(sizeof(BTREE));
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

BTREE *insert(BTREE *root, int data) {
    if (root != NULL) {
        if (data < root->data)
            root->left = insert(root->left, data);
        else
            root->right = insert(root->right, data);
    } else
        root = new_node(data);
    return root;
}

void preorder(BTREE *root) {
    if (root != NULL) {
        printf("%4d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(BTREE *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%4d ", root->data);
        inorder(root->right);
    }
}

void postorder(BTREE *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%4d ", root->data);
    }
}

int minValue(BTREE *root) {
    if (root == NULL)
        return 0;
    while (root->left != NULL)
        root = root->left;
    printf("%d", root->data);
    return (root->data);
}

int maxValue(BTREE *root) {
    if (root == NULL)
        return 0;
    while (root->right != NULL)
        root = root->right;
    printf("%d", root->data);
    return (root->data);
}

int size (BTREE *root) {
    if (root == NULL)
        return 0;
    else
        return 1+size(root->left)+size(root->right);
}

int leaves (BTREE *root) {
    if (root == NULL)
        return 0;
    if (root->left == root->right)
        return 1;
    else
        return leaves(root->left)+leaves(root->right);
}

BTREE *delete_node(BTREE *root, int value) {
    BTREE *p, *q;
    if (root == NULL)
        return NULL;
    if (root->data == value) {
        if (root->left == root->right) {
            free(root);
            return NULL;
        } else {
            if (root->left == NULL) {
                p = root->right;
                free(root);
                return p;
            } else if (root->right == NULL) {
                p = root->left;
                free(root);
                return p;
            } else {
                p = q = root->right;
                while (p->left != NULL)
                    p = p->left;
                p->left = root->left;
                free(root);
                return q;
            }
        }
    } else if (root->data < value)
        root->right = delete_node(root->right, value);
    else
        root->left = delete_node(root->left, value);
    return root;
}

int height(BTREE *root)
{
    if (root == NULL)
        return -1;
    else
    {
        int lheight, rheight;
        rheight = (height(root->right));
        lheight = (height(root->left));
        if (rheight > lheight)
            return rheight + 1;
        else
            return lheight + 1;
    }
}

int main() {
    BTREE *customroot = NULL;
    int i = 0;
    printf("\nPlease enter numbers to add data to the tree.\n");
    do {
        printf("Enter the Number: ");
        scanf("%d", &i);
        if (i != -1)
            customroot = insert(customroot, i);
    } while (i != -1);
    if (customroot != NULL) {
        printf("Inorder value: ");
        inorder(customroot);
        printf("\n");
        printf("Preorder value: ");
        preorder(customroot);
        printf("\n");
        printf("Postorder value: ");
        postorder(customroot);
        printf("\n");
        printf("Min value: ");
        minValue(customroot);
        printf("\n");
        printf("Max value: ");
        maxValue(customroot);
        printf("\n");
        printf("Tree size: ");
        printf("%d", size(customroot));
        printf("\n");
        printf("Number of leaves: ");
        printf("%d", leaves(customroot));
        printf("\n");
        printf("Height = %d", height(customroot));
        printf("\n");
    }
    getchar();
    return 0;
}