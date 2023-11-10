// I have implemented first 4 parts of the Grading rubrics, including optional Node::leave() implementation.

Compile and run:

    1. To compile the code, run command:
    g++ Run.cpp ChordDHT.cpp Utility_func.cpp Node.cpp FingerTable.cpp --std=c++11

    2. To run the code, run command:
    ./a.out

Operations Available:

    1. add node to the chord. 
        - First Type "AN"
        - Then input Node id of the node to be added. 
        - Then input Node id of the reference node.
    2. remove node from the chord.
        - First Type "LN" to 
        - Then input Node id of the node to be added.
    3. insert key/value to the chord.
        - First Type "AK"
        - Then input key to be added to the chord
        - Then select (YES or NO) if you want to add value for the key
        - Then input value to be added to the chord
    4. Remove a key from a node in the chord.
        - First Type "RK"
        - Then input key to be removed to the chord
    5. Type "LK" to search for key and its value in the chord.
        - First Type "LK"
        - Then input key you want to lookup in the chord
    6. Print stored keys for all nodes in the chord.
        - Type "PSK"
    7. Print finger table for all nodes in the chord.
        - Type "PFT"
    8. Print all key lookup for a node.
        - Type "PKL_NODE"
    9. Type "EXIT" to exit the chord.
        - Type "EXIT"


Code details:
    Main.cpp: 
    - File that runs the chord. 
    - Has int main() function, from where the code starts. 
    - Takes input for various operations a user can perform, and calls appropriate functions of ChordDHT class.

    ChordDHT.h/ChordDHT.cpp
    - Class that defines general functions for Chord. 
    - Uses Node class as its child

    Node.h/Node.cpp
    - Class that defines node of the Chord. 
    - Uses FingerTable class as its child.

    FingerTable.h/FingerTable.cpp
    - Class that defines finger Table for a Node. 
    - Uses Utility_func class to carry out general common operations.

    Utility_func.h/Utility_func.cpp
    - Class that defines general used utility functions.
