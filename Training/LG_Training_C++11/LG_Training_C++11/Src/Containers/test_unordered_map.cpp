#include "test_unordered_map.h"
#include <unordered_map>
#include <map>
#include <iostream>
#include <string>
//unordered_map  containers are generally faster than map
//Internally, the elements in the unordered_map are not sorted in any particular order with respect 
//to either their key or mapped values, but organized into buckets depending on their hash values 
//to allow for fast access to individual elements directly by their key values
//(with a constant average time complexity on average).
//local_iterator begin ( size_type n );

void test_unordered_map()
{
    std::map<std::string, int> map;
    map["c"] = 3;
    map["d"] = 4;
    map["e"] = 5;
    map["a"] = 1;
    map["b"] = 2;
    // still print specific order: a,b,c,d,e
    std::map<std::string, int>::iterator it;
    for (it = map.begin(); it != map.end(); it++)
    {
        const std::pair<std::string, int>& element = *it;
        std::cout << "{" << element.first << "," << element.second << "}" << std::endl;
    }

    std::unordered_map<std::string, std::string> mymap;
    mymap = { { "Australia","Canberra" },{ "U.S.","Washington" },{ "France","Paris" },{ "Australia","Canberra_1" } };

    std::cout << "mymap contains:";
    for (auto it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << " " << it->first << ":" << it->second;
    std::cout << std::endl;

    std::string input = "Australia";
    std::unordered_map<std::string, std::string>::const_iterator got = mymap.find(input);
    if (got == mymap.end())
        std::cout << "not found";
    else
        std::cout << got->first << " is " << got->second;

    for (auto& x : mymap) {
        std::cout << "Element [" << x.first << ":" << x.second << "]";
        std::cout << " is in bucket #" << mymap.bucket(x.first) << std::endl;
    }

    //Return number of buckets
    unsigned nbuckets = mymap.bucket_count();
    std::cout << "mymap has " << nbuckets << " buckets:\n";

    for (unsigned i = 0; i<nbuckets; ++i) {
        //Returns the number of elements in bucket n.
        std::cout << "bucket #" << i << " has " << mymap.bucket_size(i) << " elements.\n";
    }
}