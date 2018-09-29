/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/
//4

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    // creste the head and tail sentinel
    list_head = new Double_node();
    list_tail = new Double_node();
    list_head->node_value = Type();
    list_tail->node_value = Type();
    // let list_head pointer to point to head sentinel node
    //let tail sentinel node to point to point to head sentinel and nullpter
    //let head sentinel node point to tail sentinel node and nullptr
    list_head->next_node = list_tail;
    list_head->previous_node = nullptr;
    list_tail->previous_node = list_head;
    list_tail->next_node = nullptr;
	
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    // creat an empty list
    list_head = new Double_node();
    list_tail = new Double_node();
    list_head->node_value = Type();
    list_tail->node_value = Type();
    
    //if the original list is empty, the new list only has head and tail
    if (list.list_size==0)
    {
        list_head->previous_node = nullptr;
        list_head->next_node = list_tail;
        list_tail->previous_node = list_head;
        list_tail->next_node = nullptr;
    }
    //if the list is not empty, create one new (curr) node to traverse the original list
    else{
 //let the curr point to the next node of the head sentinel
Double_node* curr=list.list_head->next_node;
Double_node* before=list_head;
    
while(curr->next_node!=NULL)
{
    //create one (newnew) node to traverse the new created list untill all items in original list is copyed to the new list
    Double_node* newnew=new Double_node();
    newnew->node_value=curr->node_value;
    
    //insert the (newnew) node to the new list between the tail sentinel and the node before the tail sentinel
    newnew->next_node=list_tail;
    newnew->previous_node=before;
    before->next_node=newnew;
    list_tail->previous_node=newnew;
    
    before=before->next_node;
    
    
    //let (curr) node to traverse through the original list
    curr=curr->next_node;
    //increment the list size
    list_size++;
}
   
}
}


template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    //create a new list
    list_head = new Double_node();
    list_tail = new Double_node();
    list_head->node_value = Type();
    list_tail->node_value = Type();
    
    
//if the original list is empty, then nothing will pass to the new list
    if (list.list_size==0){
        list_head->next_node=list_tail;
        list_tail->previous_node=list_head;
        list_head->previous_node=nullptr;
        list_tail->next_node=nullptr;
        
        
    }
    //call the swap fucntion to pass the items to the new created list
    swap(list);
    
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
 //delete all nodes by using the pop_front function untill only head and sentinels left
    while(!empty())
    {

         pop_front();
        
    }
    
    
    //delete head and tail sentinels
    delete list_tail;
    delete list_head;
    
	
 
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    //return the number of list
    return list_size;
  
	
    
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    
    // check is the list is empty; if it is, return true otherwise false
	return list_size==0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
   //check if the list is empyt, if no items in it, throw underflow
    if (empty())
        throw underflow();
  //check if the list is not empty, then return the value of the first node that the head sentinel points to
    else
        return list_head->next_node->node_value;
	
	 
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    //check if the list is empyt, if no items in it, throw underflow
    if (empty())
        throw underflow();
    //check if the list is not empty, then return the value of the previous node that the tail sentinel points to
    else
        return list_tail->previous_node->node_value;
	
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
   //return the address of waht the head sentinel points to
    return list_head->next_node;
	
	
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    //return the address of tail sentinel
    return list_tail;
	
	
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    //return the address of what the tail sentinel node points to
    return list_tail->previous_node;
	
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
   //return the address of the head sentinel itself
    return list_head;
	
	
}
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    // initialize a new node for triggering nodes through the list
    Double_node* trigger=list_head->next_node;
   
    while(trigger->next_node!=NULL)
    {
        //if found a node value matches obj, then return the adddress of the node
        if (trigger->node_value==obj)
        {return trigger;}
        
        trigger=trigger->next_node;
    }
    //if found no match, return the list tail
    return list_tail;
    
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    //create a count=0;
    int node_count=0;
     // initialize a new node for triggering nodes through the list
    Double_node* trigger=list_head->next_node;
    while(trigger->next_node!=NULL)
    {   //if found a node value matches obj, increment the count value; moving forward the counter
        if (trigger->node_value==obj)
        { node_count++;}
        
        trigger=trigger->next_node;
    }
   //return the number of occurrence of obj in the list
    return node_count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
    // This is done for you
    std::swap( list_head, list.list_head );
    std::swap( list_tail, list.list_tail );
    std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
    // This is done for you
    swap( rhs );
    
    return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
    // This is done for you
    swap( rhs );
    
    return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    //initialize a new Double node that has thenode value=obj
    Double_node* push_front=new Double_node();
    push_front->node_value=obj;
    //insert the new node at the front of the list
    
    //let the new node points to the next node of head sentinel
    push_front->next_node = list_head->next();
    //let the next node of head sentinel points back to the new node
    list_head->next_node->previous_node = push_front;
    //let the head sentinel points to the  new node
    list_head->next_node=push_front;
    //let the new node istself points back to the head sentinel
    push_front->previous_node=list_head;
    //increment the list size
    list_size++;
   
}


template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
//initialize a new Double node that has thenode value=obj
    Double_node* push_back=new Double_node();
    push_back->node_value=obj;
    //insert the new node at the end of the list
    
    //let the new node points back to the previous node of tail sentinel
    push_back->previous_node=list_tail->previous_node;
    //let the previous node of tail sentinel points to the new node
    list_tail->previous_node->next_node=push_back;
    //let the new node points to the tail sentinel
    push_back->next_node=list_tail;
    //let the tail sentinel points back to the new node
    list_tail->previous_node=push_back;
    
     //increment the list size
    list_size++;
    
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
  //check if the list is empyt, if no items in it, throw underflow
    if (empty())
    {  throw underflow();}
    //initialize a new node = the node that head sentinel points to, to store the node value
    Double_node *front=list_head->next_node;
    //delete the node after the head sentinel
    
    
    //let the next node of the next node (needed to be deleted) of the head sentinel points back to the head  sentinel
    list_head->next_node->next_node->previous_node=list_head;
    //let the head sentinel points to the next node of the next node (needed to be deleted) of head sentinel
    list_head->next_node=list_head->next_node->next_node;
    
    //delete the new node
    delete front;
    //decrement the list size
    list_size--;
    
    
    // Enter your implementation here
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    //check if the list is empyt, if no items in it, throw underflow
    if (empty())
    {throw underflow();}
     //initialize a new node = the node that tail sentinel points back to, to store the node value
    Double_node *pop_back=list_tail->previous_node;
    //delete the node before the tail sentinel
    
    
    //let the previous node of the node (needed to be deleted) points to the tail sentinel
    pop_back->previous_node->next_node=list_tail;
    //let the tail sentinel points back to the node that node (needed to delete) points back to
    list_tail->previous_node=pop_back->previous_node;
    
    //delete the new node
    delete pop_back;
    //decrement the list size
    list_size--;
    
    // Enter your implementation here
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    // initialize a counter=0
    int node_count=0;
    //create a new node (match)that points to the next node of head sentinel, and then let the node to traverse the list
    Double_node *match = list_head->next_node;
    //erase all instances of the node that has the value=obj
    
    while(match->next_node != NULL){
       if(match->node_value == obj){
          //if found the node that the node value=obj, then increment the counter
            node_count++;
           //initialize a new node(temp) for deleting the node (match)
            Double_node *temp=match;
    
            //delete the node (match) by making the node before the match points to the next node of match; and the next node of match points back to the previous node of match
           match->previous_node->next_node=match->next_node;
            match->next_node->previous_node=match->previous_node;
          
            //move match node to next node before deleting the
           match=match->next_node;
           //decrement the list size
            list_size--;
            //delete the node (temp)
            delete temp;
    
       }
        else{
            //move forward the node (match) to traverse the rest of the list items if there the node doesnot match the target node
            match = match->next_node;}

   }
    return node_count;

}
template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	// Enter your implementation here
	node_value=nv;

}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
   return node_value;
    
	// This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return previous_node;
	
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
	
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
