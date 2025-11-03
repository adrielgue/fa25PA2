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
        int root = data[0];//root equals index 0
        size--;//reduce heap size
        if (size > 0){
            data[0] = data[size];//move last element to the root/top
            downheap(0, weightArr);//rearrange heap
            printHeap(weightArr);//print helper function
    }
        return root;
    }

    void upheap(int pos, int weightArr[]) {
            // TODO: swap child upward while smaller than parent
            while (pos > 0) {// do stuff till root is reached
                int parent = (pos - 1) / 2;//finds parent node

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
        while (2 * pos + 1 < size) {
            int leftChild = 2 * pos + 1;//finds left child index
            int rightChild = 2 * pos + 2;//finds right child index
            int smallest = leftChild;

            //checks if left child is within the array and if it is smaller than the leftchild
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[leftChild]]) {
                smallest = rightChild;
            }

            //if parent is smalller than left and right child stop
            if (weightArr[data[pos]] <= weightArr[data[smallest]]) {
                break;
            }

            //swap parent with smaller child
            int temp = data[pos];
            data[pos] = data[smallest];
            data[smallest] = temp;

            //move down
            pos = smallest;


        }
    }
};

#endif