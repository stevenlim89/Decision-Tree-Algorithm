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
#include <iomanip>

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
    if(featureUsed(0) && featureUsed(1) && featureUsed(2) && featureUsed(3)){
        return NULL;
    }

    double temp = 0;
    double minEntropy = -1;

    int labelOneCount = 0, labelTwoCount = 0, labelThreeCount = 0;

    vector< vector<double> > leftVectors;
    vector< vector<double> > rightVectors;

    //cout << "data size:" <<dataPointsVectors.size() << endl;

    Node *n = new Node(dataPointsVectors, nodeCount++);
    //cout<<"Node created"<<endl;
    if(n->isPure()){
        n->label = dataPointsVectors[0][4];
        return n;
    }

    for(int i = 0; i < 4; i++){
        if(featureUsed(i)){
            continue;
        }
        for(double j = 0.1; j < 7.8; j += 0.1){
            temp = n->calcEntropy(i, j);
           // cout << "temp:" << temp << endl;
            if(minEntropy == -1){
                n->split = j;
                n->feature = i;
                //cout<<"first split: "<<n->split<<endl;
                minEntropy = temp;
            }
            else if(temp < minEntropy){
                minEntropy = temp;
                n->feature = i;
                n->split = j;
                 //cout<<"Split: "<<n->split<<endl;
            }
            //cout << minEntropy << endl;
        }

    }

    setFeatureUsed(n->feature);

    for(int i = 0; i < dataPointsVectors.size(); i++){
        if(dataPointsVectors[i][n->feature] <= n->split){
            leftVectors.push_back(dataPointsVectors[i]);
            //cout<<"Does it go in here"<<endl;
        }
        else{
            rightVectors.push_back(dataPointsVectors[i]);
        }
    }
    //cout<<"Child nodes "<<rightVectors[0][0]<<endl;
    n->leftNode = createNode(leftVectors);
    n->rightNode = createNode(rightVectors);

    if(n->leftNode != NULL)
        n->leftNode->parentNode = n;
    if(n->rightNode != NULL)
        n->rightNode->parentNode = n;

    // if leaf node, set label 
    if(n->leftNode == NULL && n->rightNode == NULL){
        for(int i = 0; i < dataPointsVectors.size(); i++){
            if(dataPointsVectors[i][4] == 1){
                labelOneCount++;
            }
            else if(dataPointsVectors[i][4] == 2){
                labelTwoCount++;
            }
            else if(dataPointsVectors[i][4] == 3){
                labelThreeCount++;
            }
        }


        // Trying to find majority label
        int max = 0;
        int temp = 0;
        for(int i = 0; i < 3; i++){
            if(i == 0 && labelOneCount > max){
                max = labelOneCount;
                temp = i;
            }
            if(i == 1 && labelTwoCount > max){
                max = labelTwoCount;
                temp = i;
            }
            if(i == 2 && labelThreeCount > max){
                max = labelThreeCount;
                temp = i;
            }
        }
        n->label = temp;
    }

    return n;
}
void postorder(Node* p, int indent)
{
    if(p != NULL) {
        if(p->rightNode) {
            postorder(p->rightNode, indent+4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (p->rightNode) cout<<" /\n" << setw(indent) << ' ';
            cout<< p->number << "\n ";
        if(p->leftNode) {
            cout << setw(indent) << ' ' <<" \\\n";
            postorder(p->leftNode, indent+4);
        }
    }
}
int main() {
    string trainingFile = "hw3train.txt";
    string testFile = "hw3test.txt";

    vector< vector<double> > trainingMatrix = fileToMatrix(trainingFile);
    vector< vector<double> > testMatrix = fileToMatrix(testFile);

    Node *root = createNode(trainingMatrix);

    postorder(root, 1);

   
    return 0;
}