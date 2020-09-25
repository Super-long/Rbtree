#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Rbtree{
private:
    enum class RBTColor {RED, BLACK};

    #define rb_parent(r)   ((r)->parent)
    #define rb_color(r) ((r)->color)
    #define rb_is_red(r)   ((r)->color==RBTColor::RED)
    #define rb_is_black(r)  ((r)->color==RBTColor::BLACK)
    #define rb_set_black(r)  do { (r)->color = RBTColor::BLACK; } while (0)
    #define rb_set_red(r)  do { (r)->color = RBTColor::RED; } while (0)
    #define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
    #define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

    template <typename Type> 
    class RbtNode{
        public:
            RBTColor color;
            Type key;
            RbtNode* parent;
            RbtNode* left;
            RbtNode* right;
            RbtNode(T value, RBTColor c, 
                RbtNode *p = nullptr, RbtNode *l = nullptr, RbtNode *r = nullptr)
                :key(value),color(c),parent(),left(l),right(r) {}
    };

    RbtNode<T>* TreeRoot;

    // 在插入或者删除一个节点以后的再平衡操作
    void InsertRebalance(Rbtree<T>::RbtNode<T>* node);
    void RemoveRebalance(Rbtree<T>::RbtNode<T>* node);
    
    // 对x节点进行旋转
    void leftRotate(Rbtree<T>::RbtNode<T>* x);
    void rightRotate(Rbtree<T>::RbtNode<T>* y);

    // 用于在删除时找到要删除的节点
    Rbtree<T>::RbtNode<T>* Search(T key);

    // ------------- 测试用函数
    void print(Rbtree<T>::RbtNode<T>* tree, T key, int direction);

public:

    Rbtree();
    ~Rbtree();

    bool remove(T key);
    bool insert(T key);

    // ------------- 测试用函数
    void print();
};

template <typename T>
Rbtree<T>::Rbtree():TreeRoot(nullptr){}

template <typename T>
Rbtree<T>::~Rbtree(){
    cout << "先不析构 后面再说\n";
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值 后面用于保存父节点的键
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */

template <typename T>   
void Rbtree<T>::print(Rbtree<T>::RbtNode<T>* tree, T key, int direction){
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            cout << setw(4) << tree->key << "(B) is root" << endl;
        else                // tree是分支节点
            cout << setw(4) << tree->key <<  (rb_is_red(tree)?"(R)":"(B)") << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <typename T>
void Rbtree<T>::print()
{
    if (TreeRoot != NULL)
        print(TreeRoot, TreeRoot->key, 0);
}


/*  
 * 偷一个示意图，非常的直观
 * 对x进行左旋
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \       --(左旋)-->           / \ 
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 */

template <typename T>
void Rbtree<T>::leftRotate(Rbtree<T>::RbtNode<T>* x){
    RbtNode<T>* y = x->right;

    x->right = y->left;
    if(y->left != nullptr){
        y->left->parent = x;    // ly此时关联完毕
    }

    y->parent = x->parent;
    if(x->parent == nullptr){   // x->parent为根节点
        TreeRoot = y;
    } else {
        if(x->parent->left == x){
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    }
    y->left = x;    // y关联完毕

    x->parent = y;
}

/*
 * 对y进行右旋
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \ 
 *        x   ry                           lx   y
 *       / \                                   / \ 
 *      lx  rx                                rx  ry
 *
 */

template <typename T>
void Rbtree<T>::rightRotate(Rbtree<T>::RbtNode<T>* y){
    RbtNode<T>* x = y->left;
    y->left = x->right;

    if(x->right != nullptr){
        x->right->parent = y;
    }

    x->parent = y->parent;

    if(y->parent == nullptr){
        TreeRoot = x;
    } else {
        if (y->parent->right == y){
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
    }
    x->right = y;
    // x 关联完毕

    y->parent = x;
}

template <typename T>
bool Rbtree<T>::insert(T key){

    // 步骤1：创建节点并初始化
    RbtNode<T>* newNode = nullptr;
    // 新插入的节点颜色为红色
    newNode = new RbtNode<T>(key, RBTColor::RED);
    if(newNode == nullptr){
        return false;
    }
    
    // 步骤2：找到该插入的地方并插入
    RbtNode<T>* helper = TreeRoot;
    RbtNode<T>* newNodeParent = nullptr;

    while(helper != nullptr){
        newNodeParent = helper; // 跳出循环以后newNodeParent是新插入节点的父亲
        if(newNode->key < helper->key){
            helper = helper->left;
        } else {
            helper = helper->right;
        }
    }
    newNode->parent = newNodeParent;

    if(newNodeParent != nullptr){
        if(newNode->key < newNodeParent->key){
            newNodeParent->left = newNode;
        } else {
            newNodeParent->right = newNode;
        }
    } else {
        TreeRoot = newNode; // 树为空把root赋为newNode
    }

    // 步骤3：对这个新插入节点的树进行平衡
    InsertRebalance(newNode);
    
    return true;
}

template <typename T>
void Rbtree<T>::InsertRebalance(Rbtree<T>::RbtNode<T>* node){
    RbtNode<T>* parent = nullptr;
    RbtNode<T>* grandparent = nullptr;

    // 因为插入的节点为红色，parent是黑色显然就不需要修改了
    while((parent = rb_parent(node)) && rb_is_red(parent)){
        grandparent = rb_parent(parent);

        // 父节点是祖先的左孩子
        if(parent == grandparent->left){
            RbtNode<T>* uncle = grandparent->right; // 得到父节点的兄弟节点，即uncle
            // 情况1：uncle为红色
            if(uncle && rb_is_red(uncle)){
                rb_set_red(grandparent);
                rb_set_black(parent);
                rb_set_black(uncle);

                // grandparent变红 上面的节点可能出现两个红 需要递归修改
                node = grandparent;
                continue;
            }

            // 情况2：uncle为黑色，插入节点为右孩子
            if(parent->right == node){
                RbtNode<T>* temp = nullptr;
                leftRotate(parent);
                temp = parent;
                parent = node;
                node = temp;
            }

            // 情况3：uncle为黑色，插入的节点为左孩子
            rb_set_black(parent);
            rb_set_red(grandparent);
            rightRotate(grandparent);
            // 情况4：新节点的父亲为黑不需要操作，
            // 情况5：插入的节点为根节点颜色要变黑
        } else {    
            // 父节点是祖先的右孩子
            // 操作与上面一样，不再注释
            RbtNode<T>* uncle = grandparent->left; 

            if(uncle && rb_is_red(uncle)){
                rb_set_red(grandparent);
                rb_set_black(parent);
                rb_set_black(uncle);

                node = grandparent;
                continue;
            }

            if(parent->left == node){
                RbtNode<T> *temp;
                rightRotate(parent);
                temp = parent;
                parent = node;
                node = temp;
            }

            rb_set_black(parent);
            rb_set_red(grandparent);
            leftRotate(grandparent);
        }
    }
    
    // 情况5：在第一次插入时有效和递归修改了根节点以后有效
    rb_set_black(TreeRoot);
}

template<typename T>
bool Rbtree<T>::remove(T key){

}

template<typename T>
void Rbtree<T>::RemoveRebalance(Rbtree<T>::RbtNode<T>* node){

}

#endif  //RED_BLACK_TREE_H_