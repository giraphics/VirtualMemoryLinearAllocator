#pragma once

#include <stdint.h>
#include <stddef.h>

#include "VirtualMemory.h"
#include "VirtualMemoryLinearConfig.h"

class VMLinear : public VirtualMemory
{
public:
    VMLinear();
    virtual ~VMLinear();

    void Init();

    void* Alloc(size_t p_Size, uint32_t p_Alignment);
    void Reset();
    size_t UsedSize();

public:
    struct MemoryLinear
    {
        PageAllocation pageAlloc;

        void* baseAddress    = nullptr;
        void* currentAddress = nullptr;

        size_t usedByteSize = 0;
    } ;

    MemoryLinear* m_CurrentLinear = nullptr;
};
