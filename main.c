#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct avl_node {
    int data;
    int height;
    struct avl_node *left;
    struct avl_node *right;
} avl_node;

int max(int a, int b) {
    return a > b ? a : b;
}

int height(avl_node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

avl_node *new_node(int data) {
    avl_node *node = (avl_node *) malloc(sizeof(avl_node));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

avl_node *right_rotate(avl_node *y) {
    avl_node *x = y->left;
    avl_node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

avl_node *left_rotate(avl_node *x) {
    avl_node *y = x->right;
    avl_node *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


void write_file(char *file_name, char *text) {
    FILE *file = fopen(file_name, "a");
    fprintf(file, "%s", text);
    fclose(file);
}


int get_balance(avl_node *node, int *comparations) {
    if (node == NULL) {
        *comparations += 1;
        return 0;
    }
    *comparations += 1;
    return height(node->left) - height(node->right);
}

avl_node *insert(avl_node *node, int data, int *comparations) {
    if (node == NULL) {
        *comparations += 1;
        return new_node(data);
    }

    if (data < node->data) {
        *comparations += 2;
        node->left = insert(node->left, data, comparations);
    } else if (data > node->data) {
        *comparations += 3;
        node->right = insert(node->right, data, comparations);
    } else {
        *comparations += 3;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node, comparations);

    if (balance > 1 && data < node->left->data) {
        *comparations += 1;
        return right_rotate(node);
    }

    if (balance < -1 && data > node->right->data) {
        *comparations += 2;
        return left_rotate(node);
    }

    if (balance > 1 && data > node->left->data) {
        *comparations += 3;
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        *comparations += 4;
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

avl_node *min_value_node(avl_node *node, int *comparations) {
    avl_node *current = node;
    while (current->left != NULL) {
        *comparations += 1;
        current = current->left;
    }
    return current;
}

avl_node *delete_node(avl_node *root, int data, int *comparations) {
    if (root == NULL) {
        *comparations += 1;
        return root;
    }

    if (data < root->data) {
        *comparations += 2;
        root->left = delete_node(root->left, data, comparations);
    } else if (data > root->data) {
        *comparations += 3;
        root->right = delete_node(root->right, data, comparations);
    } else {
        if (root->left == NULL || root->right == NULL) {
            *comparations += 4;
            avl_node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                *comparations += 1;
                temp = root;
                root = NULL;
            } else {
                *comparations += 1;
                *root = *temp;
            }
            free(temp);
        } else {
            *comparations += 4;
            avl_node *temp = min_value_node(root->right, comparations);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data, comparations);
        }
    }

    if (root == NULL) {
        *comparations += 1;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = get_balance(root, comparations);

    if (balance > 1 && get_balance(root->left, comparations) >= 0) {
        *comparations += 1;
        return right_rotate(root);
    }

    if (balance > 1 && get_balance(root->left, comparations) < 0) {
        *comparations += 2;
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && get_balance(root->right, comparations) <= 0) {
        *comparations += 3;
        return left_rotate(root);
    }

    if (balance < -1 && get_balance(root->right, comparations) > 0) {
        *comparations += 4;
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void pre_order(avl_node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        pre_order(root->left);
        pre_order(root->right);
    }
}

void in_order(avl_node *root) {
    if (root != NULL) {
        in_order(root->left);
        printf("%d ", root->data);
        in_order(root->right);
    }
}

void post_order(avl_node *root) {
    if (root != NULL) {
        post_order(root->left);
        post_order(root->right);
        printf("%d ", root->data);
    }
}

typedef struct binary_tree {
    int data;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;


binary_tree *new_binary_tree_node(int data) {
    binary_tree *node = (binary_tree *) malloc(sizeof(binary_tree));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

binary_tree *insert_binary_tree(binary_tree *node, int data, int *comparations) {
    if (node == NULL) {
        *comparations += 1;
        return new_binary_tree_node(data);
    }

    if (data < node->data) {
        *comparations += 2;
        node->left = insert_binary_tree(node->left, data, comparations);
    } else if (data > node->data) {
        *comparations += 3;
        node->right = insert_binary_tree(node->right, data, comparations);
    } else {
        *comparations += 3;
        return node;
    }

    return node;
}

binary_tree *delete_binary_tree_node(binary_tree *root, int data, int *comparations) {
    if (root == NULL) {
        *comparations += 1;
        return root;
    }

    if (data < root->data) {
        *comparations += 2;
        root->left = delete_binary_tree_node(root->left, data, comparations);
    } else if (data > root->data) {
        *comparations += 3;
        root->right = delete_binary_tree_node(root->right, data, comparations);
    } else {
        if (root->left == NULL || root->right == NULL) {
            *comparations += 4;
            binary_tree *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                *comparations += 1;
                temp = root;
                root = NULL;
            } else {
                *comparations += 1;
                *root = *temp;
            }
            free(temp);
        } else {
            *comparations += 4;
            binary_tree *temp = root->right;
            while (temp->left != NULL) {
                *comparations += 1;
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = delete_binary_tree_node(root->right, temp->data, comparations);
        }
    }

    return root;
}

void pre_order_binary_tree(binary_tree *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        pre_order_binary_tree(root->left);
        pre_order_binary_tree(root->right);
    }
}

void in_order_binary_tree(binary_tree *root) {
    if (root != NULL) {
        in_order_binary_tree(root->left);
        printf("%d ", root->data);
        in_order_binary_tree(root->right);
    }
}

void post_order_binary_tree(binary_tree *root) {
    if (root != NULL) {
        post_order_binary_tree(root->left);
        post_order_binary_tree(root->right);
        printf("%d ", root->data);
    }
}


avl_node *search_avl_tree(avl_node *root, int data, int *comparations) {
    if (root == NULL || root->data == data) {
        *comparations += 1;
        return root;
    }

    if (root->data < data) {
        *comparations += 2;
        return search_avl_tree(root->right, data, comparations);
    }

    *comparations += 2;
    return search_avl_tree(root->left, data, comparations);
}

binary_tree *search_binary_tree(binary_tree *root, int data, int *comparations) {
    if (root == NULL || root->data == data) {
        *comparations += 1;
        return root;
    }

    if (root->data < data) {
        *comparations += 2;
        return search_binary_tree(root->right, data, comparations);
    }

    *comparations += 2;
    return search_binary_tree(root->left, data, comparations);
}


avl_node *insert_random_avl_tree(int n, avl_node *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        int data = rand() % 100000;
        root = insert(root, data, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("avl_insert.csv", text_comparations);
        sprintf(text_data, "%d,\n", data);
        write_file("avl_insert.csv", text_data);

    }
    
    return root;
}

binary_tree *insert_random_binary_tree(int n, binary_tree *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        int data = rand() % 100000;
        root = insert_binary_tree(root, data, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("binary_tree_insert.csv", text_comparations);
        sprintf(text_data, "%d,\n", data);
        write_file("binary_tree_insert.csv", text_data);
    }

    return root;
}

avl_node *delete_random_avl_tree(int n, avl_node *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        int data = rand() % 100000;
        root = delete_node(root, data, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("avl_delete.csv", text_comparations);
        sprintf(text_data, "%d,\n", data);
        write_file("avl_delete.csv", text_data);
    }

    return root;
}

binary_tree *delete_random_binary_tree(int n, binary_tree *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        int data = rand() % 100000;
        root = delete_binary_tree_node(root, data, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("binary_tree_delete.csv", text_comparations);
        sprintf(text_data, "%d,\n", data);
        write_file("binary_tree_delete.csv", text_data);
    }
}

void free_avl_tree(avl_node *root) {
    if (root != NULL) {
        free_avl_tree(root->left);
        free_avl_tree(root->right);
        free(root);
    }
}

void free_binary_tree(binary_tree *root) {
    if (root != NULL) {
        free_binary_tree(root->left);
        free_binary_tree(root->right);
        free(root);
    }
}

avl_node *insert_ordered_avl_tree(int n, avl_node *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        root = insert(root, i, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("avl_insert_ordered.csv", text_comparations);
        sprintf(text_data, "%d,\n", i);
        write_file("avl_insert_ordered.csv", text_data);

    }
    
    return root;
}

binary_tree *insert_ordered_binary_tree(int n, binary_tree *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        root = insert_binary_tree(root, i, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("binary_tree_insert_ordered.csv", text_comparations);
        sprintf(text_data, "%d,\n", i);
        write_file("binary_tree_insert_ordered.csv", text_data);
    }

    return root;
}

avl_node *delete_ordered_avl_tree(int n, avl_node *root) {
    int i;
    for (i = n; i > 0; i--) {
        int comparations = 0;
        root = delete_node(root, i, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("avl_delete_ordered.csv", text_comparations);
        sprintf(text_data, "%d,\n", i);
        write_file("avl_delete_ordered.csv", text_data);
    }

    return root;
}

binary_tree *delete_ordered_binary_tree(int n, binary_tree *root) {
    int i;
    for (i = n; i > 0; i--) {
        int comparations = 0;
        root = delete_binary_tree_node(root, i, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("binary_tree_delete_ordered.csv", text_comparations);
        sprintf(text_data, "%d,\n", i);
        write_file("binary_tree_delete_ordered.csv", text_data);
    }

    return root;
}

void search_random_avl_tree(int n, avl_node *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        int data = rand() % 100000;
        search_avl_tree(root, data, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("avl_search.csv", text_comparations);
        sprintf(text_data, "%d,\n", data);
        write_file("avl_search.csv", text_data);
    }
}

void search_random_binary_tree(int n, binary_tree *root) {
    int i;
    for (i = 0; i < n; i++) {
        int comparations = 0;
        int data = rand() % 100000;
        search_binary_tree(root, data, &comparations);
        char text_comparations[20] = "";
        char text_data[10] = "";
        sprintf(text_comparations, "%d,", comparations); 
        write_file("binary_tree_search.csv", text_comparations);
        sprintf(text_data, "%d,\n", data);
        write_file("binary_tree_search.csv", text_data);
    }
}


int main(){
    binary_tree *root = NULL;
    avl_node *avl_root = NULL;

    // binary_tree *root_ordered = NULL;
    // avl_node *avl_root_ordered = NULL;

    int i = 100000;

    write_file("avl_insert.csv", "comparations,data,\n");
    write_file("binary_tree_insert.csv", "comparations,data,\n");
    write_file("avl_delete.csv", "comparations,data,\n");
    write_file("binary_tree_delete.csv", "comparations,data,\n");
    write_file("avl_search.csv", "comparations,data,\n");
    write_file("binary_tree_search.csv", "comparations,data,\n");

    // write_file("avl_insert_ordered.csv", "comparations,data,\n");
    // write_file("binary_tree_insert_ordered.csv", "comparations,data,\n");
    // write_file("avl_delete_ordered.csv", "comparations,data,\n");
    // write_file("binary_tree_delete_ordered.csv", "comparations,data,\n");

    avl_root = insert_random_avl_tree(i, avl_root);
    root = insert_random_binary_tree(i, root);

    search_random_avl_tree(i, avl_root);
    search_random_binary_tree(i, root);

    avl_root = delete_random_avl_tree(i, avl_root);
    root = delete_random_binary_tree(i, root);

    // avl_root_ordered = insert_ordered_avl_tree(i, avl_root_ordered);
    // root_ordered = insert_ordered_binary_tree(i, root_ordered);

    // avl_root_ordered = delete_ordered_avl_tree(i, avl_root_ordered);
    // root_ordered = delete_ordered_binary_tree(i, root_ordered);

    return 0;
}