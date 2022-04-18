// DSPD - ASSIGNMENT2 ( USED AVL TREES)
// BT20CSE097 - PRAJVAL PASE
// gcc compiler used to compile passenger.c train.c main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "train.h"
#include "passenger.h"

void main()
{
    passenger *root = NULL, *t, *d;
    int n;
    printf("Enter\n1)to insert new passenger details: \n2)to delete passenger details\n3)to get the list of the passengers having same destination and train id\n4)Display the list of destination stations for a particular passenger sorted by dates of travel\n5)to display train details sorted by no. of passengers\n6)to promote passengers to next available class: ");
    int choice;
    scanf("%d", &choice);
    train *T = ret_train_head();
    switch (choice)
    {
        case 1:
        {
            int n;
            printf("\nEnter the number of passengers to be added: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                root = getDetails(root);
            }
            inorder_traversal(root);
            printf("\nRegistration for all %d passengers has been completed successfully!", n);
            break;
        }
        case 2:
        {
            char id_to_deleted[50];
            printf("\nEnter the passenger id: ");
            scanf("%s", id_to_deleted);
            deleteReservation(root, id_to_deleted);
            printf("Passenger registration deleted successfully. \n");
            printf("After deleting the passenger: \n");
            inorder_traversal(root);
            break;
        }
        case 3:
        {
            char id[10];
            char ds[50];
            printf("Enter train id and destination station: ");
            scanf("%s", id);
            fflush(stdin);
            scanf("%s", ds);
            fflush(stdin);
            passenger *newlist;
            newlist = getListDestination(root, ds, id);
            printf("New list has been created successfully!");
            break;
        }
        case 4:
        {
            char pd[50];
            printf("Enter the passenger id: ");
            scanf("%s", pd);
            SortByTravelDate(root, pd);
            break;
        }

        case 5:
        {
            // Since insertion into train database is done w.r.t num of passengers, LVR can print the sorted order
            inorder_train(T);
            break;
        }
        case 6:
        {
            int low, high;
            printf("Enter the lower bound of the range: ");
            scanf("%d", &low);
            printf("Enter the upper bound of the range: ");
            scanf("%d", &high);
            rangeSearch(T, low, high);
        }
        default:
            printf("Enter right choice.");
            break;
    }
}
