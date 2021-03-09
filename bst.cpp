//#include "defn.h"
#include <iostream>
//
// Created by Justin on 3/3/2021.
//
//Function to add the node to the binary search tree (BST)
//nodeToAdd is the node we're adding, while node is the information of the node.
struct bst * newNode(app_info key);
bst* insertNode(bst * node, app_info application)
{
    if (node == nullptr)
    {
        return newNode(application);
    }
    //If the application name comes before, go to the left subtree
    else if (strcmp(application.app_name, node->record.app_name) < 0)
    {
        node->left = insertNode(node->left, application);
    }
    //If the application name comes before, go to the right subtree
    else if (strcmp(application.app_name, node->record.app_name) > 0)
    {
        node->right = insertNode(node->right, application);
    }
    else
        //Shouldn't hit this, for error checking
        std::cout <<"yayeet";

    return node;
}
////////////////////////////////////////////////////////
//Given the root of the BST, going to traverse it (inorder)
//and print out the information associated with it


void printInorder(bst * node)
{
    if (node == NULL)
        return;
    //Traverse the left tree
    printInorder(node->left);

    //Then print the information of the tree
    std::cout << '\t' << node->record.app_name << '\n';

    //Then print the right subtree
    printInorder(node->right);

}
struct bst * newNode(app_info key)
{
    //Assign info, helper method
    struct bst *temp = new bst;
    temp->record = key;
    temp->right = nullptr;
    temp->left = nullptr;
    return temp;

}
int addToArray(bst * node, float arr[], int i)
{

    //If that's the end of node, return the position in heap array
    if(node == NULL)
        return i;

    //Assign value into the array
    arr[i] = node->record.price;
    i++;
    //Search the rest of the BST while incrementing i
    if(node->left != NULL)
        i = addToArray(node->left, arr, i);
    if(node->right != NULL)
        i = addToArray(node->right, arr, i);

    return i;
}

void printMax(bst * node, float price)
{
    if (node == NULL)
        return;
    //Traverse the left tree
    printMax(node->left, price);

    //Then print the information of the tree
    if (node->record.price == price)
        std::cout << '\t' << node->record.app_name << '\n';


    //Then print the right subtree
    printMax(node->right, price);

}
void heapify(float arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
void buildHeap(float arr[], int n)
{
    // Index of last non-leaf node
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
}
void deleteBST(bst * root)
{
    // If node is empty, do nothing
    if (root == NULL) { return; }

    // Delete subtrees
    deleteBST(root->left);
    deleteBST(root->right);

    // Delete current node
    free(root);
    root = NULL;
}
