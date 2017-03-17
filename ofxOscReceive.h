#include "ofxOsc.h"
//ofApp.h에 ofxOsc.h include필요없음.


//쓰는법 :
//1. global variable에 벡터 선언
//2. receive의 첫번째 arg에 주소들 { } 로 넣어주고, 두번째에 그 벡터를 넣어주면 그냥 끝.
//3. 벡터는 class안에서 알아서 address의 사이즈로 resize되므로 initialize나 resize필요없음.

//example :
// ofApp.h에
// #include "class_oscReceiver.h"
// vector<float> test;

// draw또는 update에 :
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

