//
// Created by Justin on 3/23/2021.
//
#include "prime.cpp"
#include "defn.h"

int HashFunc(int key, int tableSize)
{
    return key % tableSize;
}

void insertToHash(bst* node, int key, int tableSize, std::string name)
{
    int hash_val = HashFunc(key, tableSize);

    return;
}