#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdexcept>
#include <iostream>
using std::to_string;
using std::out_of_range;

template <typename T>
struct SinglyLinkedListNode {
  T data;
  SinglyLinkedListNode<T>* next{nullptr};
};

template <typename T>
class SinglyLinkedList {
  private:
    SinglyLinkedListNode<T>* head{nullptr};
    SinglyLinkedListNode<T>* tail{head};

  public:
    void prepend(T data){
      SinglyLinkedListNode<T>* new_node = new SinglyLinkedListNode<T>{data,head};
      head = new_node;
    }

    void append(T data){
      SinglyLinkedListNode<T>* new_tail = new SinglyLinkedListNode<T>{data,nullptr};
      SinglyLinkedListNode<T>* current_tail{tail};
      if (tail){
        current_tail->next =  new_tail;
      } else {
        head = new_tail;
      }
      tail = new_tail; 
    }
    
    void insert_after(T data,size_t position){
      SinglyLinkedListNode<T>* new_node = new SinglyLinkedListNode<T>{data,nullptr};
      SinglyLinkedListNode<T>* current_node{head};
      if ((int)position<0){
        // if position is 0, 
        new_node->next = head;
        head = new_node;
      } else{
        for(size_t i{0} ; i<position ; i++){
          if(!current_node->next){
            throw out_of_range("Cannot insert after index "+to_string(position));   
          }
          current_node = current_node->next;
        }
        new_node->next = current_node->next;
        current_node->next = new_node;
      }
      if (tail == current_node){
        tail = new_node;
      }
    }

    void remove(size_t position){
      SinglyLinkedListNode<T>* n_minus_1{head};
      SinglyLinkedListNode<T>* n_plus_1;
      SinglyLinkedListNode<T>* node_to_delete;
      for(size_t i{0} ; i<(position-1) ; i++){
        if(!n_minus_1->next){
          throw out_of_range("List index "+to_string(position)+" is out of range");
        }
        n_minus_1 = n_minus_1->next;
      }
      node_to_delete = n_minus_1->next;
      n_plus_1 = node_to_delete->next;
      n_minus_1->next = n_plus_1;
      delete node_to_delete;
    }

    T at(size_t position){
      SinglyLinkedListNode<T>* node{head};
      for(size_t i{0} ; i<position ; i++){
        if(!node->next){
          throw out_of_range("List index "+to_string(position)+" is out of range");
          return "";
        }
        node = node->next;
      }
      return node->data;
    }

    T get_head(){
      return head->data;
    }

    T get_tail(){
      return tail->data;
    }

    ~SinglyLinkedList(){
      // Destructor releases all nodes from heap
      if(head != nullptr){
        SinglyLinkedListNode<T>* next_node{head};
        while(next_node->next){      
          SinglyLinkedListNode<T>* tmp = next_node;
          next_node = next_node->next;
          delete tmp;
        }
      }
    }
};
#endif