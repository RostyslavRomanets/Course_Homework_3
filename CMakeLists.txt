cmake_minimum_required(VERSION 3.27)
project(homework_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework_3 main.cpp
        HandleGuard.h
        SmartPtr/SmartPtr.h
        SmartPtr/ControlBlock.h
        SmartPtr/PtrBase.h
)

if(WIN32)
    target_link_libraries(homework_3 wsock32 ws2_32)
endif()
