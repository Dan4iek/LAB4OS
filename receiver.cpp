
#include "file_queue.h"
#include <iostream>
#include <windows.h>
int main(){
    std::string f; int cap,n;
    std::cout<<"File: "; std::cin>>f;
    std::cout<<"Capacity: "; std::cin>>cap;
    FileQueue q(f.c_str(),cap,true);
    std::cout<<"Sender count: "; std::cin>>n;
    for(int i=0;i<n;i++){
        STARTUPINFO si{sizeof(si)}; PROCESS_INFORMATION pi{};
        std::string cmd="Sender.exe "+f;
        CreateProcessA(nullptr,cmd.data(),0,0,FALSE,0,0,0,&si,&pi);
    }
    while(true){
        std::string c; std::cout<<"Command(read/exit): "; std::cin>>c;
        if(c=="read") q.receive();
        if(c=="exit") break;
    }
}
