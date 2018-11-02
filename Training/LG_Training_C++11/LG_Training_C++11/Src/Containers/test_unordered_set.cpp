#include "test_unordered_set.h"
#include <iostream>
#include <string>
#include <unordered_set>
//Unordered sets are containers that store unique elements in no particular order, 
//and which allow for fast retrieval of individual elements based on their value.
//local_iterator begin ( size_type n );

void test_unordered_set()
{
    std::unordered_set<std::string> myset =
    { "Mercury","Venus","Earth","Mars","Jupiter","Saturn","Uranus","Neptune" };

    myset.insert("purple");
    myset.insert({ "purple","orange" });
    myset.erase("purple");
    std::cout << "myset contains:";
    for (auto it = myset.begin(); it != myset.end(); ++it)
        std::cout << " " << *it;
    std::cout << std::endl;

    std::cout << "myset's buckets contain:\n";
    for (unsigned i = 0; i < myset.bucket_count(); ++i) {
        std::cout << "bucket #" << i << " contains:";
        for (auto local_it = myset.begin(i); local_it != myset.end(i); ++local_it)
            std::cout << " " << *local_it;
        std::cout << std::endl;
    }
}