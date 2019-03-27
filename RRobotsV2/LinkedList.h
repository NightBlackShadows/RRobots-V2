#pragma once

#include <iterator>
#include <utility>
#include "WayType.h"
#include "Node.h"

template <typename T>
class LinkedList
{
public:

    LinkedList();

    T getIndex(int index){
        if(index < 0 || index > size)
            throw std::invalid_argument("Index out of range");
        if(index == 0)
            return root.move;
        else if(index == size-1)
            return tail.move;
        else{
            Node<T> node = findNode(index);
            return node.move;
        }
    };
    bool add(int characterColor, T data){
        if(size == 0) {
            root = Node<T>(data, NULL);
            tail = root;
            size++;
            return true;
        }
        else{
            Node<T> node = findNode(size-1);
            node.next = Node<T>(data,NULL);
            tail = node.next;
            size++;
            return true;
        }
        return false;
    };
    T remove(int index){
        if(index < 0 || index > size)
            throw std::invalid_argument("Index out of range");
        Node<T> node = findNode(index);
        T data = node.data;
        if(index == 0){
            root = node.next;
        }else{
            node.next = node.next->next;
        }


        return data;
    };

    int Size(){ return  size;};

    ~LinkedList<T>(){
        tail = root = NULL;
        size = 0;
    };
private:
    int size;
    Node<T>* root, *tail;
    Node<T> findNode(int index);
};
