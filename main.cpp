#include <string>
#include <thread>
#include <iostream>
#include "dlib/pipe.h"

const int USER_ERROR__inconsistent_build_configuration__see_dlib_faq_1_ = 0;


int main(){
    dlib::pipe<std::string> q{8};
    std::string strings[] = {"string 1", "string 2", "string 3", "string 4", "string 5"};
    for(auto &s: strings){
        std::cout << "enuqeueueing " << s << "\n"; 
        q.enqueue(s);
        std::cout << "s is now :\"" << s << "\"\n"; 
    }
    
    std::string s;
    while(q.size()){
        q.dequeue_or_timeout(s,0);
        std::cout << "dequeueing " << s << "\n";
    }

    std::thread te{ [&q] {
        for (int i = 0; i < 1024; ++i) {
            std::string s{ "string " + std::to_string(i) };
            q.enqueue(s);
        }
    }};

    std::thread td{ [&q] {
        std::string s;
        for (int i = 0; i < 1024; ++i) {
            q.dequeue_or_timeout(s, 1000);
            std::cout << s << "\n";
        }
    } };


    te.join();
    td.join();
}