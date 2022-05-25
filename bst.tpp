
#include <iostream>
#include "bst.h"

template <typename T>
BinaryTree<T>::BinaryTree() : size(0), root_node_ptr(nullptr)
{
}

template <typename T>
bool BinaryTree<T>::push_item(T data)
{
    node<T>(*node_ptr) = new node<T>;
    if (this->root_node_ptr == nullptr) // first item?
    {
        node_ptr->smaller_node_ptr = nullptr;
        node_ptr->greater_node_ptr = nullptr;
        node_ptr->status = HEAD;
        this->root_node_ptr = node_ptr;
    }
    else
    {                                                      // nope
        node<T>(*kamikaze_node_ptr) = this->root_node_ptr; // used to iterate to end of node leaf, nothing else
        node<T>(*node_parent_ptr) = kamikaze_node_ptr;
        while (kamikaze_node_ptr != nullptr)
        {
            if (kamikaze_node_ptr->data < data)
            {
                node_parent_ptr = kamikaze_node_ptr;                     // hold prev node for detect last node
                kamikaze_node_ptr = kamikaze_node_ptr->greater_node_ptr; // iter to greater node
                continue;
            }
            if (kamikaze_node_ptr->data > data)
            {
                node_parent_ptr = kamikaze_node_ptr;                     // hold prev node for detect last node
                kamikaze_node_ptr = kamikaze_node_ptr->smaller_node_ptr; // iter to smaller node
                continue;
            }
        }
        if (node_parent_ptr->data < data)
        {
            node_parent_ptr->greater_node_ptr = node_ptr;
            node_ptr->status = GREATER;
        }
        else
        {
            node_parent_ptr->smaller_node_ptr = node_ptr;
            node_ptr->status = SMALLER;
        }
    }
    node_ptr->data = data;
    this->size++;
    return this->size;
}
template <typename T>
static node<T>(*tmp_target_node_ptr);

template <typename T>
bool BinaryTree<T>::remove_item(T data)
{
    if (this->root_node_ptr == nullptr)
        return false;

    tmp_target_node_ptr<T> = this->root_node_ptr;
    node<T>(*parent_node_ptr) = get_target_node(tmp_target_node_ptr<T>, data);

    if (parent_node_ptr == nullptr)
        return false;

    node<T>(*g_target_node_ptr) = tmp_target_node_ptr<T>->greater_node_ptr;
    node<T>(*s_target_node_ptr) = tmp_target_node_ptr<T>->smaller_node_ptr;

    position status = tmp_target_node_ptr<T>->status;

    delete tmp_target_node_ptr<T>;

    if (status == SMALLER)
    {
        parent_node_ptr->smaller_node_ptr = g_target_node_ptr;
        if (g_target_node_ptr != nullptr)
        {
            g_target_node_ptr->status = SMALLER;
            connect_node(g_target_node_ptr, s_target_node_ptr);
        }
        return true;
    }
    if (status == GREATER)
    {
        parent_node_ptr->greater_node_ptr = g_target_node_ptr;
        if (g_target_node_ptr != nullptr)
        {
            g_target_node_ptr->status = GREATER;
            connect_node(g_target_node_ptr, s_target_node_ptr);
        }
        return true;
    }
    return false;
}

template <typename T>
void BinaryTree<T>::connect_node(node<T>(*g_target_node_ptr), node<T>(*s_target_node_ptr))
{
    while (g_target_node_ptr->smaller_node_ptr != nullptr)
    {
        g_target_node_ptr = g_target_node_ptr->smaller_node_ptr;
    }
    g_target_node_ptr->smaller_node_ptr = s_target_node_ptr;
}

template <typename T>
node<T> *BinaryTree<T>::get_target_node(node<T>(*target_node_ptr), T data)
{
    node<T>(*target_parent_ptr) = target_node_ptr;
    while (target_node_ptr != nullptr)
    {
        if (target_node_ptr->data == data)
            break;

        if (target_node_ptr->data < data)
        {
            target_parent_ptr = target_node_ptr;
            target_node_ptr = target_node_ptr->greater_node_ptr;
            continue;
        }
        if (target_node_ptr->data > data)
        {
            target_parent_ptr = target_node_ptr;
            target_node_ptr = target_node_ptr->smaller_node_ptr;
            continue;
        }
    }
    tmp_target_node_ptr<T> = target_node_ptr;

    if (target_node_ptr == nullptr)
        return nullptr;

    return target_parent_ptr;
}

template <typename T>
T BinaryTree<T>::find(T data)
{
    if (this->root_node_ptr == nullptr)
        return static_cast<T>(0);

    node<T>(*target_node_ptr) = this->root_node_ptr;
    while (target_node_ptr != nullptr)
    {
        if (target_node_ptr->data == data)
            break;

        if (target_node_ptr->data < data)
        {
            target_node_ptr = target_node_ptr->greater_node_ptr;
            continue;
        }
        if (target_node_ptr->data > data)
        {
            target_node_ptr = target_node_ptr->smaller_node_ptr;
            continue;
        }
    }

    if (target_node_ptr == nullptr)
        return static_cast<T>(0);

    return target_node_ptr->data;
}

template <typename T>
void BinaryTree<T>::print_items()
{
    if (this->root_node_ptr == nullptr)
        return;

    print_items_recursively(this->root_node_ptr);
}

template <typename T>
void BinaryTree<T>::print_items_recursively(node<T>(*target_node_ptr))
{
    node<T>(*node_parent_ptr);
    while (target_node_ptr != nullptr)
    {
        std::cout << "Data : " << target_node_ptr->data << std::endl;

        node_parent_ptr = target_node_ptr;
        target_node_ptr = target_node_ptr->smaller_node_ptr;
        if (target_node_ptr != nullptr)
            print_items_recursively(target_node_ptr);

        target_node_ptr = node_parent_ptr->greater_node_ptr;
        if (target_node_ptr != nullptr)
            print_items_recursively(target_node_ptr);

        std::cout << "*******************" << std::endl;
    }
}
