#include "test_forward_list.h"
#include <forward_list>
#include <iostream>
//Like Linked list (only append new elements at head of list)
//They are very similar to forward_list : The main difference being that forward_list objects are single 
//- linked lists, and thus they can ....only be iterated forwards......, in exchange for being somewhat smaller and more efficient.
void test_forward_list()
{
    std::forward_list<int> mylist = { 77, 2,2, 16 };

    //Returns an iterator pointing to the position before the first element in the container
    mylist.insert_after(mylist.before_begin(), 19); // 19,77,2,16
    //Remove elements with specific value
    mylist.remove(2); // 19,77,16
    mylist.push_front(3);// 3,19,77,16

    std::cout << "mylist contains: \n";
    std::forward_list<int>::iterator it = mylist.before_begin();
    it++;
    mylist.insert_after(it, 18);// 3,18,19,77,16

    for (it = mylist.begin(); it != mylist.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << '\n';
}