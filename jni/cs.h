#ifndef _CS_H_
#define _CS_H_

#include <stdio.h>
void *MSOpenMemory(void *data, size_t size);
void MSCloseMemory(void *handle);
void MSClearCache(void *data, size_t size);

void MSHookFunction(void *symbol, void *replace, void **result);

struct MSHookMemory {
    void *handle_;

    MSHookMemory(void *data, size_t size) :
        handle_(MSOpenMemory(data, size))
    {
    }

    void Close() {
        if (handle_ != NULL) {
            MSCloseMemory(handle_);
            handle_ = NULL;
        }
    }

    ~MSHookMemory() {
        Close();
    }
};

#endif
