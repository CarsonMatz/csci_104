#include "stones.h"
#include "max_heap.h"

int lastStoneWeight(std::vector<int>& stones) {
    MaxHeap<int> heap;
    
    // TO BE COMPLETED
    for(std::vector<int>::iterator it = stones.begin(); it != stones.end(); ++it){
    	heap.push(*it);
    }
    size_t size = heap.size();


    while(size > 1){
    	size_t s1 = heap.top();
    	heap.pop();
    	size_t s2 = heap.top();
    	heap.pop();


    	if(s1 != s2){
    		size_t weight = s1 - s2;
    		heap.push(weight);
    	}
    	size = heap.size();
    }

    if(heap.size() == 0){
    	return 0;
    }
    else{
    	return heap.top();
    }
}
