//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void printHeap(int weightArr[]) { //helper function to track down/upheap
        cout << "Heap weights: ";
        for (int i = 0; i < size; ++i) {
            cout << weightArr[data[i]] << " ";
        }
        cout << endl;
    }


    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;//place new element index at end of heap
        upheap(size, weightArr);//move element up if possible
        size++;//increase heap
        printHeap(weightArr);//helper function

    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) return -1;
        int root = data[0];
        size--;
        if (size > 0){
            data[0] = data[size];
        }
        return root;
        // return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
            // TODO: swap child upward while smaller than parent
            while (pos > 0) {// do stuff until pos==0
                int parent = (pos - 1) / 2;//finds parent node depending on index

                if (weightArr[data[pos]] < weightArr[data[parent]]) { //if child weight is less than parent
                    int temp = data[pos];//temp variable to hold child index
                    data[pos] = data[parent];// child index is swaped with parent
                    data[parent] = temp;//parent index is now old child index
                    pos = parent;//
                } else {
                    break;
                }

            }
        }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

    }
};

#endif