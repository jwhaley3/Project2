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
void printFree(bst * node)
{
    if (node == NULL)
        return;
    //traverse the left tree
    printFree(node->left);

    //Then print the information of the tree
    if (node->record.price == 0.00) {
        std::cout << '\t' << node->record.app_name << '\n';
    }

    //Then print from the right subtree
    printFree(node->right);
}
void printInRange(bst* node, float high, float low)
{

    if (node == NULL)
        return;
    //traverse the left tree
    printInRange(node->left, high, low);

    //Then print the information of the tree
    if (node->record.price >= low && node->record.price <= high) {
        std::cout << '\t' << node->record.app_name << '\n';
    }

    //Then print from the right subtree
    printInRange(node->right, high, low);
    return;
}
bool printInRange(bst* node, float high, float low, bool flag)
{

    if (node == NULL)
        return flag;
    //traverse the left tree
    printInRange(node->left, high, low, flag);

    //Then print the information of the tree
    if (node->record.price >= low && node->record.price <= high) {
        flag = true;
    }

    //Then print from the right subtree
    printInRange(node->right, high, low, flag);
    return flag;
}

void findApp(bst* node, std::string name)
{
    if (node == NULL)
        return;
    //traverse the left tree
    findApp(node->left, name);

    //Then print the information of the tree
    if (node->record.app_name == name) {
        std::cout << '\t' << "Category: " << node->record.category << '\n';
        std::cout << '\t' << "Application Name: " << node->record.app_name << '\n';
        std::cout << '\t' << "Version: " << node->record.version << '\n';
        std::cout << '\t' << "Size: " << node->record.size << '\n';
        std::cout << '\t' << "Units: " << node->record.units << '\n';
        std::cout << '\t' << "Price: $" << node->record.price << "\n\n";
    }

    //Then print from the right subtree
    findApp(node->right, name);
}
void printInNumericalRange(bst * node, std::string start, std::string end)
{
    if (node == NULL)
        return;
    printInNumericalRange(node->left, start, end);

    //Printing the information from the tree
    if (strcmp(node->record.app_name, start.c_str()) >=0 && strcmp(node->record.app_name, end.c_str()) <= 0)
        std::cout << '\t' << node->record.app_name << '\n';

    printInNumericalRange(node->right, start, end);
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
struct bst* minValueNode(struct bst* node)
{
    struct bst* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
struct bst * deleteSingleBST(bst * root, std::string name)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (std::strcmp(name.c_str(), root->record.app_name) < 0)
        root->left = deleteSingleBST(root->left, name);

        // If the key to be deleted
        // is greater than the root's
        // key, then it lies in right subtree
    else if (std::strcmp(name.c_str(), root->record.app_name) > 0)
        root->right = deleteSingleBST(root->right, name);

        // if key is same as root's key,
        // then This is the node
        // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct bst* temp = root->right;
            free(root);
            root = NULL;
            return temp;
        }
        else if (root->right == NULL) {
            struct bst* temp = root->left;
            free(root);
            root = NULL;
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct bst* temp = minValueNode(root->right);

        // Copy the inorder
        // successor's content to this node
        strcpy(root->record.category, temp->record.category);
        strcpy(root->record.app_name, temp->record.app_name);
        strcpy(root->record.version, temp->record.version);
        root->record.size = temp->record.size;
        strcpy(root->record.units, temp->record.units);
        root->record.price = temp->record.price;



        // Delete the inorder successor
        root->right = deleteSingleBST(root->right, temp->record.app_name);
    }
    return root;

}