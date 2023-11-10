#include "Node.h"
#include <math.h>
#include "Utility_func.h"
#include <iostream>
#include "FingerTable.h"

Node::Node(int nodeId) {
    M= 8;
    id_= nodeId;
    hash_id= nodeId % int(pow(2,M));
    fingerTable_= FingerTable(this);
    predecessor= NULL;
}

Node::Node(int nodeId, int bitsForHash){
    M= bitsForHash;
    id_= nodeId;
    hash_id= nodeId % int(pow(2,M));
    fingerTable_= FingerTable(this, bitsForHash);
    predecessor= NULL;
}

Node* Node::findSuccessor(int key, vector<Node*>& path){
    if(getHashId() == key){
        path.push_back(this);
        return this;
    }
    else{
        Node* precedingNode= findPredecessor(key, path);
        path.push_back(precedingNode->getSuccessor());
        return precedingNode->getSuccessor();
    }
    
}
Node* Node::findPredecessor(int key, vector<Node*>& path){
    Node* possiblePredecessor= this;
    path.push_back(possiblePredecessor);
    
    while(keyBetweenNodesBothIncluded(key, possiblePredecessor->getHashId(), possiblePredecessor->getSuccessor()->getHashId() )==false){
        possiblePredecessor= possiblePredecessor->closestPrecedingFinger(key);
        path.push_back(possiblePredecessor);
    }

    return possiblePredecessor;
}
Node* Node::closestPrecedingFinger(int key){
    for(int i= M; i>=1; i--){
        if( (getFingerTable().getNextNode(i)->getHashId() != this->getHashId()) && keyBetweenNodesBothIncluded(getFingerTable().getNextNode(i)->getHashId(), getHashId(), key)){
            return getFingerTable().getNextNode(i);
        }
    }

    return this;
}


//TODO: implement node join function
void Node::join(Node* node){        
    if (node == NULL){
        setPredecessor(this);
    }
    else{
        vector<Node*> path;
        Node* successor = node->findSuccessor(this->getFingerTable().getIntervalStart(1), path);
    
        fingerTable_.setNextNode(1, successor);
        setPredecessor(successor->getPredecessor());
        successor->setPredecessor(this);

        updateOwnFingerTable(node);
        updateOthersFingerTableJoinOP();
        migrateKeysOnJoin();
    }
}
void Node::updateOwnFingerTable(Node* node){

    for(int i=2; i<=M; i++){
        int interval_start= this->getFingerTable().getIntervalStart(i);
        
        vector<Node*> path;
        Node* successorForIntervalStart= node->findSuccessor(interval_start, path);

        (this->fingerTable_).setNextNode(i, successorForIntervalStart);
    }

}
void Node::updateOthersFingerTableJoinOP(){
    for(int i=1; i<=M; i++){
        int possibleUpdateValue= getHashId() - pow(2, i-1);
        if(possibleUpdateValue <0){
            possibleUpdateValue=   pow(2, M) - possibleUpdateValue;
        }

        vector<Node*> path;
        Node* predecessorToBeUpdated= findPredecessor(possibleUpdateValue, path); 
        if(predecessorToBeUpdated != this)
            predecessorToBeUpdated->updateFingerTableJoinOP(this, i);
    }
}
void Node::updateFingerTableJoinOP(Node* node, int index){
    Node* successor_node = getFingerTable().getFinger(index).next_node;
        
    if(node != this){
        if( keyBetweenNodesIncluding1(node->getHashId(), this->hash_id, successor_node->hash_id)){
            fingerTable_.setNextNode(index, node);
            
            getPredecessor()->updateFingerTableJoinOP(node, index);
        }
    }
}
void Node::migrateKeysOnJoin(){

    Node* successorNode= getSuccessor();

    std::map<int, int> successorsKeys= successorNode->getLocalKeys();
    std::map<int, int>::iterator it;
    
    if(successorNode!=this){
        cout << "-------------------Key Migration---------------------" << endl;

        for (it=successorsKeys.begin(); it!=successorsKeys.end(); ++it){

            if(it->first <= getHashId()){
                this->localKeys_[it->first]= it->second;
                cout << "Migrate key " << it->first << " from node " << successorNode->getId() << " to node " << this->getId() << endl;
            }
        }

        for (it=successorsKeys.begin(); it!=successorsKeys.end(); ++it){

            if(it->first <= getHashId()){
                successorNode->localKeys_.erase(it->first);
            }
        }

        cout << "----------------------------------------" << endl;
    }
    
}


//TODO: implement node leave function
void Node::leave(){

    Node* successor_node = getFingerTable().getNextNode(1);
    Node* predecessor_node = getPredecessor();
    successor_node->setPredecessor(predecessor_node);

    updateOthersFingerTableLeaveOP();
    migrateKeysOnLeave();
    
}
void Node::updateOthersFingerTableLeaveOP(){
    Node* successor_node = getFingerTable().getNextNode(1);

    Node* next_successor_node;

    while(successor_node->getId()!=getId()){
        next_successor_node = successor_node->getFingerTable().getNextNode(1);
        successor_node->updateFingerTableLeaveOP(this);
        successor_node = next_successor_node;
    }
}
void Node::updateFingerTableLeaveOP(Node* node){
    
    for(int i=1; i<=M ;i++){

        if(fingerTable_.getNextNode(i) == node)
        {
            fingerTable_.setNextNode(i, node->getSuccessor());
        }
    }
    
}
void Node::migrateKeysOnLeave(){

    Node* successorNode= getSuccessor();

    std::map<int, int> localKeys= this->getLocalKeys();
    std::map<int, int>::iterator it;

    if(successorNode!=this)
    {
        cout << "----------------------Key Migration------------------" << endl;
        for (it=localKeys.begin(); it!=localKeys.end(); ++it){

            cout << "Migrate key " << it->first << " from node " << this->getId() << " to node " << successorNode->getId() << endl;
            successorNode->localKeys_[it->first]= it->second;
            
        }
        cout << "----------------------------------------" << endl;
    }

}


//TODO: implement DHT lookup
int Node::find(int key){

    vector<Node*> path;
    Node* node_with_key = findSuccessor(key, path);

    int value;

    if (node_with_key->getLocalKeys().find(key) == node_with_key->getLocalKeys().end()){
        value= -1;
        cout << "Given Key " << key << " does not exist in the chord." << endl;
    }
    else{
        value= node_with_key->getLocalKeys()[key];
        cout << "Loopkup result of key " << key << " from node " << getId() << " with path ";
        print_path(path);

        if(value!=-1)
            cout << "value is " << value << endl;
        else
            cout << "value is " << "None" << endl;
    }

    
    return value;
    
}

//TODO: implement DHT key insertion
void Node::insert(int key, int value){
    
    vector<Node*> path;
    Node* node_with_key = findSuccessor(key, path);
    
    node_with_key->localKeys_[key]= value;
    
    if(value!=-1)
        cout << "Key " << key << " with value " << value << " successfully added to the Chord in the node " << node_with_key->getId() << endl;
    else
        cout << "Key " << key << " with None value, successfully added to the Chord in the node " << node_with_key->getId() << endl;
}

//TODO: implement DHT key deletion
void Node::remove(int key){

    vector<Node*> path;
    Node* node_with_key = findSuccessor(key, path);
        
    if(node_with_key->getLocalKeys().find(key) != node_with_key->getLocalKeys().end())
    {
        node_with_key->localKeys_.erase(key);
        cout << "Key " << key << " successfully removed from the node " << node_with_key->getId() << endl;
    }

}

//setters and getters
int Node::getId(){
    return id_;
}
void Node::setId(int key){
    id_= key;
}

int Node::getHashId(){
    return hash_id;
}
void Node::setHashId(int hash){
    hash_id= hash;
}

Node* Node::getPredecessor(){
    return predecessor;
}
void Node::setPredecessor(Node* node){
    predecessor= node;
}

Node* Node::getSuccessor(){
    return getFingerTable().getNextNode(1);
}

FingerTable Node::getFingerTable(){
    return fingerTable_;
}
void Node::setFingerTable(FingerTable fingerTable ){
    fingerTable_= fingerTable;
}

std::map<int, int> Node::getLocalKeys(){
    return localKeys_;
}
void Node::setLocalKeys(std::map<int, int> localKeys){
    localKeys_= localKeys;
}


//print functions
void Node::printLocalKeys(){
    cout << "----------" << "Node Id: " << getId() << "----------" << endl << endl;
    
    string local_key_value_string="{";

    std::map<int, int> localKeys= getLocalKeys();

    std::map<int, int>::iterator it;
    for (it=localKeys.begin(); it!=localKeys.end(); ++it){
        if(it->second == -1){
            local_key_value_string= local_key_value_string + to_string(it->first) + ": " + "None" + ", ";
        }
        else
            local_key_value_string= local_key_value_string + to_string(it->first) + ": " + to_string(it->second) + ", ";
    }
    
    local_key_value_string= local_key_value_string + "}";
    cout << local_key_value_string << endl;
}

void Node::printNodeFingerTable(){
    cout << "----------" << "Node Id: " << getId() << "----------" << endl << endl;

    cout << "Successor: " << getSuccessor()->getId() << "     " << "Predecessor: " << getPredecessor()->getId() << endl;
    cout << "FingerTables:" << endl;

    fingerTable_.prettyPrint();

    cout << "-------------------------------------" << endl << endl;
}

void Node::print_path(vector<Node*>& path){

    int n=path.size();
    if(path[0]->getId() == path[n-1]->getId()){
        cout << "[" << to_string(path[0]->getId()) << "]" << endl;
    }
    else{
        cout << "[" << to_string(path[0]->getId()) << ", " << to_string(path[n-1]->getId()) << "]" << endl;
    }

}