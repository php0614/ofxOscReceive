#include "ofxOsc.h"

// #include "class_oscReceiver.h"
// vector<float> test;

// oscR.receive( {"/x", "/y"}, test );

class ofxOscReceive : public ofxOscReceiver{

private :
    bool printOrNot_;

public:
    ofxOscReceive(){
        printOrNot_ = false;
        this->setup(12345);
    };

    void setPrint(bool printOrNot){
        printOrNot_ = printOrNot;
    }

    template<class T>
    void receive(const vector<string>& addresses, vector<T>& TargetglobalVariables){

            TargetglobalVariables.resize(addresses.size());

            while(this->hasWaitingMessages()){
                ofxOscMessage m;

                for(int i = 0; i<addresses.size(); i++){
                this->rcvFunc(addresses[i], TargetglobalVariables[i], m);
                }
            }
    };

    void receive(const vector<string>& addresses, vector<string>& TargetglobalVariables){

            TargetglobalVariables.resize(addresses.size());

            while(this->hasWaitingMessages()){
                ofxOscMessage m;

                for(int i = 0; i<addresses.size(); i++){
                this->rcvFunc(addresses[i], TargetglobalVariables[i], m);
                }
            }
    };


    template<class T>
    void rcvFunc(string address, T &TargetglobalVariable, ofxOscMessage& m){


        this->getNextMessage(&m);

        if(m.getAddress() == address){

            bool stringOrNot = true;
            T tmp;
            const char* type = typeid(TargetglobalVariable).name();


               if(type  == typeid(float).name())
                    tmp = m.getArgAsFloat(0);
               if(type == typeid(int).name())
                    tmp = m.getArgAsInt(0);
               if(type == typeid(double).name())
                    tmp = m.getArgAsDouble(0);

              if(printOrNot_) { cout << address << " : "<< tmp << endl;}
              TargetglobalVariable = tmp;

        }
        m.clear();
    }

    void rcvFunc(string address, string &TargetglobalVariable, ofxOscMessage& m){


        this->getNextMessage(&m);

        if(m.getAddress() == address){

            bool stringOrNot = true;
            string tmp;
            const char* type = typeid(TargetglobalVariable).name();


            tmp = m.getArgAsString(0);

            if(printOrNot_) { cout << address << " : "<< tmp << endl;}
            TargetglobalVariable = tmp;

        }
        m.clear();
    }


};

