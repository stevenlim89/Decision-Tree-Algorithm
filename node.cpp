#include <vector>
#include <math.h>
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
		//cout<<"beginning "<<endl;
		for(int i = 0; i < dataPointVectors.size(); i++){
		//	cout<<"in loop"<<endl;
			int labeli = dataPointVectors[i][4];
			if(label1 != labeli){
				return false;
			}
		}
		//cout<<"end of function "<<endl;
		return true;
	}

	double calcEntropy(int feature, double splitVal){

    	// <= counter 
    	int lessEqCount = 0;

    	// > counter
    	int greatCount = 0;

    	double pOne = 0;
    	double pTwo = 0;
    	double pThree = 0;

    	// Counts how many of each label fall on the split
    	int labelOneCountGr = 0, labelOneCountLt = 0;
    	int labelTwoCountGr = 0, labelTwoCountLt = 0;
    	int labelThreeCountGr = 0, labelThreeCountLt = 0;

    	// counts total number of each label
    	int countLabelOne = 0, countLabelTwo = 0, countLabelThree = 0;

    	for(int i = 0; i < dataPointVectors.size(); i++){
    		//cout<<"datapointvectors:  "<< dataPointVectors[i][feature];
    		//	cout<<"SplitVal:   "<< splitVal<<endl;
    		if(dataPointVectors[i][feature] <= splitVal){
    			if(dataPointVectors[i][4] == 1){
    		//		cout<<"Inside 1 lt"<< endl;
    				labelOneCountLt++;
    				countLabelOne++;
    			}
    			else if(dataPointVectors[i][4] == 2){
    		//		cout<<"Inside 2 lt"<< endl;
    				labelTwoCountLt++;
    				countLabelTwo++;
    			}
    			else if(dataPointVectors[i][4] == 3){
    				//cout<<"Inside 3 lt "<< endl;
    				labelThreeCountLt++;
    				countLabelThree++;
    			}

    			lessEqCount++;
    		}
    		else{
    			if(dataPointVectors[i][4] == 1){
    				//cout<<"Inside 1 gt"<< endl;
    				labelOneCountGr++;
    				countLabelOne++;
    			}
    			else if(dataPointVectors[i][4] == 2){
    				//cout<<"Inside 2 gt"<< endl;
    				labelTwoCountGr++;
    				countLabelTwo++;
    			}
    			else if(dataPointVectors[i][4] == 3){
    				//cout<<"Inside 3 gt"<< endl;
    				labelThreeCountGr++;
    				countLabelThree++;
    			}
    			greatCount++;
    		}

    	}

    	// Get probabilities and end entropies
    	double ltp = lessEqCount / dataPointVectors.size();
    	double gtp = greatCount / dataPointVectors.size();
    	if(gtp > 0)
    	cout<<"ltp:  "<<ltp<<endl;
    	if(gtp > 0)
    		cout<<"gtp:  "<<gtp<<endl;
    	//cout<<"size:  "<<dataPointVectors.size()<<endl;
		if(lessEqCount == 0){
			pOne = 0;
			pTwo = 0;
			pThree = 0;
		}
    	else{
    		pOne = labelOneCountLt/lessEqCount;
    		pTwo = labelTwoCountLt/lessEqCount;
    		pThree = labelThreeCountLt/lessEqCount;
    	}

    	if(pOne != 0){
    		pOne = pOne * log(pOne);
    	}
    	if(pTwo != 0){
    		pTwo = pTwo * log(pTwo);
    	}
    	if(pThree != 0){
    		pThree = pThree * log(pThree);
    	}
    	//cout<< "inside calcEntropy: "<< pOne << " " << pTwo <<" " << pThree <<endl;
    	double ltEntropy = -(pOne) - (pTwo) - (pThree);

    	if(greatCount == 0){
			pOne = 0;
			pTwo = 0;
			pThree = 0;
		}
		else{
			pOne = labelOneCountGr/greatCount;
    		pTwo = labelTwoCountGr/greatCount;
    		pThree = labelThreeCountGr/greatCount;
		}	

    	if(pOne != 0){
    		//cout<< "before logs 1 "<< pOne<<endl;
    		pOne = pOne * log(pOne);
    		//cout<< "logs 1 "<< pOne<<endl;
    	}
    	if(pTwo != 0){
    		//cout<< "before logs 2 "<< pTwo<<endl;
    		pTwo = pTwo * log(pTwo);
    		//cout<< "logs 2 "<< pTwo<<endl;
    	}
    	if(pThree != 0){
    		//cout<< " before logs 3 "<< pThree<<endl;
    		pThree = pThree * log(pThree);
    		//cout<< "logs 3 "<< pThree<<endl;
    	}

    	double gtEntropy = -(pOne) - (pTwo) - (pThree);

    	double value = (ltp * ltEntropy) + (gtp * gtEntropy);
    	if(ltp == 0 || gtp == 0){
    		return 1;
    	}
    	cout<< "Value "<< value << endl;//" "<<labelOneCountGr<<endl;
    	return value;
	}
};