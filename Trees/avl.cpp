#include<bits/stdc++.h>
#include<fstream>

using namespace std;

class Node {
	public:
	int key;
	Node* left;
	Node* right;
	int height;
};

int height(Node* node) {
	if (node == NULL)
		return 0;
	return node->height;
}

Node* newNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially 
                      // added at leaf  
    return(node);  
}  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left), 
                    height(y->right)) + 1;  
    x->height = max(height(x->left), 
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  
  
// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree.  
Node* insert(Node* node, int key)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
    else // Equal keys are not allowed in BST  
        return node;  
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    /* 3. Get the balance factor of this ancestor  
        node to check whether this node became  
        unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}

void inorder(Node* x, ofstream &file) {
	if (x == NULL)
		return;
	inorder(x->left, file);
	file << x->key << " ";
	inorder(x->right, file);
}

void makeTreeComplete(Node* x, int maxHeight, int depth) {
	if (depth == maxHeight)
		return;
	if (x->left == NULL)
		x->left = newNode(-100000);
	if (x->right == NULL)
		x->right = newNode(-100000);
	makeTreeComplete(x->left, maxHeight, depth+1);
	makeTreeComplete(x->right, maxHeight, depth+1);
}

int nodes(Node* x) {
	if (x == NULL)
		return 0;
	return nodes(x->left) + nodes(x->right) + 1;
}

void printSpace() {
    cout << "   ";
}

void printNode(Node* x) {
    cout << " " << x->key << " ";
}

void printLevel(Node* x, int level) {
    if (x == NULL)
        printSpace();
    if (level == 1)
        printNode(x);
    else if (level > 1) {
        printLevel(x->left, level-1);
        printLevel(x->right, level-1);
    }
}

void printTree(Node* root, int maxHeight) {
    double spacing = pow(2, maxHeight - 1);
    for (int i = 0; i < maxHeight; i++) {
        
        // print preceding spaces
        for (int j = 0; j < spacing; j++)
            printSpace();

        printLevel(root, i);

        spacing--;
    }
}

int main() {
	
	
	int NUM = rand()%51 + 50;
	
	ofstream outfile1;
	outfile1.open("input.txt");		
	while (NUM-- > 0) {
		outfile1 << rand()%100001 << " ";
	}
	outfile1.close();
	
	Node* root = NULL;
	ifstream infile;
	infile.open("input.txt");
	int val;
	while (infile >> val) {
		root = insert(root, val);	
	}

	ofstream outfile;
	outfile.open("output.txt");
	inorder(root, outfile);
	outfile << endl;
	outfile.close();

	cout << nodes(root) << endl;
	makeTreeComplete(root, height(root), 1);
	cout << nodes(root) << endl;
    
}
