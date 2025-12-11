
#pragma once
#include <windows.h>

constexpr int MAX_MSG = 20;

struct Message { char text[MAX_MSG]; };
struct QueueHeader { int w, r, cap; };

class FileQueue {
public:
    FileQueue(const char* name, int cap, bool create);
    void send(const char* msg);
    void receive();
private:
    HANDLE file_, mutex_, empty_, full_;
    QueueHeader h_;
    void rh(); void wh();
};
