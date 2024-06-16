#include <new>
#include "avl_tree.hpp"

size_t tAVLTreeNode::GetHeight ()
{
    if (!this) {
        return 0;
    }
    return uHeight;
}

tAVLTreeNode::tAVLTreeNode () : uLeft (nullptr), uRight (nullptr), uNext (nullptr), uPrev (nullptr)
{
    uData = 0;
    uHeight = 1;
}

AVLTree::AVLTree () : vRoot (nullptr)
{
}

AVLTree::~AVLTree ()
{
    DeleteAllNodes (vRoot);
}

void AVLTree::Insert (int pData)
{
    vRoot = Insert (vRoot, pData);
}

void AVLTree::Delete (int pData)
{
    vRoot = Delete (vRoot, pData);
}

bool AVLTree::Search (int pData)
{
    return Search (vRoot, pData);
}

void AVLTree::Update(int pOldData, int pNewData)
{
    Delete (pOldData);
    Insert (pNewData);
}

tAVLTreeNode* AVLTree::GetRoot()
{
    return vRoot;
}

/*
* Normal BST insertion using recution
* if node became unbalanced, balance it
*/
tAVLTreeNode * AVLTree::Insert (tAVLTreeNode * pNode, int pData)
{
    tAVLTreeNode *  temp        = nullptr;
    tAVLTreeNode *  new_node    = nullptr;
    bool            insert      = false;

    // make new node
    if (!pNode) {
        temp = new (std::nothrow) tAVLTreeNode ();

        if (!temp) {
            return pNode;
        }
        temp->uData = pData;
        return temp;
    }

    // check insert left or right subtree
    if (pData < pNode->uData) {

        insert = !(pNode->uLeft);
        pNode->uLeft = Insert (pNode->uLeft, pData);

        // insert new node in linked list
        if (insert) {
            new_node = pNode->uLeft;

            new_node->uPrev = pNode->uPrev;
            new_node->uNext = pNode;

            if (pNode->uPrev) { 
                pNode->uPrev->uNext = new_node; 
            }
            pNode->uPrev = new_node;
        }

    } else if (pData > pNode->uData) {

        insert = !(pNode->uRight);
        pNode->uRight = Insert (pNode->uRight, pData);

        // insert new node in linked list
        if (insert) {
            new_node = pNode->uRight;

            new_node->uPrev = pNode;
            new_node->uNext = pNode->uNext;

            if (pNode->uNext) {
                pNode->uNext->uPrev = new_node;
            }
            pNode->uNext = new_node;
        }

    } else {
        return pNode;
    }

    // update height
    pNode->uHeight = Max (pNode->uLeft->GetHeight (), pNode->uRight->GetHeight ()) + 1;

    // Balance
    return Balance (pNode);
}

tAVLTreeNode* AVLTree::Delete (tAVLTreeNode* pNode, int pData)
{
        tAVLTreeNode * inorder_successor = nullptr;
        tAVLTreeNode * temp              = nullptr;

    if (!pNode) {
        return pNode;
    }

    // check delwte in left or right subtree
    if (pData < pNode->uData) {
        pNode->uLeft = Delete (pNode->uLeft, pData);

    } else if (pData > pNode->uData) {
        pNode->uRight = Delete (pNode->uRight, pData);

    } else {

        if (pNode->uLeft && pNode->uRight) {

            // both child
            inorder_successor = pNode->uNext;
            pNode->uData = inorder_successor->uData;

            pNode->uRight = Delete(pNode->uRight, inorder_successor->uData);

        } else if (!pNode->uLeft && !pNode->uRight) {

            // no child

            // remove node form liked list
            if (pNode->uPrev) {
                pNode->uPrev->uNext = pNode->uNext;
            }
            if (pNode->uNext) {
                pNode->uNext->uPrev = pNode->uPrev;
            }

            // del node
            // update pNode
            delete pNode;
            pNode = nullptr;

        } else {

            // one child

            // remove node form liked list
            if (pNode->uPrev) {
                pNode->uPrev->uNext = pNode->uNext;
            }
            if (pNode->uNext) {
                pNode->uNext->uPrev = pNode->uPrev;
            }

            temp = pNode->uRight;

            if (pNode->uLeft) {
                temp = pNode->uLeft;
            }

            // del node
            // update pNode
            delete pNode;
            pNode = temp;
        }

        //return pNode;
    }

    if (!pNode) {
        return pNode;
    }

    // update height
    pNode->uHeight = Max (pNode->uLeft->GetHeight (), pNode->uRight->GetHeight ()) + 1;

    // Balance
    return Balance (pNode);
}

bool AVLTree::Search (tAVLTreeNode * pNode, int pData)
{
    if (!pNode) {
        return false;
    }

    // find in left or right subtree
    if (pData < pNode->uData) {
        return Search (pNode->uLeft, pData);

    } else if (pData > pNode->uData) {
        return Search (pNode->uRight, pData);

    }

    return true;
}

tAVLTreeNode* AVLTree::RotateLeft (tAVLTreeNode* pNode)
{
        tAVLTreeNode * right_node       = nullptr;
        tAVLTreeNode * right_left_node  = nullptr;

    right_node = pNode->uRight; 
    right_left_node = right_node->uLeft; 
 
    // Perform rotation 
    right_node->uLeft = pNode; 
    pNode->uRight = right_left_node; 
 
    // Update heights 
    pNode->uHeight = Max (pNode->uLeft->GetHeight (), pNode->uRight->GetHeight ()) + 1;
    right_node->uHeight = Max (right_node->uLeft->GetHeight (), right_node->uRight->GetHeight ()) + 1;
 
    // Return new root 
    return right_node; 
}

tAVLTreeNode* AVLTree::RotateRight (tAVLTreeNode* pNode)
{
        tAVLTreeNode * left_node       = nullptr;
        tAVLTreeNode * left_right_node  = nullptr;

    left_node = pNode->uLeft; 
    left_right_node = left_node->uRight; 
 
    // Perform rotation 
    left_node->uRight = pNode; 
    pNode->uLeft = left_right_node; 
 
    // Update heights 
    pNode->uHeight = Max (pNode->uLeft->GetHeight (), pNode->uRight->GetHeight ()) + 1;
    left_node->uHeight = Max (left_node->uLeft->GetHeight (), left_node->uRight->GetHeight ()) + 1;
 
    // Return new root 
    return left_node; 
}

int AVLTree::GetBalance(tAVLTreeNode* pNode)
{
    if (!pNode) {
        return 0;
    }
    int bal = int (pNode->uLeft->GetHeight() - pNode->uRight->GetHeight());
    return bal;
}

tAVLTreeNode* AVLTree::Balance (tAVLTreeNode* pNode)
{
    if (!pNode) {
        return nullptr;
    }

        int balance_factor = GetBalance (pNode);

    // left left case
    if (balance_factor > 1 && GetBalance (pNode->uLeft) > 0) {
        return RotateRight (pNode);
    }

    // left right case
    if (balance_factor > 1 && GetBalance (pNode->uLeft) <= 0) {
        pNode->uLeft = RotateLeft (pNode->uLeft);  
        return RotateRight (pNode);
    }

    // right left case
    if (balance_factor < -1 && GetBalance (pNode->uLeft) > 0) {
        pNode->uRight = RotateRight (pNode->uRight);
        return RotateLeft (pNode);
    }

    // right right case
    if (balance_factor < -1 && GetBalance (pNode->uLeft) <= 0) {
        return RotateLeft (pNode);
    }

    return pNode;
}

void AVLTree::DeleteAllNodes (tAVLTreeNode * pNode)
{
    if (!pNode) {
        return;
    }

    DeleteAllNodes (pNode->uLeft);
    DeleteAllNodes (pNode->uRight);

    delete pNode;
    pNode = nullptr;
}

size_t Max (size_t pData1, size_t pData2)
{
    if (pData1 > pData2) {
        return pData1;
    }

    return pData2;
}
