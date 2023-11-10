#ifndef CHORDDHT_H
#define CHORDDHT_H

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include <utility> 
#include "Node.h"
using namespace std;

struct NodeCmp {
    bool operator()(Node* node1, Node* node2) const { 
        return node1->getId() < node2->getId(); 
    }
};

class ChordDHT{
public:
	
	ChordDHT();
	ChordDHT(int bitsForHash);

	void addNewNodeToChord(int nodeId, int refNodeId);

	void leaveNodeFromChord(int nodeId);

	void addKeyValueToChord(int key, int value);

	void removeKeyFromChord(int key);

	int lookupKeyValueFromChord(int key);

	void printLocalKeysOfAllNodes();

	void printFingerTableOfAllNodes();

	void printLookUpResultForAllKeysOnNode(int nodeId);

	set<Node*, NodeCmp> nodesInChord;
	int bitsForHash;

private:
	Node* findNode(int nodeId);

	
	set<int> keysInChord;
};

#endif