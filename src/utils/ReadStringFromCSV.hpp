#ifndef _READSTRINGFROMCSV_HPP_
#define _READSTRINGFROMCSV_HPP_

#include <string>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// int STEP = 0;

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

            for (unsigned int i=0; i < this->db.at(sceneNo+1).size(); i++) {
                std::cout << "check-" << i << ": " << this->db.at(sceneNo+1).at(i) << std::endl;
            }

            return this->db.at(sceneNo + 1);
        }

        //columns: scene_no - 0, dialogue - 1, choices - 2 & 3, choices_result - 4 & 5, type_scene 6 

        std::string getSceneDialogue(int sceneNo) {
            return this->db.at(sceneNo + 1).at(1);
        }

        std::vector<std::string> getSceneChoices(int sceneNo) {
	    std::vector<std::string> tempVector; 
	    tempVector.push_back(db.at(sceneNo + 1).at(2));
	    tempVector.push_back(db.at(sceneNo + 1).at(3));
            return tempVector;
        }

        std::vector<int> getSceneChoices_Result(int sceneNo) {
	    std::vector<int> tempVector;
	    std::string temp1 = db.at(sceneNo + 1).at(4);
	    std::string temp2 = db.at(sceneNo + 1).at(5);
        std::cout << "temp1: " << temp1 << std::endl;
        std::cout << "temp2: " << temp2 << std::endl;
        int result1 = std::stoi(temp1);
	    int result2 = std::stoi(temp1);
	    tempVector.push_back(result1);
	    tempVector.push_back(result2);            
	    return tempVector;
        }

        std::string getSceneType_Scene(int sceneNo) {
            return this->db.at(sceneNo + 1).at(6);
        }
};

#endif
