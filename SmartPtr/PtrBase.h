//
// Created by Rostik on 3/13/2024.
//

#ifndef HOMEWORK_3_PTRBASE_H
#define HOMEWORK_3_PTRBASE_H

#include "ControlBlock.h"

template <typename Resource>
class PtrBase {
public:
    Resource* Get() const {
        return resource_;
    }

    Resource& operator*() const {
        return *resource_;
    }

    Resource& operator->() const {
        return *resource_;
    }

    long UseCount() const {
        return controlBlock_ ? controlBlock_->RefsCount() : 0;
    }

    void Swap(PtrBase<Resource> &rhs) {
        swap(resource_, rhs.resource_);
        swap(controlBlock_, rhs.controlBlock_);
    }

protected:
    void ConstructShared(Resource *res) {
        resource_ = res;
        controlBlock_ = new ControlBlock();
    }

    void ConstructWeakFrom(const PtrBase<Resource>& ptr) {
        resource_ = ptr.resource_;
        controlBlock_ = ptr.controlBlock_;
        if (controlBlock_)
            controlBlock_->IncWeaks();
    }

    void ConstructSharedFrom(const PtrBase<Resource>& ptr) {
        resource_ = ptr.resource_;
        controlBlock_ = ptr.controlBlock_;
        if (controlBlock_)
            controlBlock_->IncRefs();
    }

    void DecRefs() {
        controlBlock_->DecRefs();
        if (controlBlock_->RefsCount() == 0)
            Destruct();
    }

    void DecWeaks() {
        if (controlBlock_)
            controlBlock_->DecWeaks();
    }

private:
    void Destruct() {
        if (controlBlock_)
        {
            delete resource_;
            delete controlBlock_;
        }
    }

private:
    Resource* resource_ = nullptr;
    ControlBlock* controlBlock_ = nullptr;
};


#endif //HOMEWORK_3_PTRBASE_H
