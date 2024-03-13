//
// Created by Rostik on 3/8/2024.
//

#ifndef HOMEWORK_3_SMARTPTR_H
#define HOMEWORK_3_SMARTPTR_H

#include "PtrBase.h"

template <typename T> class WeakPtr;

template <typename Resource>
class SharedPtr : public PtrBase<Resource> {
public:
    SharedPtr() = default;

    explicit SharedPtr(Resource *res) {
        this->ConstructShared(res);
    }

    SharedPtr(const SharedPtr<Resource> &rhs) {
        this->ConstructSharedFrom(rhs);
    }

    SharedPtr(const WeakPtr<Resource> &rhs) {
        this->ConstructSharedFrom(rhs);
    }

    SharedPtr<Resource>& operator=(const SharedPtr<Resource> &rhs) {
        this->ConstructSharedFrom(rhs);

        return *this;
    }

    ~SharedPtr() {
        this->DecRefs();
    }

    void Reset() {
        SharedPtr().Swap(*this);
    }

    void Reset(Resource *res) {
        SharedPtr(res).Swap(*this);
    }
};

template <typename Resource>
class WeakPtr : public PtrBase<Resource> {
public:
    WeakPtr() = default;

    WeakPtr(const WeakPtr<Resource> &rhs) {
        this->ConstructWeakFrom(rhs);
    }

    WeakPtr(const SharedPtr<Resource> &rhs) {
        this->ConstructWeakFrom(rhs);
    }

    WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs) {
        this->ConstructWeakFrom(rhs);

        return *this;
    }

    WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs) {
        this->ConstructWeakFrom(rhs);

        return *this;
    }

    ~WeakPtr() {
        this->DecWeaks();
    }

    void Reset() {
        WeakPtr().Swap(*this);
    }

    bool Expired() {
        return this->UseCount() == 0;
    }

    SharedPtr<Resource> Lock() const {
        return Expired() ? SharedPtr<Resource>() : SharedPtr<Resource>(*this);
    }
};


#endif //HOMEWORK_3_SMARTPTR_H
