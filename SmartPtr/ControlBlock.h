//
// Created by Rostik on 3/9/2024.
//

#ifndef HOMEWORK_3_CONTROLBLOCK_H
#define HOMEWORK_3_CONTROLBLOCK_H

class ControlBlock {
public:
    void IncRefs() {
        refs_++;
    }

    void DecRefs() {
        refs_--;
    }

    void IncWeaks() {
        weaks_++;
    }

    void DecWeaks() {
        weaks_--;
    }

    long RefsCount() {
        return refs_;
    }

private:
    long refs_ = 1;
    long weaks_ = 0;
};

#endif //HOMEWORK_3_CONTROLBLOCK_H
