#include "Node.h"
#include "ChordDHT.h"
#include <math.h>
#include "Utility_func.h"
#include <iostream>


bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int inputNumber(){
    int ans;

    string num_string;
    while(1){
        cin >> num_string;

        if(is_number(num_string)){
            ans= stoi(num_string);
            return ans;
            break;
        }
        else{
            cout << "Please enter a valid number." << endl;
        }
    }

}

int main(){

    int bitsForHash;
    bool exit=false;

    cout << "Welcome to chord Distributed Hash Table." << endl << endl;
    cout << "Please enter size of the hash for the chord" << endl;

    bitsForHash=inputNumber();

    ChordDHT chord= ChordDHT(bitsForHash);

    string operation;
    while(!exit){
        cout << endl;
        cout << "Please select operation you want to perform" << endl << endl;

        cout << "Type \"AN\" to add node to the chord." << endl;
        cout << "Type \"LN\" to remove node from the chord." << endl;
        cout << "Type \"AK\" to insert key/value to the chord." << endl;
        cout << "Type \"RK\" to remove a key from a node in the chord." << endl;
        cout << "Type \"LK\" to search for key and its value in the chord." << endl;
        cout << "Type \"PSK\" to print stored keys for all nodes in the chord.." << endl;
        cout << "Type \"PFT\" to print finger table for all nodes in the chord." << endl;
        cout << "Type \"PKL_NODE\" to print all key lookup for a node." << endl;
        cout << "Type \"EXIT\" to exit the chord." << endl;

        cout << endl;

        cin >> operation;
        if(operation.compare("AN")==0){

            int nodeId;
            int refNodeId;

            cout << "Enter node id of the node to be inserted" << endl;
            nodeId=inputNumber();
            
            if(chord.nodesInChord.size() > 0)
            {
                cout << "Enter node id of the existing node to be used as refernce" << endl;
                refNodeId=inputNumber();;
                chord.addNewNodeToChord(nodeId, refNodeId);
                
            }
            else{
                chord.addNewNodeToChord(nodeId, '\0');
            }

            
        }
        else if(operation.compare("LN")==0){
            int nodeId;

            cout << "Enter node id of the node to be removed" << endl;
            nodeId =inputNumber();;

            chord.leaveNodeFromChord(nodeId);
        }
        else if(operation.compare("AK")==0){
            int key;
            int value;
            string value_bool;

            cout << "Enter key to be added to the chord" << endl;
            key =inputNumber();;

            cout << "Do you want to store value as well? Type \"YES\" or \"NO\" " << endl;
            cin >> value_bool;

            if(value_bool.compare("YES")==0)
            {
                cout << "Enter value to be added to the chord." << endl;
                value =inputNumber();;
                chord.addKeyValueToChord(key, value);
            }
            else{
                chord.addKeyValueToChord(key, -1);
            }

            
        }
        else if(operation.compare("RK")==0){
            int key;

            cout << "Enter key to be removed from the chord." << endl;
            key =inputNumber();;

            chord.removeKeyFromChord(key);
        }
        else if(operation.compare("LK")==0){
            int key;

            cout << "Enter key you want to search for in the chord." << endl;
            key =inputNumber();;

            chord.lookupKeyValueFromChord(key);
        }
        else if(operation.compare("PSK")==0){
            chord.printLocalKeysOfAllNodes();
        }
        else if(operation.compare("PFT")==0){
            chord.printFingerTableOfAllNodes();
        }
        else if(operation.compare("PKL_NODE")==0){
            int nodeId;

            cout << "Enter node id of the node to print all key lookup for." << endl;
            nodeId =inputNumber();;

            chord.printLookUpResultForAllKeysOnNode(nodeId);
        }
        else if(operation.compare("EXIT")==0){
            exit=true;
        }
        else{
            cout << "Invalid operation entred" << endl;
        }
    }
}