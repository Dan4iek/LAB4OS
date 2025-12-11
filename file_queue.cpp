
#include "file_queue.h"
#include <iostream>
#include <cstring>

FileQueue::FileQueue(const char* name, int cap, bool create) {
    mutex_ = CreateMutex(nullptr,FALSE,"Global\\QMutex");
    empty_ = CreateSemaphore(nullptr,cap,cap,"Global\\QEmpty");
    full_  = CreateSemaphore(nullptr,0,cap,"Global\\QFull");
    file_ = CreateFileA(name,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,nullptr,
        create?CREATE_ALWAYS:OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(create){
        h_={0,0,cap}; DWORD w;
        WriteFile(file_,&h_,sizeof(h_),&w,nullptr);
        Message m{}; for(int i=0;i<cap;i++) WriteFile(file_,&m,sizeof(m),&w,nullptr);
    }
}
void FileQueue::rh(){SetFilePointer(file_,0,0,0);DWORD r;ReadFile(file_,&h_,sizeof(h_),&r,0);}
void FileQueue::wh(){SetFilePointer(file_,0,0,0);DWORD w;WriteFile(file_,&h_,sizeof(h_),&w,0);}
void FileQueue::send(const char* msg){
    WaitForSingleObject(empty_,INFINITE);
    WaitForSingleObject(mutex_,INFINITE);
    rh();
    DWORD pos=sizeof(QueueHeader)+h_.w*sizeof(Message);
    SetFilePointer(file_,pos,0,0);
    Message m{}; strncpy_s(m.text,msg,MAX_MSG-1);
    DWORD w; WriteFile(file_,&m,sizeof(m),&w,0);
    h_.w=(h_.w+1)%h_.cap; wh();
    ReleaseMutex(mutex_); ReleaseSemaphore(full_,1,0);
}
void FileQueue::receive(){
    WaitForSingleObject(full_,INFINITE);
    WaitForSingleObject(mutex_,INFINITE);
    rh();
    DWORD pos=sizeof(QueueHeader)+h_.r*sizeof(Message);
    SetFilePointer(file_,pos,0,0);
    Message m{}; DWORD r; ReadFile(file_,&m,sizeof(m),&r,0);
    std::cout<<"Received: "<<m.text<<std::endl;
    h_.r=(h_.r+1)%h_.cap; wh();
    ReleaseMutex(mutex_); ReleaseSemaphore(empty_,1,0);
}
