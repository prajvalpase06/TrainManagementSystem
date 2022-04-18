#ifndef TRAIN_H
#define TRAIN_H

typedef struct train_tag
{
    char name_of_train[30];
    int train_id;
    int date_of_travel;
    int num_of_passengers;
    struct train_tag *left;
    struct train_tag *right;
    int train_node_height;
} train;

int max(int, int);
char* getid(char*, char*);
int train_node_height(train*);
train *leftRotate_train(train *n);
train *rightRotate_train(train *n);
int get_balance(train*);
void display_train(train*);
train* min_node_train(train*);                                    // GET THE NODE WITH LEAST NUMBER OF PASSENGERS
train* add_train(train* t, char* bt, int, int, int);              // ADD A NEW TRAIN TO THE DATABASE
train* check_train_exists(train* t, int);                       // CHECK IF TRAIN EXISTS IN DATABASE
train* update_passengers(train* t, int id);                    // IF TRAIN EXISTS IN DATABASE, UPDATE THE PASSENGER COUNT
void SortTrains(train* t);
void rangeSearch(train* t, int h, int l);
void inorder_train(train*);

#endif