//#include "defn.h"
#include <iostream>
//
// Created by Justin on 3/3/2021.
//
//Function to add the node to the binary search tree (BST)
//nodeToAdd is the node we're adding, while node is the information of the node.
bst* insertNode(bst * node, app_info application)
{
    if (node == nullptr)
    {
        node = new bst;
        node->record = application;
        node->right = nullptr;
        node->left = nullptr;
    }
    //If the application name comes before, go to the left subtree
    else if (application.app_name[0] < node->record.app_name[0])
    {
        node->left = insertNode(node->right, application);
    }
    else if (application.app_name[0] >= node->record.app_name[0])
    {
        node->right = insertNode(node->right, application);
    }
    //If the application name comes before, go to the right subtree
    else
        std::cout << "yayeet";
    return nullptr;
}
