#include "BackgroundThreadWrapper.hpp"
#include <coreinit/cache.h>

BackgroundThreadWrapper::BackgroundThreadWrapper(int32_t priority) : CThread(CThread::eAttributeAffCore2, priority, 0x100000) {
}

BackgroundThreadWrapper::~BackgroundThreadWrapper() {
    exitThread = 1;
    DCFlushRange((void *) &exitThread, 4);
}

void BackgroundThreadWrapper::executeThread() {
    while (true) {
        if (exitThread) {
            break;
        }
        if (!whileLoop()) {
            break;
        }
    }
}
