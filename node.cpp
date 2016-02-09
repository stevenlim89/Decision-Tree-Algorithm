#include <vector>
#define LABELSPOT 4
using namespace std;

class Node{
	public:
	int label;
	Node *leftNode;
	Node *rightNode;
	double split;
	int feature;
	int number;
	vector< vector<double> > dataPointVectors;

	//public: 
		Node(vector< vector<double> > v, int key){
			dataPointVectors = v;
			number = key;
			
			leftNode = NULL;
			rightNode = NULL;

			split = -1;
			label = -1;
			feature = -1;
		}

	bool isPure(){
		int label1 = dataPointVectors[0][4];
		// loop through datapointvectors
		for(int i = 0; i < dataPointVectors.size(); i++){
			int labeli = dataPointVectors[i][4];
			if(label1 != labeli){
				return false;
			}
		}
		return true;
	}

	double calcEntropy(int feature, double splitVal){
    	// <= counter 
    	int lessEqCount = 0;

    	// > counter
    	int greatCount = 0;

    	for(int i = 0; i < dataPointVectors.size(); i++){
    		if(dataPointVectors[i][feature] <= splitVal){
    			lessEqCount++;
    		}
    		else{
    			greatCount++;
    		}
    	}

    	double value = lessEqCount / dataPointVectors.size();
    	

    	return value;
	}
};