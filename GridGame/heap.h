#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int n;
  PComparator comp;

  void heapify(int index);
  void trickleUp(int index);
};

// Add implementation of member functions here
//constructor, initializes n and c for m-ary and comparator
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
: n(m), comp(c) 
{

}
//destructor
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("heap is empty");
  }

  //put the last element in the top spot
  data[0]=data.back();
  //delete the last element
  data.pop_back();
  //heapify the tree, starting at the 0 index where the node that needs to go down is
  if(!empty()){
    heapify(0);

  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int index){
  //if the current node has no children (leaf node), return
  if((n*index+1) >= (int)data.size()){
    return;
  }
  //start with the left-most child
  int child = n*index+1;
  //check all children to see which to swap (has highest priority)
  for(int i = 2; i <= (int)n; i++){
    int nchild = n*index+i;
    if(nchild >= (int)data.size()){
      break;
    }
    if( comp(data[nchild], data[child]) ){
      child = nchild;
    }
  }

  //if th highest priority child has priority of the parent (current node), swap them and run heapify again
  if( comp(data[child], data[index]) ){
    std::swap(data[child], data[index]);
    heapify(child);
  } 
}

//push() function
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  //add the item to the back of the list, move it up the tree to the appropriate spot using trickle up
  data.push_back(item);
  trickleUp(data.size()-1);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int index){
  //if the list is empty or there is only one item, no need to move it anywhere
  //if index = 0, then node is top of tree already so can't be moved up
  if((data.size() <= 1) || (index == 0)){
    return;
  }

  //get index of parent
  int p = (index - 1)/n;
  //if the child (current node) has higher priority than the parent, swap them and run trickleUp again
  if( comp(data[index], data[p]) ){
    std::swap(data[index], data[p]);
    trickleUp(p);
  }
}

//empty() function
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return data.empty();
}


#endif

