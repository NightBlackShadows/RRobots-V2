#include "LinkedList.h"
/*
LinkedList::LinkedList(){
    size = 0;
    tail = root = NULL;
}

bool LinkedList::add(T value){
    if(value == null)
        return false;
    if(size == 0){
        root = new Node;
        root.data = value;
        tail = root;
        return true;
    }
    Node node = getNode(size-1);
    node.next = new Node;
    node.next.value = value;
    tail = node.next;
    return true;
}

std::iterator LinkedList::Itr(){
    return new Itr();
}

T LinkedList::remove(){
    return false;
}

Node LinkedList::getNode(int index) {
    Node node = root;
    for(int i = 0; i < index && node != null; i++){
        node = node.next;
    }
    return node;
}*/