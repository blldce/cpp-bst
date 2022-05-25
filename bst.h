
#ifndef BINARY_H
#define BINARY_H 1

enum position
{
    SMALLER = 1,
    HEAD,
    GREATER
};

template <typename T>
struct node
{
    T data;
    position status;
    node<T>(*smaller_node_ptr);
    node<T>(*greater_node_ptr);
};

template <typename T>
class BinaryTree
{
private:
    int size;
    node<T>(*root_node_ptr);

public:
    explicit BinaryTree();
    bool push_item(T);
    bool remove_item(T);
    T find(T);
    void print_items();

private:
    node<T> *get_target_node(node<T>(*), T);
    void connect_node(node<T>(*), node<T>(*));
    void print_items_recursively(node<T>(*));
};

#include "bst.tpp"

#endif
