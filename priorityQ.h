#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>


template <class t1, class t2>
class priorityQ
{
public:
    priorityQ(){}; //Root will be index 0
    void push_back(const t1&, const t2&);
    void pop_front();
    void increaseKey(const t1&, const t2&);
    t2 get_front_priority() const;
    t1 get_front_key() const;
    bool isEmpty() const;
private:
    struct priorityType{
        t1 key;
        t2 priority;
    };
    void bubbleUp (std::size_t);
    void bubbleDown (std::size_t);
    std::vector <priorityType> heapArray;
    std::unordered_map <t1, std::size_t> itemToPQ;
};

//Public Members
template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& value){
    priorityType temp = {key, value}; //creates a priorityType with input values
    heapArray.push_back(temp);
    itemToPQ[key] = heapArray.size() - 1;
    bubbleUp(heapArray.size() - 1); 
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front(){
    if(isEmpty()) return;
    itemToPQ[heapArray[0].key] = 0;
    heapArray[0] = heapArray[heapArray.size() - 1];
    heapArray.pop_back();
    bubbleDown(0);
}

template <class t1, class t2>
void priorityQ<t1, t2>::increaseKey(const t1& key, const t2& value){
    size_t index = itemToPQ[key];
    heapArray[index].priority += value;
    bubbleUp(index);
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const{
    return heapArray[0].priority;
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const{
    return heapArray[0].key;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const{
    return heapArray.empty();
}

//Private Members
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index){
    while (index != 0){ 
        std::size_t parentIndex = index / 2;
        if (heapArray[index].priority > heapArray[parentIndex].priority){
            std::swap(heapArray[index], heapArray[parentIndex]);
            std::swap(itemToPQ[heapArray[index].key], itemToPQ[heapArray[parentIndex].key]);
            index = parentIndex; // Move to the next parent
        }else break;
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index){
    size_t leftChild, rightChild, largestChild;
    while(true){
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        largestChild = index;

        if(leftChild < heapArray.size() && heapArray[leftChild].priority > heapArray[index].priority) {
            largestChild = leftChild;
        }
        if(rightChild < heapArray.size() && heapArray[rightChild].priority > heapArray[largestChild].priority) {
            largestChild = rightChild;
        }
        
        if(heapArray[largestChild].priority > heapArray[index].priority) {
            std::swap(heapArray[index], heapArray[largestChild]);
            std::swap(itemToPQ[heapArray[index].key], itemToPQ[heapArray[largestChild].key]);
            index = largestChild;
        } else break;
    }
        
}