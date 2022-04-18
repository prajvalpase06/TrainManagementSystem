#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "train.h"
#include "passenger.h"


#define MAXSEATS 200

int sleeper_seats = 1;  // max is 50
int threeAC_seats = 51; // max is 50
int twoAC_seats = 101;  // max is 50
int oneAC_seats = 151;  // max is 50


int NodeHeight(passenger *n)
{
    if (n == NULL)
        return 0;
    int retval = n->NodeHeight;
    return retval;
}

passenger *leftRotate(passenger *n)
{
    passenger *x = n->right;
    passenger *temp = x->left;

    x->left = n;
    n->right = temp;

    x->NodeHeight = 1 + max(NodeHeight(x->left), NodeHeight(x->right));
    n->NodeHeight = 1 + max(NodeHeight(n->left), NodeHeight(n->right));

    return x;
}

passenger *rightRotate(passenger *n)
{
    passenger *x = n->left;
    passenger *t = x->right;

    x->right = n;
    n->left = t;

    x->NodeHeight = 1 + max(NodeHeight(x->left), NodeHeight(x->right));
    n->NodeHeight = 1 + max(NodeHeight(n->left), NodeHeight(n->right));

    return x;
}

int getBalance(passenger *n)
{
    if (!n)
        return 0;
    return NodeHeight(n->left) - NodeHeight(n->right);
}

passenger *min_id_node(passenger *p)
{
    passenger *curr = p;
    while (curr->left)
    {
        curr = curr->left;
    }
    return curr;
}

passenger *newNode(char name[50], char id[8], char btrain[30], char bstation[40], char Class[10], char dstation[40], int tid, char upgrade, char meal, char age[3], int seat, int date)
{
    passenger *n = (passenger *)malloc(sizeof(passenger));
    train *nw = NULL;
    n->left = NULL;
    n->right = NULL;
    n->NodeHeight = 1;
    strcpy(n->name, name);
    strcpy(n->boardingTrain, btrain);
    strcpy(n->boardingStation, bstation);
    strcpy(n->Class, Class);
    strcpy(n->destinationStation, dstation);
    n->TrainId = tid;
    n->seatNumber = seat;
    n->travel_date = date;
    n->upgrade = upgrade;
    n->MealIncluded = meal;
    n->reservationStatus = 'T';
    char *pass_id = getid(name, age);
    strcpy(n->id, pass_id);

    return n;
}

passenger *createPassenger(passenger *root, char NAME[50], char id[8], char btrain[30], char bstation[40], char Class[10], char dstation[40],int tid, char upgrade, char meal, char age[3], int seatno, int date)
{

    passenger *n = (passenger *)malloc(sizeof(passenger));
    if (root == NULL)
    {
        passenger *ret = newNode(NAME, id, btrain, bstation, Class, dstation, tid, upgrade, meal, age, seatno, date);
        return ret;
    }
    if (date < (root)->travel_date)
        (root)->left = createPassenger(root->left, NAME, id, btrain, bstation, Class, dstation, tid, upgrade, meal, age, seatno, date);
    else if (date > root->travel_date)
        (root)->right = createPassenger(root->right, NAME, id, btrain, bstation, Class, dstation, tid, upgrade, meal, age, seatno, date);
    else
        return root;

    (root)->NodeHeight = 1 + max(NodeHeight((root)->left), NodeHeight((root)->right));
    int b = getBalance(root);

    if (b > 1)
    {
        if (getBalance(root->left) >= 0)
        {
            root = rightRotate(root);
        }
        else if (getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
    }
    else if (b < -1)
    {
        if (getBalance(root->right) <= 0)
        {
            root = leftRotate(root);
        }
        else if (getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
    }

    return root;
}

void display_details(passenger *n)
{
    printf("Name: %s\n", n->name);
    printf("passenger ID: %s\n", n->id);
    printf("Boarding Station: %s\n", n->boardingStation);
    printf("Boarding Train: %s\n", n->boardingTrain);
    printf("Class Chosen: %s\n", n->Class);
    printf("Destination Station: %s\n", n->destinationStation);
    printf("Train ID: %d\n", n->TrainId);
    printf("Travel Data: %d\n", n->travel_date);
    printf("Seat Number: %d\n", n->seatNumber);
    printf("Upgrade Request: %c\n", n->upgrade);
    printf("Meal Included: %c\n", n->MealIncluded);
    printf("Reservation Status: %c\n", n->reservationStatus);
}
train* train_head = NULL;
passenger *getDetails(passenger *root)
{
    char NAME[50], id[8], btrain[30], bstation[40], Class[10], dstation[40], seatno[4], upgrade, meal, age[3];
    int seat_no, date, tid;
    printf("Enter the Name of the passenger: ");
    scanf("%s", NAME);
    fflush(stdin);
    printf("Enter age: ");
    scanf("%s", age);
    fflush(stdin);
    printf("Enter Boarding train name: ");
    scanf("%s", btrain);
    fflush(stdin);
    printf("Enter Boarding Station name: ");
    scanf("%s", bstation);
    fflush(stdin);
    printf("Enter the date of your travel: (mmddyy) ");
    scanf("%d", &date);
    fflush(stdin);
    printf("Enter which Class you prefer (Sleeper, 3AC, 2AC, AC) ");
    scanf("%s", Class);
    fflush(stdin);
    if (strcmp(Class, "Sleeper") == 0 && sleeper_seats < 51)
    {
        seat_no = sleeper_seats;
        sleeper_seats++;
    }
    else if (strcmp(Class, "3AC") == 0 && sleeper_seats < 101)
    {
        seat_no = threeAC_seats;
        threeAC_seats++;
    }
    else if (strcmp(Class, "2AC") == 0 && sleeper_seats < 151)
    {
        seat_no = twoAC_seats;
        twoAC_seats++;
    }
    else if (strcmp(Class, "AC") == 0 && oneAC_seats < 201)
    {
        {
            seat_no = oneAC_seats;
            oneAC_seats++;
        }
    }
    printf("Enter Destination Station name: ");
    scanf("%s", dstation);
    fflush(stdin);
    printf("Enter the train id: ");
    scanf("%d", &tid);
    fflush(stdin);
    fflush(stdin);
    printf("Would you like a upgrade of travel Class? (Y/N) ");
    scanf(" %c", &upgrade);
    fflush(stdin);
    printf("Would you like a meal during your travel? (Y/N) ");
    scanf(" %c", &meal);
    fflush(stdin);

    if(train_head != NULL){
        //train doesnt exist in database
        if(check_train_exists(train_head, tid) == NULL){        
            train_head = add_train(train_head, btrain, tid, date,0);
        }
        // if exists update passengers
        else {train_head = update_passengers(train_head, tid);}
    }
    else{ 
        train_head = add_train(train_head, btrain, tid, date,0);
    }    

    passenger *sd;
    sd = createPassenger(root, NAME, id, bstation, btrain, Class, dstation, tid, upgrade, meal, age, seat_no, date);
    return sd;
}

train* ret_train_head(){
    return train_head;
}

passenger *deleteReservation(passenger *root, char pass_id[50])
{
    if (root == NULL)
    {
        return root;
    }

    if (strcmp(pass_id, root->id) < 0)
    {
        root->left = deleteReservation(root->left, pass_id);
    }
    else if (strcmp(pass_id, root->id) > 0)
    {
        root->right = deleteReservation(root->right, pass_id);
    }
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            passenger *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }

            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            // get the inorder successor
            passenger *t = min_id_node(root->right);
            strcpy(root->name, t->name);
            strcpy(root->boardingStation, t->boardingStation);
            strcpy(root->boardingTrain, t->boardingTrain);
            strcpy(root->Class, t->Class);
            strcpy(root->destinationStation, t->destinationStation);
            strcpy(root->id, t->id);
            root->TrainId = t->TrainId;
            root->seatNumber = t->seatNumber;
            root->travel_date = t->travel_date;
            root->upgrade = t->upgrade;
            root->MealIncluded = t->MealIncluded;
            root->reservationStatus = t->reservationStatus;
            root->right = deleteReservation(root->right, t->id);
        }
    }

    if (root == NULL)
        return root;

    root->NodeHeight = 1 + max(NodeHeight(root->left), NodeHeight(root->right));

    int balance = getBalance(root);

    // left left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder_traversal(passenger *n)
{
    if (n == NULL)
        return;
    inorder_traversal(n->left);
    printf("Name: %s\n", n->name);
    printf("passenger ID: %s\n", n->id);
    printf("Boarding Station: %s\n", n->boardingStation);
    printf("Boarding Train: %s\n", n->boardingTrain);
    printf("Class Chosen: %s\n", n->Class);
    printf("Destination Station: %s\n", n->destinationStation);
    printf("Train ID: %d\n", n->TrainId);
    printf("Travel Data: %d\n", n->travel_date);
    printf("Seat Number: %d\n", n->seatNumber);
    printf("Upgrade Request: %c\n", n->upgrade);
    printf("Meal Included: %c\n", n->MealIncluded);
    printf("Reservation Status: %c\n", n->reservationStatus);
    inorder_traversal(n->right);
}

// passenger *getListDestination(passenger *root, int tid, char *des_station)
// {
//     if (strcmp(root->TrainId, tid) > 0 && strcmp(root->destinationStation, des_station) > 0)
//     {
//         root->right = getListDestination(root->left, tid, des_station);
//     }
// }

void preOrder(passenger *n)
{
    if (n != NULL)
    {
        // cout << root->key << " ";
        // display_details(root);
        printf("Name: %s\n", n->name);
        printf("passenger ID: %s\n", n->id);
        printf("Boarding Station: %s\n", n->boardingStation);
        printf("Boarding Train: %s\n", n->boardingTrain);
        printf("Class Chosen: %s\n", n->Class);
        printf("Destination Station: %s\n", n->destinationStation);
        printf("Train ID: %d\n", n->TrainId);
        printf("Travel Data: %d\n", n->travel_date);
        printf("Seat Number: %d\n", n->seatNumber);
        printf("Upgrade Request: %c\n", n->upgrade);
        printf("Meal Included: %c\n", n->MealIncluded);
        printf("Reservation Status: %c\n", n->reservationStatus);
        preOrder(n->left);
        preOrder(n->right);
    }
}