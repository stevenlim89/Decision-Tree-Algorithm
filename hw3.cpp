#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <sstream>
#include "node.cpp"

int nodeCount = 0;
bool featOne = false;
bool featTwo = false;    
bool featThree = false;
bool featFour = false;

vector< vector<double> > fileToMatrix(string filename){
    char delimiter = ' ';

    // feature vector
    vector<double> feature;

    // Matrix to hold all feature vecttors
    vector< vector<double> > featureMatrix;

    // Variable to hold char number from file
    char line[4];

    // Variable to hold number that used to be a char
    double number;

    // Counter to check when to put into featureMatrix
    int count = 0;

    ifstream trainfile; 
    trainfile.open(filename);

    //check to see if the file is opened:
    if (trainfile.is_open())
    {
        //while there are still lines in the
        //file, keep reading:
        while (! trainfile.eof() )
        {
            count++;

            // Get character from file and store in variable line
            trainfile.getline(line, 256, delimiter);

            // line is a character so convert to int
            number = atof(line);

            // add to feature vector
            feature.push_back(number);

            // If counter is 5, then feature vector has been filled and you can add it to matrix
            if(count == 5){
                featureMatrix.push_back(feature);

                // reset values
                count = 0;
                feature.clear();
            } 

        }     
    }
    trainfile.close();

    return featureMatrix;
}

bool featureUsed (int i) {
    if(featOne == true && i == 0){
        return true;
    }
    if(featTwo == true && i == 1){
        return true;
    }
    if(featThree == true && i == 2){
        return true;
    }
    if(featFour == true && i == 3){
        return true;
    }
    return false;
}

void setFeatureUsed (int i) {
    if(i == 0){
        featOne = true;
    }
    if(i == 1){
        featTwo = true;
    }
    if(i == 2){
        featThree = true;
    }
    if(i == 3){
        featFour = true;
    }
    return;
}

Node* createNode(vector< vector<double> > dataPointsVectors){
    double temp = 0;
    double minEntropy = -1;

    vector< vector<double> > leftVectors;
    vector< vector<double> > rightVectors;

    Node *n = new Node(dataPointsVectors, nodeCount++);


    if(n->isPure()){
        n->label = dataPointsVectors[0][4];
        return n;
    }

    for(int i = 0; i < 4; i++){
        if(featureUsed(i)){
            continue;
        }
        for(double j = 0; j < 8; j += 0.1){
            temp = n->calcEntropy(i, j);
            if(minEntropy == -1){
                minEntropy = temp;
            }
            else if(temp < minEntropy){
                minEntropy = temp;
                n->feature = i + 1;
                n->split = j;
            }
        }
    }

    setFeatureUsed(n->feature);

    for(int i = 0; i < dataPointsVectors.size(); i++){
        if(dataPointsVectors[i][n->feature] <= n->split){
            leftVectors.push_back(dataPointsVectors[i]);
        }
        else{
            rightVectors.push_back(dataPointsVectors[i]);
        }
    }

    n->leftNode = createNode(leftVectors);
    n->rightNode = createNode(rightVectors);

    return n;
}

int main() {
    string trainingFile = "hw3train.txt";
    string testFile = "hw3test.txt";

    vector< vector<double> > trainingMatrix = fileToMatrix(trainingFile);
    vector< vector<double> > testMatrix = fileToMatrix(testFile);
   
    return 0;
}