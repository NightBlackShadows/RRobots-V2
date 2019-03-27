//
// Created by shade on 3/26/19.
//

#ifndef RROBOTSV2_NODE_H
#define RROBOTSV2_NODE_H

template<class T>
class Node {
public:
    Node<T>* next;
    T data;
    Node<T>(T data, Node* next){
        this->next = next;
        this->data = data;
    };
    ~Node<T>();
};


#endif //RROBOTSV2_NODE_H
