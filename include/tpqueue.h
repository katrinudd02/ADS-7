// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <vector>
#include <string>

template<typename T>
class TPQueue {
  // реализация шаблона очереди с приоритетом на связанном списке
 public:
     PQueue():head(nullptr), tail(nullptr){}
     ~TPQueue();
     void push(const T&);
     T pop();
     void print()const;
     void insert(vector<int>&, int);
     void remove(vector<int>&, int) {

 private:
     TPQueue::SYM* create(const T&);
     void ChangeElements(int*, int*);
     void sort(vector<int>&, int);
     SYM* head;
     SYM* tail;
};

struct SYM {
  char ch;
  int prior;
};

template<typename T>
typename TPQueue<T>::SYM* TPQueue<T>::create(const T& data) {
    SYM* sb = new SYM;
    sb->data = data;
    sb->next = nullptr;
    return sb;
}

template<typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template<typename T>
void TPQueue<T>::push(const T& data) {
    if (tail && head) {
        tail->next = create(data);
        tail = tail->next;
    } else {
        head = create(data);
        tail = head;
    }
}

template<typename T>
T TPQueue<T>::pop() {
    if (head) {
        SYM* tmp = head->next;
        T data = head->data;
        head = tmp;
        return data;
    } else {
        throw std::string("Empty!");
    }
}

template<typename T>
void TPQueue<T>::ChangeElements(int* a, int* b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

template<typename T>
void TPQueue<T>::sort(vector<int>& parent, int i) {
    int size = parent.size();
    int largest = i;
    int leftchild = 2 * i + 1;
    int rightchild = 2 * i + 2;
    if (leftchild < size && parent[leftchild] > parent[largest]) {
        largest = leftchild;
    }
    if (rightchild < size && parent[rightchild] > parent[largest]) {
        largest = rightchild;
    }
    if (largest != i) {
        ChangeElements(&parent[i], &parent[largest]);
        sort(parent, largest);
    }
}

template<typename T>
void TPQueue<T>::insert(vector<int>& parent, int newEl) {
    int size = parent.size();
    if (size == 0) {
        parent.push_back(newEl);
    } else {
        parent.push_back(newEl);
        for (int i = size / 2 - 1; i >= 0; i--) {
            sort(parent, i);
        }
    }
}

template<typename T>
void TPQueue<T>::remove(vector<int>& parent, int element) {
    int size = parent.size();
    int i;
    for (int i = 0; i < size; i++) {
        if (element == parent[i]) {
            break;
        }
    }

    ChangeElements(parent[i], parent[size - 1]);

    parent.pop_back();
    for (int i = size / 2 - 1; i >= 0; i--) {
        sort(parent, i);
    }
}

#endif  // INCLUDE_TPQUEUE_H_
