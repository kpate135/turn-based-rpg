#include <iostream>
#include <string>
#include "ReadStringFromCSV.hpp"

using namespace std;

int main() {
    cout << "Creating SceneDataBase object" << endl;
    SceneDataBase testscene_database("test.csv");

    //print db to check
    for (int i = 0; i < testscene_database.db.size(); ++i) {
        cout << "Row " << i << ": ";
        for (int j = 0; j < testscene_database.db.at(i).size(); ++j) {
            cout << testscene_database.db.at(i).at(j);
        }
        cout << endl;
    }

}   
