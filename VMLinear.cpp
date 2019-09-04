#include "VMLinear.h"

#include <assert.h>
#include <inttypes.h>

#include "VirtualMemoryUtils.h"

static VMLinear::MemoryLinear gMemLinearContext;
VMLinear::VMLinear()
{
}

VMLinear::~VMLinear()
{
}

void VMLinear::Init()
{
    bool success = VmAllocate(g_LinearMemoryCapacity, &gMemLinearContext.pageAlloc);
    if (!success)
    {
        LOG_ERROR("Unable to allocate virtual memory.");
        assert(success);
    }

    gMemLinearContext.baseAddress = gMemLinearContext.pageAlloc.baseAddress;
    gMemLinearContext.currentAddress = gMemLinearContext.baseAddress;
    gMemLinearContext.usedByteSize = 0;

    m_CurrentLinear = &gMemLinearContext;
}

void* VMLinear::Alloc(size_t p_Size, uint32_t p_Alignment)
{
    const bool success = p_Size < g_LinearMemoryCapacity;
    if (!success)
    {
        LOG_ERROR("Unable to allocate a bigger buffer size than the available capacity.");
        assert(success);
        return nullptr;
    }

    p_Alignment = (p_Alignment < GFX_SYSTEM_DEFAULT_ALIGNMENT) ? GFX_SYSTEM_DEFAULT_ALIGNMENT : p_Alignment;
    void* memPtr = GFX_ALIGN_POINTER(m_CurrentLinear->currentAddress, p_Alignment);
    if (GFX_IS_VALID_RANGE(GFX_ADVANCE_POINTER_BY_OFFSET(memPtr, p_Size), m_CurrentLinear->baseAddress, GFX_ADVANCE_POINTER_BY_OFFSET(m_CurrentLinear->baseAddress, g_LinearMemoryCapacity)))
    {
        m_CurrentLinear->currentAddress = GFX_ADVANCE_POINTER_BY_OFFSET(memPtr, p_Size);
        m_CurrentLinear->usedByteSize += p_Size;
        return memPtr;
    }

    return nullptr;
}

void VMLinear::Reset()
{
    m_CurrentLinear->usedByteSize = 0;
    m_CurrentLinear->currentAddress = m_CurrentLinear->baseAddress;
}

size_t VMLinear::UsedSize()
{
    return m_CurrentLinear->usedByteSize;
}
