//
//  heap.h
//  project2
//  Analysis of Algorithms Project 2
//  Heapsort Analysis
//  Hasan H. Eroğlu
//  150150058
//  Created by Hasan Hüsamettin Eroğlu on 01/11/2018.
//  Copyright © 2018 Hasan Hüsamettin Eroğlu. All rights reserved.
//
#include <iostream>

#ifndef heap_h
#define heap_h

template <class T>
class Heap{
    
public:
    T * heap;
    int heapSize;
    
    Heap(){
        heapSize = 1;
        heap = new T[heapSize]();
    }
    Heap(int _heapSize){
        heapSize = _heapSize;
        heap = new T[heapSize]();
    }
    ~Heap(){
        delete [] heap;
    }
    void FillHeap(int _index, T _element){
        
        if(_index >= heapSize || _index < 0){
            std::cout<<"Fill index out of range."<<std::endl;
            return;
        }
        
        heap[_index] = _element;
    }
    void MaxHeapify(int _numbers[], int _index){
        
        if(_index > heapSize || _index < 0)
            return;
    
        int current = _numbers[_index];
        int leftChild = -1;
        int rightChild = -1;
        bool leftChildExists = GetLeftChild(_numbers, _index, leftChild);
        bool rightChildExists = GetRightChild(_numbers, _index, rightChild);
        int nextHeapifyIndex = -1;
        
        if(current >= leftChild && current >= rightChild)
            return;
        
        if(leftChildExists && (leftChild >= rightChild))
            nextHeapifyIndex = SwapWithLeftChild(_numbers, _index);
        
        else if(rightChildExists && (rightChild > leftChild))
            nextHeapifyIndex = SwapWithRightChild(_numbers, _index);
        
        MaxHeapify(_numbers, nextHeapifyIndex);
    }
    void MinHeapify(int _numbers[], int _index){
        
        if(_index >= heapSize || _index < 0)
            return;
        
        int current = _numbers[_index];
        int leftChild = -1;
        int rightChild = -1;
        bool leftChildExists = GetLeftChild(_numbers, _index, leftChild);
        bool rightChildExists = GetRightChild(_numbers, _index, rightChild);
        int nextHeapifyIndex = -1;
        
        if(current >= leftChild && current >= rightChild)
            return;
        
        if( leftChildExists && (leftChild <= rightChild))
            nextHeapifyIndex = SwapWithLeftChild(_numbers, _index);
        
        else if( rightChildExists && (rightChild < leftChild))
            nextHeapifyIndex = SwapWithRightChild(_numbers, _index);
        
        MinHeapify(_numbers, nextHeapifyIndex);
    }
    void BuildMaxHeap(int _numbers[]){
        int startIndex = (heapSize - 1)/2;
        
        for(int i = startIndex; i >= 0; i--)
            MaxHeapify(_numbers, i);
    }
    void BuildMinHeap(int _numbers[]){
        int startIndex = (heapSize - 1)/2;
        
        for(int i = startIndex; i >= 0; i--)
            MinHeapify(_numbers, i);
    }
    void HeapSort(int _numbers[]){
        int startIndex = heapSize - 1;
        int tempHeapSize = heapSize;
        
        BuildMaxHeap(_numbers);
        
        for(int i = startIndex; i >= 1; i--){
            Swap(_numbers[0], _numbers[heapSize - 1]);
            Swap(heap[0], heap[heapSize - 1]);
            heapSize--;
            MaxHeapify(_numbers, 0);
        }
        
        heapSize = tempHeapSize;
    }
    void IncreaseKey(int _numbers[], int _index, int _newNumber, T _newElement){
        
        if(_index <= 0 || _index > heapSize)
            return;
        
        int parentIndex = GetParentIndex(_index);
        
        if(parentIndex <= 0 || parentIndex > heapSize)
            return;
        
        heap[_index] += _newElement;
        
        _numbers[_index]  += _newNumber;
        
        while(_index > 0 && _numbers[_index] > _numbers[parentIndex]){
            
            Swap(heap[_index], heap[parentIndex]);
            Swap(_numbers[_index], _numbers[parentIndex]);
            
            _index = parentIndex;
            parentIndex = GetParentIndex(parentIndex);
        }
    }
    int Insert(int *& _numbers, int _newNumber, T _newElement, int _heapSize){
        
        int oldHeapSize = _heapSize;
        _heapSize++;
        heapSize = oldHeapSize + 1;
        
        IncreaseArrayMemory(_numbers, oldHeapSize, heapSize);
        IncreaseArrayMemory(heap, oldHeapSize, heapSize);
        
        _numbers[heapSize - 1] = 0;
        heap[heapSize - 1] = T();
        IncreaseKey(_numbers, heapSize - 1, _newNumber, _newElement);
        
        return _heapSize;
    }
    int ExtractMax(int numbers[]){
        int max = numbers[0];
        
        numbers[0] = numbers[heapSize - 1];
        heapSize--;
        
        MaxHeapify(numbers, 0);
        
        return max;
    }
    int ExtractMin(int numbers[]){
        int min = numbers[0];
        
        numbers[0] = numbers[heapSize - 1];
        heapSize--;
        
        MinHeapify(numbers, 0);
        
        return min;
    }
    template <class S>
    void Swap(S &elementA, S &elementB){
        S tempElement = elementA;
        elementA = elementB;
        elementB = tempElement;
    }
    template <class S>
    void IncreaseArrayMemory(S *& _array, int _oldSize, int _newSize){
        S * increasedArray = new S[_newSize]();
        
        for(int i=0; i < _newSize; i++){
            increasedArray[i] = _array[i];
        }
        
        delete [] _array;
        
        _array = increasedArray;
    }
    template <class S>
    void DecreaseArrayMemory(S *& _array, int _oldSize, int _newSize){
        S * increasedArray = new S[_newSize]();
        
        for(int i=0; i < _oldSize; i++){
            increasedArray[i] = _array[i+1];
        }
        
        delete [] _array;
        
        _array = increasedArray;
    }
    int SwapWithLeftChild(int *& _numbers, int _index){
        int leftChildIndex = GetLeftChildIndex(_index);
        Swap(_numbers[_index], _numbers[leftChildIndex]);
        Swap(heap[_index], heap[leftChildIndex]);
        return leftChildIndex;
    }
    int SwapWithRightChild(int *& _numbers, int _index){
        int rightChildIndex = GetRightChildIndex(_index);
        Swap(_numbers[_index], _numbers[rightChildIndex]);
        Swap(heap[_index], heap[rightChildIndex]);
        return rightChildIndex;
    }
    int GetParentIndex(int _index){
        if(_index != 0){
            if(_index % 2 == 0)
                return (_index / 2) - 1;
            else
                return (_index / 2);
        }
        else
            return -1;
    }
    int GetLeftChildIndex(int _index){
        return (2 * _index) + 1;
    }
    int GetRightChildIndex(int _index){
        return 2 * (_index + 1);
    } 
    bool GetLeftChild(int _numbers[], int _index, int &_leftChild){
        int leftChildIndex = GetLeftChildIndex(_index);
        
        if(leftChildIndex < heapSize && leftChildIndex > 0){
            _leftChild = _numbers[leftChildIndex];
            return true;
        }
        else
            return false;
    }
    bool GetRightChild(int _numbers[], int _index, int &_rightChild){
        int rightChildIndex = GetRightChildIndex(_index);
        
        if(rightChildIndex < heapSize && rightChildIndex > 0){
            _rightChild = _numbers[rightChildIndex];
            return true;
        }
        else
            return false;
    }
    
};






#endif /* heap_h */
