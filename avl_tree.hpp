#ifndef AVL_TREE
#define AVL_TREE

struct tAVLTreeNode {

    int             uData;
    size_t          uHeight;
    tAVLTreeNode *  uLeft;
    tAVLTreeNode *  uRight;
    tAVLTreeNode *  uNext;
    tAVLTreeNode *  uPrev;

    size_t          GetHeight    ();
                    tAVLTreeNode ();

};

class AVLTree {

  public:

                    AVLTree        ();
                    ~AVLTree       ();

    void            Insert         (int pData);
    void            Delete         (int pData);
    bool            Search         (int pData);
    void            Update         (int pOldData, int pNewData);
    tAVLTreeNode *  GetRoot        ();

  private:

    tAVLTreeNode *  Insert         (tAVLTreeNode * pNode, int pData);
    tAVLTreeNode *  Delete         (tAVLTreeNode * pNode, int pData);
    bool            Search         (tAVLTreeNode * pNode, int pData);

    tAVLTreeNode *  RotateLeft     (tAVLTreeNode * pNode);
    tAVLTreeNode *  RotateRight    (tAVLTreeNode * pNode);
    int             GetBalance     (tAVLTreeNode * pNode);
    tAVLTreeNode *  Balance        (tAVLTreeNode * pNode);
    void            DeleteAllNodes (tAVLTreeNode * pNode);

    tAVLTreeNode *  vRoot;
};

size_t Max (size_t pData1, size_t pData2); 

#endif // !AVL_TREE