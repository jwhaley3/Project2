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
        struct app_info newNode;


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
        strcpy(newNode.category, category.c_str());
        strcpy(newNode.app_name, name.c_str());
        strcpy(newNode.version, version.c_str());
        newNode.size = size;
        strcpy(newNode.units, units.c_str());
        newNode.price = price;

        //Find which BST this should be apart of
        for (int j = 0; j < numCategories; j++)
        {
            if (category == app_categories[j].category) {
                categoryIndex = j;
                break; //Don't run through everything once we get a match
            }
        }//End of search loop
        //Now we have the category index for app_categories, we can traverse the tree
        app_categories[categoryIndex].root = insertNode(app_categories[categoryIndex].root, newNode);

        //Node created and added

    }//End of numApps for loop

    /////////////////////////////////////////////////////////////////
    //We have the nodes added at this point
    //Read in the number of queries
    int numQueries;
    cin >> numQueries;
    //string will be useful in shortening the length of the if statements.
    string a = "print-apps";
    string b = "find";

    string rawCatToSearch, catToSearch, useless, queryType;

    for (int i = 0; i < numQueries; i++)
    {
        cin >> queryType;
        //cout << queryType;

        if (a == queryType)
        {
            ///////////////////////////////////////////////////////////
            //print-apps
            ///////////////////////////////////////////////////////////
            //Within this function, we know that there is 2 more inputs
            //The second one is guranteed to be category, so that doesn't matter
            //The only question is, after we read that, can we read the last input as readline? //We absolutely can
            cin >> useless; //Contains "Category"
            getline(cin, rawCatToSearch);// contains < "Social Networking"> Mind the space at the begginning

            //Manipulating the string using strtok to find the contents between the quotes (")
            size_t pos = rawCatToSearch.find("\"");
            catToSearch = rawCatToSearch.substr(pos + 1,rawCatToSearch.length() - 3);

            //catToSearch now contains the correct category with the proper formatting as what's already read into the
            //array
            //Find which BST this should be apart of
            for (int j = 0; j < numCategories; j++)
            {
                if (catToSearch == app_categories[j].category) {
                    categoryIndex = j;
                    break; //Don't run through everything once we get a match
                }
            }//End of search loop
            cout << "print-apps category \"" << catToSearch << "\"\n";
            cout << "Category: " << catToSearch << '\n';
            if (app_categories[categoryIndex].root == nullptr)
                cout << "Category: " << catToSearch << " no apps found\n";
            else {
                printInorder(app_categories[categoryIndex].root);
            }


        }
        else if (b == queryType)
        {
            ////////////////////////////////////////////////
            //find max price apps <category name>
            ////////////////////////////////////////////////
            cin >> useless;
            cin >> useless;
            cin >> useless;

            getline(cin, rawCatToSearch);// contains < "Social Networking"> Mind the space at the begginning

            //Manipulating the string using substr to find the contents between the quotes (")
            size_t pos = rawCatToSearch.find("\"");
            catToSearch = rawCatToSearch.substr(pos + 1,rawCatToSearch.length() - 3);

            //catToSearch now contains the correct category with the proper formatting as what's already read into the
            //array
            //Find which BST this should be apart of
            for (int j = 0; j < numCategories; j++)
            {
                if (catToSearch == app_categories[j].category) {
                    categoryIndex = j;
                    break; //Don't run through everything once we get a match
                }
            }//End of search loop
            cout << "find max price apps" << rawCatToSearch << '\n';
            cout << "Category: " << catToSearch << '\n';

            //Create the array of floats
            float *heap = (float *) malloc(numApps * sizeof( float ));
            //Traverse the tree and copy the info
            addToArray(app_categories[categoryIndex].root, heap, 0);

            //At this point, we have to traverse the tree and print all nodes with the price.
            buildHeap(heap, numApps);
            //cout << heap[0];
            printMax(app_categories[categoryIndex].root, heap[0]);

            free(heap);


        }
        else
            cout << "no report";


    }



    free(app_categories);

}//End of main
