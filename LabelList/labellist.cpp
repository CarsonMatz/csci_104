#include "labellist.h"
#include <cassert>

// Complete - Do not alter
LabelList::MsgNode::MsgNode(const MsgType& msg)
    : msg_(msg)
{
    // Every message is part of the "all" (index 0) label
    labelled_.push_back(true);
    next_.push_back(nullptr);
    prev_.push_back(nullptr);
}


// Complete - Do not alter
LabelList::MsgToken::MsgToken()
 : node_(nullptr), list_(nullptr)
{
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::MsgToken(MsgNode* node, LabelList* list)
// Add any initializers here
//initialize the message token so the node and list equal the input node/list
: node_(node), list_(list)
{
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const
{
    //if the nodes are equal then true, if not then false
    if(this->node_ == rhs.node_){
        return true;
    }
    else{
        return false;
    }
}

// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::operator bool() const
{
    //if return the result of whether or not the messge token is valid
    return this->isValid();
}

// Complete - Do not alter
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->next_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::prev(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->prev_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(const LabelType& label) const
{
    size_t index = this->list_->findLabelIndex(label);
    return isLabelMember(index);
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(size_t index) const
{
    return this->isValid() && 
            index != INVALID_LABEL &&
            index < this->node_->labelled_.size() &&
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    //checks to see if the message is valid, will throw if not
    if(!this->isValid()){
        throw std::logic_error("Token refernces an invalid message");
    }
    //returns the message
    return this->node_->msg_;
}
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType& LabelList::MsgToken::msg() 
{
    //checks to see if the message is valid, will throw if not
    if(!this->isValid()){
        throw std::logic_error("Token refernces an invalid message");
    }
    //returns the message
    return this->node_->msg_;
}

// Complete - Do not alter
std::ostream& operator<<(std::ostream& ostr, const LabelList::MsgToken& token)
{
    if(token.isValid())
    {
        ostr << token.node_->msg_;
    }
    return ostr;
}

// Static constant 
const LabelList::MsgToken LabelList::end_(nullptr, nullptr);

// To be completed - must adhere to any requirements in the .h file
LabelList::LabelList() 
// Add any initializers here
{
    //add the null pointer to the back of heads, set tail equal to null, and push the "all" label into the labels vector
    heads_.push_back(nullptr);
    tail=nullptr;
    labels_.push_back("all");
}

// To be completed - must adhere to any requirements in the .h file
LabelList::~LabelList()
{
    //deconstructor just resets the vector (which is the purpose fo the clear function) at end of code
    this->clear();
    heads_.pop_back();
    labels_.pop_back();
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::clear()
{
    //scroll through the entire linked list, have a temp pointer to the next vector, delete the current one, update the current to the old next
    MsgNode* d=heads_[0];
    MsgNode* n=d;
    while(d != nullptr){
        n=d->next_[0];
        delete d;
        d=n;
    }

    //clear the labels and heads vectors
    heads_.clear();
    labels_.clear();

    //essentially re-run the constructor so result is a completely new list
    tail=nullptr;
    heads_.push_back(nullptr);
    labels_.push_back("all");
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::empty() const
{
    //list is empty if the heads pointer of the "all" label is null
    if(heads_[0]==nullptr){
        return true;
    }
    else{
        return false;
    }
}

// Complete
size_t LabelList::size() const
{
    MsgNode* n = this->heads_[0];
    size_t cnt = 0;
    while(n != nullptr){
        cnt++;
        n = n->next_[0];
    }
    return cnt;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::add(const MsgType& msg)
{
    //allocate new node, set "all" label equal to true
    MsgNode* nmsg = new MsgNode(msg);
    nmsg->labelled_[0]=true;

    //set the previous of the new message equal to the old tail and the next to null
    nmsg->prev_[0]=tail;
    nmsg->next_[0]=nullptr;

    //if pointer wasn't empty (ie there was a node in the list already), set the next pointer of the old tail to the new message
    if(tail != nullptr){
        tail->next_[0]=nmsg;
    }

    //if the pointer is empty, make the new pointer the head
    if(heads_[0]==nullptr){
        heads_[0]=nmsg;
    }

    //update my tail so it now points at the new message which is last in the list
    tail=nmsg;

    //create and return a message token to the newly inserted message node
    return MsgToken(nmsg, this);

}


// To be completed - must adhere to any requirements in the .h file
void LabelList::remove(const MsgToken& token)
{
    //check to make sure the token to remove is a valid one, will return if it isn't
    if(!token.isValid()){
        return;
    }

    //create a messge node pointer for the node I want to remove
    MsgNode* dmsg=token.node_;

    //if the message to be removed is the tail node, update the tail to the second to last node in the list
    if(dmsg==tail){
        tail=dmsg->prev_[0];
    }

    //for loop to run through all the labels that the message is a part of
    for(size_t i=0; i<dmsg->labelled_.size(); i++){
        //check to see if the message to remove is part of the label, if yes reassign pointers, if no do nothing
        if(dmsg->labelled_[i]){
            //if the message to be deleted is the head for the label, change the head to the next node in the label
            if(heads_[i]==dmsg){
                heads_[i]=dmsg->next_[i];
            }
            //if dmsg has a node after it (ie not last in the list) then update that node's previous pointer to point at the node before dmsg
            if(dmsg->next_[i]!=nullptr){
                dmsg->next_[i]->prev_[i]=dmsg->prev_[i];
            }
            //if dmsg has a node before it (ie not forst in the list), update that node do its next pointer points at the node after dmsg
            if(dmsg->prev_[i]!=nullptr){
                dmsg->prev_[i]->next_[i]=dmsg->next_[i];
            }
        }
    }

    //actually delete the message node and free up the space
    delete dmsg;

}

// To be completed - must adhere to any requirements in the .h file
void LabelList::label(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }

    //get the index of the label, or INVALID_LABEL if it does not exist and create a message node pointer to the token
    size_t index=findLabelIndex(label);
    MsgNode* n=token.node_;

    //if the label already exists...
    if(index != INVALID_LABEL){
        //check to see if the token is already a member of the label and return if it is
        if(token.isLabelMember(label)){
            return;
        }
        else{
            //keep track of the size that the labelled vector is at before resizing
            size_t olds=n->labelled_.size();

            //if the labelled vector does not already go up to the index of the label, it must be resized
            //must keep in mind that size should be one larger than index
            if(index >= n->labelled_.size()){
                n->labelled_.resize(index+1);
            }
            //initialize the values in labelled
            for(size_t i=olds; i < n->labelled_.size(); i++){
                n->labelled_[i]=false;
            }

            //scroll through the "all" label to find the closest msgs in front and back that are part of the label
            //go until end of list (null) or break when a member message is hit
            MsgNode* forward=n;
            MsgNode* back=n;
            while(forward!=nullptr){
                if(forward->labelled_[index]==true){
                    break;
                }
                forward=forward->next_[0];
            }
            while(back!=nullptr){
                if(back->labelled_[index]){
                    break;
                }
                back=back->prev_[0];
            }

            //if back is null, then this msg will be our new head for the label
            //update the previous pointer of n and next pointer of the message before to point at eachother
            if(back==nullptr){
                n->next_[index]=heads_[index];
                heads_[index]->prev_[index]=n;
                heads_[index]=n;
            }
            else{
                back->next_[index]=n;
                n->prev_[index]=back;
            }

            //if forward is null then we just need to update the next of node before (which we already did) and set next to null
            //don't need to update tail because tail only points to last in "all" label and all nodes are already members of "all"
            //update the next pointer of n and previous of forward to point at eachother
            if(forward==nullptr){
                n->next_[index]=nullptr;
            }
            else{
                forward->prev_[index]=n;
                n->next_[index]=forward;
            }

            //change the bool so the msg is in the label now
            n->labelled_[index]=true;
        }
    }
    //if the label does not already exist
    else{
        //push the label into the back of the labels vector
        //push n into the back of the heads pointer because n will be the head for the new label
        labels_.push_back(label);
        heads_.push_back(n);

        //resize the labelled, next, and previous vectors of n to be the same size as labels_
        n->labelled_.resize(labels_.size());
        n->next_.resize(labels_.size());
        n->prev_.resize(labels_.size());

        //set the bool for the label equal to true and next/prev pointers to null
        //remember index is size-1
        n->labelled_[labels_.size()-1]=true;
        n->next_[labels_.size()-1]=nullptr;
        n->prev_[labels_.size()-1]=nullptr;
    }

}

// To be completed - must adhere to any requirements in the .h file
void LabelList::unlabel(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }

    //get the index of the label, will throw if label doesn't exist
    size_t index=getLabelIndex(label);
    MsgNode* n=token.node_;

    //if the index is 0 (part of "all" label) or the msg isn't part of the label, return
    if(index==0 || !n->labelled_[index]){
        return;
    }
    //make sure node isn't a part of label anymore
    n->labelled_[index]=false;

    //if the message is the only one in the label, set the head to null and do then do nothing else
    if(n->next_[index]==nullptr && n->prev_[index]==nullptr){
        heads_[index]=nullptr;
        return;
    }

    //if the node is the head, update the head pointer and set the previous of the new head to null
    if(heads_[index]==n){
        heads_[index]=n->next_[index];
        n->next_[index]->prev_[index]=nullptr;
    }
    //if the node is the last in the label, update the next pointer of the node before it to be null
    else if(n->next_[index]==nullptr){
        n->prev_[index]->next_[index]=nullptr;
    }
    //if it's not first or last, then update the pointers on either side
    else{
        n->prev_[index]->next_[index]=n->next_[index];
        n->next_[index]->prev_[index]=n->prev_[index];
    }
}

// Complete - Do not alter
LabelList::MsgToken LabelList::find(const MsgType& msg, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(n != nullptr)
    {
        if(n->msg_ == msg)
        {
            return MsgToken(n, this);
        }
        n = n->next_[level];
    }
    return end();
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::find(size_t index, const LabelType& label)
{
    //get the index (level bc index is already used) of the label, will throw if invalid
    size_t level=this->getLabelIndex(label);
    MsgNode* n=this->heads_[level];

    //move through the list until the index is reached, if n becomes a null pointer (reached the end of the list) return end;
    for(size_t i=0; i<index; i++){
        if(n==nullptr){
            return end();
        }
        n=n->next_[level];
    }

    //return a token to n
    return MsgToken(n, this);
}

// Complete - Do not alter
LabelList::MsgToken const & LabelList::end() const
{
    return end_;
}

// Complete - Do not alter
void LabelList::print(std::ostream& ostr, const LabelType& label, char separator) const
{
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(nullptr != n)
    {
        ostr << n->msg_ << separator;
        n = n->next_[level];
    }
    ostr << std::endl;
}

// To be completed - must adhere to any requirements in the .h file
size_t LabelList::findLabelIndex(const LabelType& label) const
{
    //initialize to INVALID_LABEL, then I can update when the label is found
    size_t index=INVALID_LABEL;
    //run through the label vector to find the label
    for(size_t i=0; i<labels_.size(); i++){
        if(labels_[i]==label){
            index=i;
            break;
        }
    }
    //return the index
    return index;
}

// Complete - Do not alter
size_t LabelList::getLabelIndex(const LabelType& label) const
{
    size_t retval = this->findLabelIndex(label);
    if(INVALID_LABEL == retval)
    {
        throw std::out_of_range("Label doesn't exist");
    }
    return retval;
}


