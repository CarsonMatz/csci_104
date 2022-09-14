#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MaxHeap {
private:
    std::vector<T> data;
public:
    void push(const T& item);
    // Removes the largest element in the heap
    void pop();
    // Returns the largest element in the heap (but does not remove it)
    T const& top() const;
    std::size_t size() const;
};

template <typename T>
void MaxHeap<T>::push(const T& item) {
    data.push_back(item);
    std::size_t index = data.size() - 1;
    while (index != 0) {
        std::size_t parent_index = (index - 1) / 2;
        T& current = data[index];
        T& parent = data[parent_index];
        if (current <= parent) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }
}

template <typename T>
void MaxHeap<T>::pop() {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }

    // TO BE COMPLETETED
    std::size_t index = data.size() - 1;
    std::swap(data[0], data[index]);
    data.pop_back();
    if(index>0){
        --index;
        std::size_t p = 0;
        while((2*p+2) <= index){
            std::size_t left = 2*p+1;
            std::size_t right = 2*p+2;
            if(data[left] >= data[right] && data[left] > data[p]){
                std::swap(data[p], data[left]);
                p=left;
            }
            else if(data[right] > data[left] && data[right] > data[p]){
                std::swap(data[p], data[right]);
                p=right;
            }
            else{
                break;
            }
        }
        if((2*p+1) <= index && data[2*p+1] > data[p]){
            std::swap(data[p], data[2*p+1]);
        }
    }
}

template <typename T>
T const& MaxHeap<T>::top() const {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    return data[0];
}

template <typename T>
std::size_t MaxHeap<T>::size() const {
    return data.size();
}
