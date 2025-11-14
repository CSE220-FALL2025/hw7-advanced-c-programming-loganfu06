// Name: Logan Fu
// ID: 116099756
// NetID: ltfu
#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    if(root == NULL) {
        bst_sf* m = malloc(sizeof(bst_sf));
        m->left_child = NULL;
        m->right_child = NULL;
        m->mat = mat;
        return m;
    }
    else {
        char name = mat->name;
        char rootName = root->mat->name;
        if(name < rootName) {
            root->left_child = insert_bst_sf(mat, root->left_child);
        }
        else {
            root->right_child = insert_bst_sf(mat, root->right_child);
        }
        return root;
        
    }
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    if(root == NULL) {
        return NULL;
    }
    else if(name == root->mat->name) {
        return root->mat;
    }
    else {
        if(name < root->mat->name) {
            return find_bst_sf(name, root->left_child);
        }
        else {
            return find_bst_sf(name, root->right_child);
        }
    }
}

void free_bst_sf(bst_sf *root) {
    if(root != NULL) {
        free_bst_sf(root->left_child);
        free_bst_sf(root->right_child);
        free(root);
    }
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    int rows = mat1->num_rows;
    int cols = mat1->num_cols;
    matrix_sf *m = malloc(sizeof(matrix_sf) + rows*cols*sizeof(int));
    m->num_rows = rows;
    m->num_cols = cols;
    for(int i = 0; i < rows * cols; i++) {
        m->values[i] = mat1->values[i] + mat2->values[i];
    }

    return m;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    int rows = mat1->num_rows;
    int cols = mat2->num_cols;
    int n = mat1->num_cols;
    matrix_sf *m = malloc(sizeof(matrix_sf) + rows*cols*sizeof(int));
    m->num_rows = rows;
    m->num_cols = cols;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            int sum = 0;
            for(int k = 0; k < n; k++) {
                int mat1Element = mat1->values[i * n + k];
                int mat2Element = mat2->values[k * cols + j];
                sum += mat1Element * mat2Element;
            }
            m->values[i * cols + j] = sum;
        }
    }
    return m;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    int rows = mat->num_cols;
    int cols = mat->num_rows;
    matrix_sf *m = malloc(sizeof(matrix_sf) + rows*cols*sizeof(int));
    m->num_rows = rows;
    m->num_cols = cols;
    for(int i = 0; i < mat->num_rows; i++) {
        for(int j = 0; j < mat->num_cols; j++) {
            m->values[j * cols + i] = mat->values[i*mat->num_cols + j];
        }
    }
    return m;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    char *endPointer;
    int rows = strtol(expr, &endPointer, 10);
    expr = endPointer;
    int cols = strtol(expr, &endPointer, 10);
    expr = endPointer;
    matrix_sf *m = malloc(sizeof(matrix_sf) + rows*cols*sizeof(int));
    while(ispunct(*expr) || isspace(*expr)) {
        expr++;
        if(*expr == '-') {
            break;
        }
    }
    m->name = name;
    m->num_rows = rows;
    m->num_cols = cols;
    int i = 0;
    while(1) {
        int num = strtol(expr, &endPointer, 10);
        if(expr == endPointer) {
            break;
        }
        m->values[i] = num;
        i++;
        expr = endPointer;
        while(ispunct(*expr) || isspace(*expr)) {
            expr++;
            if(*expr == '-') {
                break;
            }
        }
    }
    return m;
}

int getP(char c) {
    switch(c) {
        case '+':
            return 1;
        case '*':
            return 2;
        default:
            return 3;
    }

}
char* infix2postfix_sf(char *infix) {
    struct stack {
        char value;
        struct stack *prev;
    };
    struct stack *top = NULL;
    char *str = malloc(strlen(infix) + 1);
    char *result = str;
    while(*infix != '\0') {
        char c = *infix;
        if(isalpha(c)) {
            *str = c;
            str++;
        }
        else if(c == '(') {
            struct stack *nextValue = malloc(sizeof(struct stack));
            nextValue->value = c;
            nextValue->prev = top;
            top = nextValue;
        }
        else if(c == ')') {
            while(top->value != '(') {
                *str = top->value;
                str++;
                struct stack *pTop = top;
                top = top->prev;
                free(pTop);
            }
            struct stack *pTop = top;
            top = top->prev;
            free(pTop);
        }
        else {
            while(top != NULL && top->value != '(' && getP(c) <= getP(top->value)) {
                *str = top->value;
                str++;
                struct stack *pTop = top;
                top = top->prev;
                free(pTop);
            }
            struct stack *nextValue = malloc(sizeof(struct stack));
            nextValue->value = c;
            nextValue->prev = top;
            top = nextValue;
        }
        infix++;
    }
    while(top != NULL) {
        *str = top->value;
        str++;
        struct stack *pTop = top;
        top = top->prev;
        free(pTop);
    }
    *str = '\0';
    return result;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
