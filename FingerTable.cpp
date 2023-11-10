
#include "FingerTable.h"
#include "Node.h"
#include <math.h>
#include <iostream>

FingerTable::FingerTable(){
	// According to Chord paper, the finger table starts from index=1
	fingerTable_.resize(M + 1);
}

FingerTable::FingerTable(Node* node){
	// According to Chord paper, the finger table starts from index=1
	M= 8;
	fingerTable_.resize(M + 1);

	for(int i=1; i<=M; i++){

		int interval_start= (node->getHashId() + int(pow(2,i-1)) )%int(pow(2,M));
		int interval_end= (node->getHashId() + int(pow(2,i)) )%int(pow(2,M));

		setIntervalStart(i ,  interval_start);
		setNextNode(i , node);
		setIntervalEnd(i , interval_end);
	}
	
}

FingerTable::FingerTable(Node* node, int bitsForHash){
	// According to Chord paper, the finger table starts from index=1
	
	M= bitsForHash;
	fingerTable_.resize(M + 1);
	
	for(int i=1; i<=M; i++){

		int interval_start= (node->getHashId() + int(pow(2,i-1)) )%int(pow(2,M));
		int interval_end= (node->getHashId() + int(pow(2,i)) )%int(pow(2,M));

		setIntervalStart(i ,  interval_start);
		setNextNode(i , node);
		setIntervalEnd(i , interval_end);
	}
}

void FingerTable::setFinger(int index, Finger finger){
	fingerTable_[index] = finger;
}
Finger FingerTable::getFinger(int index) {
	return fingerTable_[index];
}

void FingerTable::setIntervalStart(int index, int interval_start){
	fingerTable_[index].interval_start = interval_start;
}
int FingerTable::getIntervalStart(int index) {
	return fingerTable_[index].interval_start;
}

void FingerTable::setIntervalEnd(int index, int interval_end){
	fingerTable_[index].interval_end = interval_end;
}
int FingerTable::getIntervalEnd(int index) {
	return fingerTable_[index].interval_end;
}

void FingerTable::setNextNode(int index, Node* next_node){
	fingerTable_[index].next_node = next_node;
}
Node* FingerTable::getNextNode(int index) {
	return fingerTable_[index].next_node;
}

void FingerTable::prettyPrint(){
	for(int i=1; i<=M; i++){
		cout << " | k = " << i << " [ " << getIntervalStart(i) << " , " << getIntervalEnd(i) << " )     succ. = " << getNextNode(i)->getId() << "  |" << endl;
	}
};