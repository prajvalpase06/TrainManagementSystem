#ifndef PASSENGER_H
#define PASSENGER_H


typedef struct avl_node
{
    char name[50];
    char id[8];
    char boardingTrain[30];
    char boardingStation[40];
    char Class[10];
    char destinationStation[40];
    int TrainId;
    int seatNumber;
    char upgrade;
    char MealIncluded;
    int travel_date; // in the form mmddyy
    struct avl_node *left;
    struct avl_node *right;
    char reservationStatus;
    int NodeHeight;
} passenger;

int NodeHeight(passenger *n);
passenger *leftRotate(passenger *n);
passenger *rightRotate(passenger *n);
int getBalance(passenger *n);
train* ret_train_head();
void display_details(passenger *n);
passenger *min_id_node(passenger *p);
passenger *newNode(char name[50], char id[8], char btrain[30], char bstation[40], char Class[10], char dstation[40], int tid, char upgrade, char meal, char age[3], int seat, int date);
passenger *createPassenger(passenger *root, char NAME[50], char id[8], char btrain[30], char bstation[40], char Class[10], char dstation[40], int tid, char upgrade, char meal, char age[3], int seatno, int date);
passenger *getDetails(passenger *root);
passenger *deleteReservation(passenger *root, char pass_id[50]);
void inorder_traversal(passenger *n);
passenger *getListDestination(passenger *root, int tid, char *des_station);
void preOrder(passenger *n);

#endif