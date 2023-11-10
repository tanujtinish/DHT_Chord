
#include <stdint.h>
#include "Utility_func.h"

bool keyBetweenNodesBothIncluded(int key, int node1, int node2){
    if(node1 < node2){
        return key<=node2 && key>=node1;
    }
    else{
        return key<=node2 || key>=node1;
    }
}

bool keyBetweenNodesBothExcluded(int key, int node1, int node2){
    if(node1 < node2){
        return key<node2 && key>node1;
    }
    else{
        return key<node2 || key>node1;
    }
}

bool keyBetweenNodesIncluding1(int key, int node1, int node2){
    if(node1 < node2){
        return key<node2 && key>=node1;
    }
    else{
        return key<node2 || key>=node1;
    }
}

bool keyBetweenNodesBothIncluding2(int key, int node1, int node2){
    if(node1 < node2){
        return key<=node2 && key>node1;
    }
    else{
        return key<=node2 || key>node1;
    }
}