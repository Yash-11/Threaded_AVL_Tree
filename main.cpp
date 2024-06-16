#include <stdio.h>
#include "avl_tree.hpp"

void DisplayInorderLinkedList (tAVLTreeNode * pRoot)
{
        tAVLTreeNode * temp = nullptr;

    printf ("\nUsing Linked list : ");

    temp = pRoot;
    while (temp->uLeft) {
        temp = temp->uLeft;
    }

    while (temp) {
        printf ("%d ", temp->uData);
        temp = temp->uNext;
    }
    printf ("\n");
}

void DisplayInorderRecursion (tAVLTreeNode * pNode)
{
    if (!pNode) {
        return;
    }

    DisplayInorderRecursion (pNode->uLeft);
    printf ("%d ", pNode->uData);
    DisplayInorderRecursion (pNode->uRight);
}

int main ()
{
        AVLTree avl;

    avl.Insert (8);
    avl.Insert (15);
    avl.Insert (3);
    avl.Insert (6);
    avl.Insert (11);
    avl.Insert (34);
    avl.Insert (57);
    avl.Insert (31);
    avl.Insert (16);
    avl.Insert (26);
    avl.Insert (67);
    avl.Insert (71);
    avl.Insert (5);

    printf ("\nUsing Recursion : ");
    DisplayInorderRecursion (avl.GetRoot ());
    DisplayInorderLinkedList (avl.GetRoot ());
 
    avl.Delete (5);
    avl.Delete (71);
    avl.Delete (67);
    avl.Delete (26);
    avl.Delete (16);
    avl.Delete (31);
    
    printf ("\nUsing Recursion : ");
    DisplayInorderRecursion (avl.GetRoot ());
    DisplayInorderLinkedList (avl.GetRoot ());

    printf ("\n31 present : %d", avl.Search (31));

    return 0;
}
