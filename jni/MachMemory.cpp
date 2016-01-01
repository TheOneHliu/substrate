/* Cydia Substrate - Powerful Code Insertion Platform
 * Copyright (C) 2008-2010  Jay Freeman (saurik)
*/

/* GNU Lesser General Public License, Version 3 {{{ */
/*
 * Substrate is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Substrate is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Substrate.  If not, see <http://www.gnu.org/licenses/>.
**/
/* }}} */

#include "cs.h"

#include <cstdio>
#include <unistd.h>
 #include <sys/mman.h>
#include <errno.h>
#include "testlog.h"

struct MSMemoryHook {
    //mach_port_t self_;
    uintptr_t base_;
    size_t width_;

    MSMemoryHook(uintptr_t base, size_t width) :
        base_(base),
        width_(width)
    {
    }
};

void *MSOpenMemory(void *data, size_t size) {
    if (size == 0)
        return NULL;

    int page(getpagesize());

    //mach_port_t self(mach_task_self());
    uintptr_t base(reinterpret_cast<uintptr_t>(data) / page * page);
    size_t width(((reinterpret_cast<uintptr_t>(data) + size - 1) / page + 1) * page - base);

    //if (kern_return_t error = vm_protect(self, base, width, FALSE, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_COPY)) {
    if(0 != mprotect((void*)((int)data& ~((page)-1)) , width,PROT_READ | PROT_WRITE | PROT_EXEC))
    {
        LOGI("MS:Error:vm_protect() = %d\n", errno);
        return NULL;
    }

    return new MSMemoryHook(base, width);
}

void MSCloseMemory(void *handle) {
    MSMemoryHook *memory(reinterpret_cast<MSMemoryHook *>(handle));
    //if (kern_return_t error = vm_protect(memory->self_, memory->base_, memory->width_, FALSE, VM_PROT_READ | VM_PROT_EXECUTE | VM_PROT_COPY))
    int page(getpagesize());
    if(0 != mprotect((void*)((int)memory->base_& ~((page)-1)) , memory->width_, PROT_READ | PROT_EXEC))
        LOGI("MS:Error:vm_protect() = %d\n", errno);
    delete memory;
}

//extern "C" void __clear_cache (char *beg, char *end);

void MSClearCache(void *data, size_t size) {
#ifdef __arm__
    // removed in iOS 4.1, it turns out __clear_cache had always been a nop
    // XXX: we should probably do something here... right?... right?!
#else
    __clear_cache(reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + size);
#endif
}
