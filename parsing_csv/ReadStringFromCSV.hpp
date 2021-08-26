#ifndef _READSTRINGFROMCSV_HPP_
#define _READSTRINGFROMCSV_HPP_

#include <string>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int STEP = 0;

// called early on
class SceneDataBase {
    public: 

        std::vector<std::vector<std::string>> db; //public data member

        SceneDataBase(std::string fName) { //SceneDatabase constructor passing in file name.
            loadSceneDb(fName);
        }

        //parsing csv
        void loadSceneDb(std::string fileName) {
            std::fstream fin;
            fin.open(fileName); //open file
            
            std::string line, word;
            std::vector<std::string> tempVector;
            while (getline(fin, line)) { 
                std::stringstream ss(line);
                char comma_space = ',';
                tempVector.clear();
                while (getline(ss, word, comma_space)) {
                    int counter = 0;
                    if (word.find(" ") != std::string::npos && counter == 0) {
                        word = word.substr(word.find(" ") + 1, word.length() - word.find(" "));
                        ++counter;
                    }                    
                    while ((word.find("[") != std::string::npos) || (word.find("]") != std::string::npos)) {
                        if (word.find("[") != std::string::npos) {
                            word.erase(word.find("["), 1);
                        }
                        else {
                            word.erase(word.find("]"), 1);
                        }
                    }
                    tempVector.push_back(word);
                }    
                this->db.push_back(tempVector);              
            }

            fin.close();
        }

        std::vector<std::string> getSceneNoData(int sceneNo) { //returns the row (vector<string>) at the specified sceneNo
            return this->db.at(sceneNo + 1);
        }

        //columns: scene_no - 0, dialogue - 1, choices - 2 & 3, choices_result - 4 & 5, type_scene 6 

        std::string getSceneDialogue(int sceneNo) {
            return this->db.at(sceneNo + 1).at(1);
        }

        std::string getSceneChoices(int sceneNo) {
            return this->db.at(sceneNo + 1).at(2) + " " + this->db.at(sceneNo + 1).at(3);
        }

        std::string getSceneChoices_Result(int sceneNo) {
            return this->db.at(sceneNo + 1).at(4) + " " + this->db.at(sceneNo + 1).at(5);
        }

        std::string getSceneType_Scene(int sceneNo) {
            return this->db.at(sceneNo + 1).at(6);
        }
};

#endif
