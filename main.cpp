//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    MinHeap heap;
    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }
    int nextEmptyIdx = nextFree;//tracker of the next free array slot

    while (heap.size > 1) {
       int smallNode1 = heap.pop(weightArr);//pop 2 of the smallest nodes
        int smallNode2 = heap.pop(weightArr);
        int parent = nextEmptyIdx++;//advance to next free slot

        weightArr[parent] = weightArr[smallNode1] + weightArr[smallNode2];//combine weights and add to parent weight
        leftArr[parent] = smallNode1;
        rightArr[parent] = smallNode2;

        heap.push(parent, weightArr);//push back to array
    }

    //print everything up to next empty
    printf("weights\n");
    for (int i = 0; i < nextEmptyIdx; i++) {
        printf("%d ", weightArr[i]);
    }
    printf("\n");

    int root = heap.pop(weightArr);//remove last node
    return root;//return it
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    return -1; // placeholder
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    stack<pair<int, string>> codeStack;
    codeStack.push({root, ""});//push root into the codestack

    while (!codeStack.empty()) { //while not empty go through all nodes
        auto [node, path] = codeStack.top();//get top pair
        codeStack.pop();//remove from stack
        //get index of lef/right
        int left = leftArr[node];
        int right = rightArr[node];

        if (left == -1 && right == -1) {//if left/right has no child assign code
            char ch = charArr[node];//get character
            codes[ch - 'a'] = path.empty() ? "0" : path;// store code
        }
        else {
            if (right != -1)//if there is a child, push right child with path + 1
                codeStack.push({right, path + '1'});
            if ( left != -1)//if there is a child, push left child with path + 0
                codeStack.push({left, path + '0'});
        }


    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }


    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}