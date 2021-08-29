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
            cout << testscene_database.db.at(i).at(j) << " ";
        }
        cout << endl;
    }

    cout << endl;

    //test getSceneNoData
    cout << "Calling getSceneNoData(0)" << endl;
    vector<string> scene_0_row_test = testscene_database.getSceneNoData(0);

    for (int i = 0; i < scene_0_row_test.size(); ++i) {
        cout << scene_0_row_test.at(i) << " ";
    }
    cout << endl;

    cout << "Calling getSceneNoData(1)" << endl;
    vector<string> scene_1_row_test = testscene_database.getSceneNoData(1);

    for (int i = 0; i < scene_1_row_test.size(); ++i) {
        cout << scene_1_row_test.at(i) << " ";
    }
    cout << endl;

    cout << endl;

    //testing get methods
    cout << "Calling getSceneDialgoue on scene 0" << endl;
    cout << "Scene 0 Dialogue: " << testscene_database.getSceneDialogue(0) << endl;
    cout << endl;

    cout << "Calling getSceneChoices on scene 1" << endl;
    vector<string> sceneChoices = testscene_database.getSceneChoices(1);
    cout << "Scene 1 Choices: "; 
    for (int i = 0; i < sceneChoices.size(); ++i) {
        cout << sceneChoices.at(i) << ", ";
    }
    cout << endl;
    cout << endl;

    cout << "Calling getSceneChoices_Result on scene 0" << endl;
    vector<int> sceneChoices_Result = testscene_database.getSceneChoices_Result(0);
    cout << "Scene 0 Choice_Result: ";
    for (int i = 0; i < sceneChoices_Result.size(); ++i) {
        cout << sceneChoices_Result.at(i) << ", ";
    }
    cout << endl;
    cout << endl;

    cout << "Calling getSceneType_Scene on scene 1" << endl;
    cout << "Scene 1 Type_Scene: " << testscene_database.getSceneType_Scene(1) << endl;
    cout << endl;

}   
