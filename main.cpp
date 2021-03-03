#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "defn.h"
#include "bst.cpp"
#include <cstring>
using namespace std;


int main() {
    string queryInput;
    cin >> queryInput;
    int numCategories = stoi(queryInput);
    string catName;
    auto *app_categories = (struct categories *)malloc(numCategories * sizeof(struct categories));
    if (app_categories == nullptr)
    {
        fprintf(stderr, "malloc failed \n");
    }
    cin.ignore(100,'\n');
    //Read in all of the categories
    for (int i = 0; i < numCategories; i++) {
        getline(cin, catName);
        strcpy(app_categories[i].category,catName.c_str());
        app_categories[i].root = nullptr;

    }//end of reading in all categories.

    //Create the variables for running the loop

    cin >> queryInput;

    int numApps = stoi(queryInput);

    //Create the variables for creating the BST

    string name, category, version, units, tempSize, tempPrice;
    float size, price;
    int categoryIndex;

    ///////////////////////////////////////////////////////////////////////
    cin.ignore(100,'\n');
    //Loop to create the nodes for the apps
    for (int i = 0; i < numApps; i++)
    {
        //Create the node using malloc
        auto * newNode = (struct app_info*)malloc(numCategories * sizeof(struct app_info));

        //Assign all values to strings that will be later imported into struct app_info
        getline(cin, category);
        getline(cin, name);
        getline(cin, version);
        getline(cin, tempSize);
        getline(cin, units);
        getline(cin, tempPrice);

        //Convert strings to integers that need to change
        size = stof(tempSize);
        price = stof(tempPrice);

        //Assign all values into the newNode;
        strcpy(newNode->category, category.c_str());
        strcpy(newNode->app_name, name.c_str());
        strcpy(newNode->version, version.c_str());
        newNode->size = size;
        strcpy(newNode->units, units.c_str());
        newNode->price = price;

        //Find which BST this should be apart of
        for (int j = 0; j < numCategories; j++)
        {
            if (category == app_categories[j].category) {
                categoryIndex = j;
                break; //Don't run through everything once we get a match
            }
        }//End of search loop
        //Now we have the category index for app_categories, we can traverse the tree



    }//End of numApps for loop



    free(app_categories);

}//End of main
