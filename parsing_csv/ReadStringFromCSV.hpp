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
                    tempVector.push_back(word);
                }    
                this->db.push_back(tempVector);              
            }

            fin.close();
        }
        /*
        void getSceneNo(int sceneNo) { //figure out the function of this method
            this->db.at(sceneNo);
        }
        */
};

#endif
