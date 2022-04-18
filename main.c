#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "train.h"
#include "passenger.h"


void main()
{
    passenger *root = NULL, *t, *d;
    root = getDetails(root);
    root = getDetails(root);
    // root = getDetails(root);
    char s[30] = "Tushar12";
    train* T = ret_train_head();
    display_train(T);
    // root = deleteReservation(root, s);
    inorder_traversal(root);
}

