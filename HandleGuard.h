//
// Created by Rostik on 3/7/2024.
//

#ifndef HOMEWORK_3_HANDLEGUARD_H
#define HOMEWORK_3_HANDLEGUARD_H

#include "windows.h"

class HandleGuard {
public:
    explicit HandleGuard(HANDLE h) : handle_(h) {}

    explicit operator HANDLE() const {
        return handle_;
    }

    HANDLE Get() {
        return handle_;
    }

    ~HandleGuard() {
        CloseHandle(handle_);
    }

private:
    HANDLE handle_;
};

#endif //HOMEWORK_3_HANDLEGUARD_H
