#include <iostream>
#include <windows.h>
#include <memory>

#include "SmartPtr/SmartPtr.h"

#include "HandleGuard.h"

void closeSockFunc(SOCKET *sock) {
    closesocket(*sock);
    delete sock;
}

class CloseSockFunctor {
public:
    void operator() (SOCKET *sock) {
        closesocket(*sock);
        delete sock;
    }
};

int main() {
    // Custom guard
    HANDLE file = CreateFileA("test.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    HandleGuard guard(file);


    // Custom deleter

    auto closeSock = [](SOCKET *sock) {
        closesocket(*sock);
        delete sock;
    };

    std::unique_ptr<SOCKET, decltype(closeSock)> p1(new SOCKET(socket(AF_INET, SOCK_STREAM, 0)), closeSock);
    std::unique_ptr<SOCKET, void(*)(SOCKET*)> p2(new SOCKET(socket(AF_INET, SOCK_STREAM, 0)), closeSockFunc);
    std::unique_ptr<SOCKET, CloseSockFunctor> p3(new SOCKET(socket(AF_INET, SOCK_STREAM, 0)));

    // Custom smart pointers
    SharedPtr<int> shared(new int(5));
    auto weak = WeakPtr(shared);

    return 0;
}
