
#include "ChordDHT.h"
#include <iostream>

ChordDHT::ChordDHT(){
    bitsForHash= 8;

}

ChordDHT::ChordDHT(int bitsForHash){
    this->bitsForHash= bitsForHash;
}


Node* ChordDHT::findNode(int nodeId){

    int n= nodesInChord.size();

    for (Node* node : nodesInChord)
    {
        if(node->getId()==nodeId){
            return node;
        }
    } 

    return NULL;
}

void ChordDHT::addNewNodeToChord(int nodeId, int refNodeId){
    
    Node* node= findNode(nodeId);
    if(node == NULL){
        node= (new Node(nodeId, bitsForHash));
    }
    else{
        cout << "Node with ID " << nodeId << " Already exists in the Chord" << endl << endl;
        return;
    }

    int n= nodesInChord.size();
    if(n>0)
    {   
        Node* refNode= findNode(refNodeId);
        if(refNode == NULL){
            cout << "Node with ID " << refNodeId << " Does not exists in the Chord. Cannot use it as the refernce node." << endl;
            return;
        }
        node->join(refNode);
    }
    else
        node->join(NULL);
    
    nodesInChord.insert(node);
    cout << "Node with ID " << nodeId << " successfully added to the Chord" << endl;
}

void ChordDHT::leaveNodeFromChord(int nodeId){
    Node* node= findNode(nodeId);
    
    if(node == NULL)
    {
        cout << "Node with ID " << nodeId << " does not exist in the Chord" << endl;
        return;
    }

    node->leave();
    nodesInChord.erase(node);

    cout << "Node with ID " << nodeId << " successfully removed from the Chord" << endl;
}

void ChordDHT::addKeyValueToChord(int key, int value){
    if(keysInChord.find(key)!=keysInChord.end())
    {
        cout << "Given key " << key << " already exists in the Chord." << endl;
        return;
    }
    
    int n= nodesInChord.size();
    if(n==0){
        cout << "Please insert atleast 1 node in Chord before executing this function" << endl;
        return;
    }

    keysInChord.insert(key);

    Node* start_node = *(nodesInChord.begin());
    (start_node)->insert(key, value);

}

void ChordDHT::removeKeyFromChord(int key){
    if(keysInChord.find(key)==keysInChord.end())
    {
        cout << "Given key " << key << " does not exist in the Chord." << endl;
        return;
    }
    
    int n= nodesInChord.size();
    if(n==0){
        cout << "Please insert atleast 1 node in Chord before executing this function" << endl;
        return;
    }

    keysInChord.erase(key);
    
    Node* start_node = *(nodesInChord.begin());
    (start_node)->remove(key);
}

int ChordDHT::lookupKeyValueFromChord(int key){
    if(keysInChord.find(key)==keysInChord.end())
    {
        cout << "Given Key " << key << " does not exist in the chord." << endl;
        return -1;
    }
    
    int n= nodesInChord.size();
    if(n==0){
        cout << "Please insert atleast 1 node in Chord before executing this function" << endl;
        return -1;
    }

    Node* start_node = *(nodesInChord.begin());
    int value= (start_node)->find(key);

    return value;
}

void ChordDHT::printLocalKeysOfAllNodes(){

    for (Node* node : nodesInChord)
    {
        node->printLocalKeys();
    }
    
}

void ChordDHT::printFingerTableOfAllNodes(){
    int n= nodesInChord.size();

    if(n==0){
        cout << "There is no node in the Chord." << endl;
        return;
    }

    for (Node* node : nodesInChord)
    {
        node->printNodeFingerTable();
    }
}

void ChordDHT::printLookUpResultForAllKeysOnNode(int nodeId){
    
    Node* node= findNode(nodeId);
    
    if(node == NULL)
    {
        cout << "Node with ID " << nodeId << " does not exist in the Chord" << endl;
        return;
    }

    cout << "----------" << "Node Id: " << nodeId << "----------" << endl << endl;
    for (int key : keysInChord)
    {
        node->find(key);
    }
    cout << "-------------------------------------" << endl << endl;
}