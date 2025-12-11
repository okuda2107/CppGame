#include "audio/OpenAL/Event.h"

#include "audio/OpenAL/EventInstance.h"

OpenAL::Event::Event(class Bank* bank) : mBank(bank) {};
OpenAL::Event::~Event() {
    while (!mInstances.empty()) {
        delete mInstances.back();
    }
}

void OpenAL::Event::AddInstance(class EventInstance* instance) {
    mInstances.push_back(instance);
}

void OpenAL::Event::RemoveInstance(class EventInstance* instance) {
    auto iter = find(mInstances.begin(), mInstances.end(), instance);
    if (iter != mInstances.end()) {
        std::iter_swap(iter, mInstances.end() - 1);
        mInstances.pop_back();
    }
}
