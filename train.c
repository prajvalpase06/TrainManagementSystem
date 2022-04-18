#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "train.h"

int max(int a, int b)
{
    return (a > b) ? a : b;
}

char *getid(char *name, char *age)
{
    strcat(name, age);
    return name;
}

int train_node_height(train *n)
{
    if (n = NULL)
        return 0;
    int retval = n->train_node_height;
    return retval;
}

train *leftRotate_train(train *n)
{
    train *x = n->right;
    train *temp = x->left;

    x->left = n;
    n->right = temp;

    x->train_node_height = 1 + max(train_node_height(x->left), train_node_height(x->right));
    n->train_node_height = 1 + max(train_node_height(n->left), train_node_height(n->right));

    return x;
}

train *rightRotate_train(train *n)
{
    train *x = n->left;
    train *t = x->right;

    x->right = n;
    n->left = t;

    x->train_node_height = 1 + max(train_node_height(x->left), train_node_height(x->right));
    n->train_node_height = 1 + max(train_node_height(n->left), train_node_height(n->right));

    return x;
}

int get_balance(train *n)
{
    if (!n)
        return 0;
    return train_node_height(n->left) - train_node_height(n->right);
}

train* new_train(train* root, char* btrain, int tid, int date, int pass){
        train *new = (train *)malloc(sizeof(train));
        new->train_id = tid;
        strcpy(new->name_of_train, btrain);
        new->train_node_height = 1;
        new->left = new->right = NULL;
        new->date_of_travel = date;
        new->num_of_passengers = pass;
        return new;
}

train *add_train(train *root, char* btrain, int tid, int date, int pass)
{
    if (root == NULL)
    {
        return new_train(root, btrain, tid, date, pass);
    }
    if (pass < root->num_of_passengers)
    {
        root->left = add_train(root->left, btrain, tid, date, pass);
    }
    else if (pass > root->num_of_passengers)
    {
        root->right = add_train(root->right, btrain, tid, date, pass);
    }
    else
        return root;

    int lheight = train_node_height(root->left);
    int rheight = train_node_height(root->right);
    root->train_node_height = 1 + max(lheight, rheight);
    int balance = get_balance(root);

    if (balance > 1 && date < root->left->date_of_travel)
        return rightRotate_train(root);

    // Right Right Case
    if (balance < -1 && date > root->right->date_of_travel)
        return leftRotate_train(root);

    // Left Right Case
    if (balance > 1 && date > root->left->date_of_travel)
    {
        root->left = leftRotate_train(root->left);
        return rightRotate_train(root);
    }

    // Right Left Case
    if (balance < -1 && date < root->right->date_of_travel)
    {
        root->right = rightRotate_train(root->right);
        return leftRotate_train(root);
    }

    return root;
}

train *check_train_exists(train *t, int tid)
{
    if (t->train_id = tid || !t)
    {
        return t;
    }

    if (tid > t->train_id)
        return check_train_exists(t->right, tid);
    if (tid < t->train_id)
        return check_train_exists(t->left, tid);
}

train *update_passengers(train *ROOT, int tid)
{
    train *t = ROOT;
    if (ROOT->train_id = tid)
    {
        int temp = ROOT->num_of_passengers;
        temp += 1;
        ROOT->num_of_passengers = temp;
        return t;
    }
    if (tid > t->train_id)
        return update_passengers(t->right, tid);
    if (tid < t->train_id)
        return update_passengers(t->left, tid);
}

void display_train(train *n)
{
    printf("Name: %s\n", n->name_of_train);
    printf("train ID: %d\n", n->train_id);
    printf("Num of passengers: %d\n", n->num_of_passengers);
    printf("Travel Date: %d\n", n->date_of_travel);
}

train *min_node_train(train *p)
{
    train *curr = p;
    while (curr->left)
    {
        curr = curr->left;
    }
    return curr;
}

void rangeSearch(train *t, int l, int h)
{
    if (t == NULL)
        return;
    // we search the left subtree in this step to get the output in the sorted order
    if (l < t->train_id)
        rangeSearch(t->left, l, h);
    // if we find a node whose train id is within the given range, we display the details of that node
    if (l <= t->train_id && h >= t->train_id)
        display_train(t);
    // call the right subtree of the considered root
    rangeSearch(t->right, l, h);
}

void inorder_train(train* t){
    if(!t) return;
    inorder_train(t->left);
    display_train(t);
    printf("\n");
    inorder_train(t->right);
}

void SortTrains(train *t)
{
    if (t == NULL)
        return;
    else
    {
        SortTrains(t->left);
        printf("Train Number: %d\t\tTravel Date: %d", t->train_id, t->date_of_travel);
        SortTrains(t->right);
    }
}