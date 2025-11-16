#ifndef libAVL
#define libAVL

#include<iostream>

using namespace std;

struct node{
    string info;
    node *left;
    node *right;
    int height;
};
 
int maxValue(int a, int b)
{
    return (a > b)? a : b;
}
 
int AVLHeight(node *p)
{
    if (p == NULL)
        return 0;
    return 1+maxValue(AVLHeight(p->left), AVLHeight(p->right));
}
 
node* newNode(string value)
{
    node* Node = new node;
    Node->info   = value;
    Node->left   = NULL;
    Node->right  = NULL;
    Node->height = 0; 
    return(Node);
}
 
node *rotateRight(node *p)
{
    node *q = p->left;
    node *temp = q->right;
 
    q->right = p;
    p->left = temp;
 
    p->height = AVLHeight(p);
    q->height = AVLHeight(q);
 
    return q;
}
 
node *rotateLeft(node *p)
{
    node *q = p->right;
    node *temp = q->left;
 
    q->left = p;
    p->right = temp;
 
    p->height = AVLHeight(p);
    q->height = AVLHeight(q);
 
    return q;
}
 
int getBalance(node *N) {
    if (N == NULL)
        return 0;
    return AVLHeight(N->right) - AVLHeight(N->left);
}
 
node* insertAVL(node* T, string value) {
	int fb;
    if (T == NULL)
        return(newNode(value));
 
    if (value < T->info)
        T->left  = insertAVL(T->left, value);
    else if (value > T->info)
        T->right = insertAVL(T->right, value);
    else 
        return T;
 
    T->height = AVLHeight(T);
 
    fb = getBalance(T);
 
    if (fb > 1 && value > T->right->info)
	{
		return rotateLeft(T);
	}
      
    if (fb < -1 && value < T->left->info)
	{
        return rotateRight(T);
    }
 
    if (fb > 1 && value < T->right->info)
    {
	    T->right =  rotateRight(T->right);
        return rotateLeft(T);
    }
 
    if (fb < -1 && value > T->left->info)
    {
        T->left = rotateLeft(T->left);
        return rotateRight(T);
    }
 
    return T;
}
 
void preOrderAVL(node *T)
{
    if(T != NULL)
    {
        cout << T->info << endl;
        preOrderAVL(T->left);
        preOrderAVL(T->right);
    }
}

void inOrderAVL(node *T)
{
    if(T != NULL)
    {
        inOrderAVL(T->left);
        cout << T->info << endl;
		inOrderAVL(T->right);
    }
} 

void postOrderAVL(node *T)
{
    if(T != NULL)
    {
        postOrderAVL(T->left);
        postOrderAVL(T->right);
        cout << T->info << endl;
    }
}

void showByLevel(node *T, int level, int getDown) {
	if (T == NULL) return;
		if (level == getDown) {
                cout << T->info << " - ";
	} else if (level < getDown) {
				showByLevel(T->left,level + 1, getDown);
				showByLevel(T->right,level + 1, getDown);
	}
}

void AVLWidth(node *T) {
	int height = AVLHeight(T);
	for (int i = 1; i <= height+1; ++i) {
		showByLevel(T, 1, i);
        cout << endl;
	}
}

bool search(node *T, string hash) {
    if(T == NULL) {
        return false;
    }
    if(T->info == hash) {
        return true;
    }
    if(T->info > hash) {
        return search(T->left, hash);
    }
    if(T->info < hash) {
        return search(T->right, hash);
    }
    return false;
}

#endif