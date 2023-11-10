#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include "FingerTable.h"
using namespace std;

//forward declaration

class Node {
public:

	Node(int nodeId);
    Node(int nodeId, int bitsForHash);

    Node* findSuccessor(int key, vector<Node*>& path);
    Node* findPredecessor(int key, vector<Node*>& path);
    Node* closestPrecedingFinger(int key);

	void join(Node* node);
    void updateOwnFingerTable(Node* node);
    void updateOthersFingerTableJoinOP();
    void updateFingerTableJoinOP(Node* node, int index);
    void migrateKeysOnJoin();

    void leave();
    void updateOthersFingerTableLeaveOP();
    void updateFingerTableLeaveOP(Node* node);
    void migrateKeysOnLeave();
    
	//TODO: implement DHT lookup
	int find(int key);
	//TODO: implement DHT key insertion
	void insert(int key, int value);
	//TODO: implement DHT key deletion
	void remove(int key);

    //setters and getters
    int getId();
    void setId(int key);

    int getHashId();
    void setHashId(int key);
	
    Node* getPredecessor();
    void setPredecessor(Node* node);

    Node* getSuccessor();
    
    FingerTable getFingerTable();
    void setFingerTable(FingerTable fingerTable );

    std::map<int, int> getLocalKeys();
    void setLocalKeys(std::map<int, int> localKeys);

    //print functions
    void printLocalKeys();
    void printNodeFingerTable();
    void print_path(vector<Node*>& path);

public:
    int M;
    FingerTable fingerTable_;
    std::map<int, int> localKeys_;

private:
	int id_;
    int hash_id;

    Node* predecessor;
};

#endif