#include <iostream>
#include <string>
#include <cstring>
#include "defn.h"
#include "bst.cpp"
//#include "hash.cpp"
#include "prime.cpp"

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

    //Create the hash table
    int hashFunction = TestForPrime(numApps*2);
    hash_table_entry **hash_table;
    hash_table = (struct hash_table_entry **) malloc( hashFunction * sizeof(struct hash_table_entry * ) );
    free(hash_table);
    for(int i = 0; i < hashFunction; i++ )
        hash_table[ i ] = NULL;


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
    //Go through all the categories and add all the information into a hash table
    //strcpy(node->app_name, name.c_str());
    //hash_table[i] = node;

    /////////////////////////////////////////////////////////////////
    //We have the nodes added at this point
    //Read in the number of queries
    int numQueries;
    cin >> numQueries;
    //string will be useful in shortening the length of the if statements.
    string a = "print-apps";
    string b = "find";
    string c = "range"; //There are 2 queries that start with this

    //Variables that are going to be used within both query operations.
    string rawCatToSearch, catToSearch, useless, queryType, next;

    for (int i = 0; i < numQueries; i++) {
        cin >> queryType;

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
            if (app_categories[categoryIndex].root == nullptr)
                cout << "Category: \"" << catToSearch << "\" no apps found.\n";
            else {
                cout << "Category: \"" << catToSearch << "\"\n";
                printInorder(app_categories[categoryIndex].root);
            }
            cout << "\n";


        }
        else if (b == queryType) {
            cin >> next;
            if (next == "max") {
                ////////////////////////////////////////////////
                //find max price apps <category name>
                ////////////////////////////////////////////////
                //get rid of price and apps
                cin >> useless;
                cin >> useless;

                getline(cin, rawCatToSearch);// contains < "Social Networking"> Mind the space at the beginning

                //Manipulating the string using substr to find the contents between the quotes (")
                size_t pos = rawCatToSearch.find("\"");
                catToSearch = rawCatToSearch.substr(pos + 1, rawCatToSearch.length() - 3);

                //catToSearch now contains the correct category with the proper formatting as what's already read into the
                //array
                //Find which BST this should be apart of
                for (int j = 0; j < numCategories; j++) {
                    if (catToSearch == app_categories[j].category) {
                        categoryIndex = j;
                        break; //Don't run through everything once we get a match
                    }
                }//End of search loop
                cout << "find max price apps" << rawCatToSearch << '\n';

                if (app_categories[categoryIndex].root == nullptr)
                    cout << "Category: \"" << catToSearch << "\" no apps found.\n\n";
                else {
                    //printInorder(app_categories[categoryIndex].root);

                    //Create the array of floats
                    float *heap = (float *) malloc(numApps * sizeof(float));
                    //Traverse the tree and copy the info
                    addToArray(app_categories[categoryIndex].root, heap, 0);

                    //At this point, we have to traverse the tree and print all nodes with the price.
                    buildHeap(heap, numApps);
                    printMax(app_categories[categoryIndex].root, heap[0]);

                    cout << "\n";
                    //The heap is only used for this query, delete it before moving on to the next query.
                    free(heap);
                }


            }
            else if (next == "price"){
                ///////////////////////////////////////////////
                //find price free <category_name>
                ///////////////////////////////////////////////
                cin >> useless;

                getline(cin, rawCatToSearch);// contains < "Social Networking"> Mind the space at the beginning

                //Manipulating the string using substr to find the contents between the quotes (")
                size_t pos = rawCatToSearch.find("\"");
                catToSearch = rawCatToSearch.substr(pos + 1, rawCatToSearch.length() - 3);
                //We now have the printing string "rawCatToSearch" and the usefull string catToSearch

                //Find which BST this should be apart of
                for (int j = 0; j < numCategories; j++) {
                    if (catToSearch == app_categories[j].category) {
                        categoryIndex = j;
                        break; //Don't run through everything once we get a match
                    }
                }//End of search loop
                if (catToSearch != app_categories[categoryIndex].category)
                {
                    cout << "Category " << catToSearch << " not found." << '\n';
                    break;
                }
                if (app_categories[categoryIndex].root == nullptr)
                    cout << "Category: \"" << catToSearch << "\" no free apps found.\n\n";
                else {
                    //At this point, we have to traverse the tree and print all nodes with the price.
                    cout << "Free apps in category:" << rawCatToSearch << '\n';
                    printFree(app_categories[categoryIndex].root);

                    cout << "\n";
                }

            }
            else if (next == "app")
            {
                /////////////////////////////////////
                //find app <app_name>
                /////////////////////////////////////
                string gameName;
                //Search all categories in order to find the application with the matching application name
                getline(cin, gameName);
                gameName = gameName.substr(2, gameName.length() - 3); //contains only the name
                bool found;
                int k = 0;
                for ( k = 0; k < numCategories; k++) {
                    findApp(app_categories[k].root, gameName);
                }



            }
        }
        else if (c == queryType)
        {
            ////////////////////////////
            //Dealing with range
            //input type  range <category name> price <low> <high>
            ////////////////////////////
            string wholeInput;

            getline(cin, wholeInput); //contains  "category name" price float float //Mind the gap
            size_t pos = wholeInput.find("\"");
            catToSearch = wholeInput.substr(pos + 1, wholeInput.length());
            pos = catToSearch.find("\"");
            catToSearch = catToSearch.substr(0, pos); //catToSearch now contains category name
            //In the test case, it contains Games as expected
            //Going to reduce whole input to everything after category name to ensure that catname isn't price, when searching
            //for price
            pos = wholeInput.find("\"");
            string priceLowHigh = wholeInput.substr(pos, wholeInput.length());
            pos = priceLowHigh.find("\"");
            priceLowHigh = priceLowHigh.substr(pos, priceLowHigh.length());
            pos = priceLowHigh.find(" ");
            string test = priceLowHigh.substr(pos + 1, 3);
            priceLowHigh = priceLowHigh.substr(pos, priceLowHigh.length());
            if (test == "app")
            {
                //app test
                pos = priceLowHigh.find("\"");
                string firstVal = priceLowHigh.substr(pos + 1, priceLowHigh.length());
                pos = firstVal.find("\"");
                firstVal = firstVal.substr(0, pos);
                //Now have obtained the first value
                pos = priceLowHigh.find("\"");
                string secondVal = priceLowHigh.substr(pos, priceLowHigh.length());
                pos = secondVal.find("\"");
                secondVal = secondVal.substr(pos+1, secondVal.length()-1);
                pos = secondVal.find("\"");
                secondVal = secondVal.substr(pos+1, secondVal.length());
                pos = secondVal.find("\"");
                secondVal = secondVal.substr(pos+1, secondVal.length()-3);


                //Contains the second value
                //Find which BST this should be apart of
                for (int j = 0; j < numCategories; j++) {
                    if (catToSearch == app_categories[j].category) {
                        categoryIndex = j;
                        break; //Don't run through everything once we get a match
                    }
                }//End of search loop

                if (catToSearch != app_categories[categoryIndex].category) {
                    cout << "Category " << catToSearch << " not found." << '\n';
                    break;
                }
                if (app_categories[categoryIndex].root == nullptr)
                    cout << "No applications found in " << catToSearch << " for the given range " << firstVal << " " << secondVal
                         << "\n\n";
                else {
                    cout << "Applications in Price Range (" << firstVal << ", " << secondVal << ") in Category: " << catToSearch
                         << "\n";

                    printInNumericalRange(app_categories[categoryIndex].root, firstVal, secondVal);
                    cout << "\n";

                }

            }
            else {

                //Should contain the two floats at this point
                priceLowHigh = priceLowHigh.substr(7, priceLowHigh.length());
                float low = -1;
                low = stof(priceLowHigh.substr(0, 4));
                float high = -1;
                high = stof(priceLowHigh.substr(5, 4));


                //Find which BST this should be apart of
                for (int j = 0; j < numCategories; j++) {
                    if (catToSearch == app_categories[j].category) {
                        categoryIndex = j;
                        break; //Don't run through everything once we get a match
                    }
                }//End of search loop

                if (catToSearch != app_categories[categoryIndex].category) {
                    cout << "Category " << catToSearch << " not found." << '\n';
                    break;
                }
                if (app_categories[categoryIndex].root == nullptr ||
                    printInRange(app_categories[categoryIndex].root, high, low, false) == false)
                    cout << "No applications found in " << catToSearch << " for the given range " << low << " " << high
                         << "\n\n";
                else {
                    cout << "Applications in Price Range (" << low << ", " << high << ") in Category: " << catToSearch
                         << "\n";
                    printInRange(app_categories[categoryIndex].root, high, low);

                }
            }

        }
        else
            cout << "";

    }

    //Must destroy the BST
    for (int i = 0; i < numCategories; i ++) {
        deleteBST(app_categories[i].root);
    }

    //destroy the initial array as well
    free(app_categories);

    return 0;
}//End of main
