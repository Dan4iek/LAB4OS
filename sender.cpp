
#include "file_queue.h"
#include <iostream>
int main(int c,char** v){
    if(c<2) return 1;
    FileQueue q(v[1],0,false);
    while(true){
        std::string cmd; std::cout<<"Command(send/exit): "; std::cin>>cmd;
        if(cmd=="send"){ std::string m; std::cout<<"Msg: "; std::cin>>m; q.send(m.c_str()); }
        if(cmd=="exit") break;
    }
}
