extern "C" {
#include "mutex.h"
}
#include <mutex>
#include <system_error>
#ifndef EMSCRIPTEN
#include <thread>
#endif

mutex_t mutex_create() {
    return new std::mutex();
}

void mutex_destroy(mutex_t mutex) {
    delete (std::mutex*)mutex;
}

void mutex_lock(mutex_t mutex) {
    ((std::mutex*)mutex)->lock();
}

void mutex_unlock(mutex_t mutex) {
    ((std::mutex*)mutex)->unlock();
}

void thread_run_detached(void (*fn)(void*), void* arg) {
#ifndef EMSCRIPTEN
    try {
        std::thread(fn, arg).detach();
        return;
    } catch (const std::system_error&) {
    }
#endif
    fn(arg);
}