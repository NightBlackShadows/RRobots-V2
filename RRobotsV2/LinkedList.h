#pragma once

#include <iterator>

template<class T>
class LinkedList
{
public:
    class Node{
        T data;
        Node* next;
        Node(T value, Node *node){
            data = value;
            next -> node;
        };
    };
    LinkedList<T>(){
        size = 0;
        root = tail = LinkedList<T>::Node::Node(NULL,NULL);
    };
    T getIndex(int index){
        if(index < 0 || index > size)
            throw std::invalid_argument("Index out of range");
        if(index == 0)
            return root.data;
        else if(index == size-1)
            return tail.data;
        else{
            Node node = findNode(index);
            return node.data;
        }

    }
    bool add(T value){
        if(value == NULL)
            return false;
        if(size == 0){
            root = new Node(value,NULL);
            tail = root;
            size++;
            return true;
        }else{
            Node node = findNode(size-1);
            node.next = Node(value,NULL);
            tail = node.next;
            size++;
            return true;
        }

    };
    T remove(int index){
        if(index < 0 || index > size)
            throw std::invalid_argument("Index out of range");
        Node node = findNode(index);
        return node.data;
    };
    ~LinkedList<T>(){
        size = 0;
        root = NULL;
        tail = NULL;
    };
private:
    int size;
    Node root, tail;
    Node findNode(int index){
        if(index < 0 || index > size)
            throw std::invalid_argument( "received invalid value" );
        if(root == NULL)
            throw std::invalid_argument("root node is null");
        Node node = root;
        for(int i = 0; i < index && node != NULL;i++){
            node = node.next;
        }
        return node;
    }
};
