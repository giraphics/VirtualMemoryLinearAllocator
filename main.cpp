#pragma once

#include "VMLinear.h"
#include <memory>

class TestVMPool
{
public:
    TestVMPool()
    {
        m_MemoryPool = std::unique_ptr<VMLinear>(new VMLinear());
    }

    ~TestVMPool()
    {
    }

private:
    std::unique_ptr<VMLinear> m_MemoryPool = nullptr;
};

int main()
{
    //TODO write the test here
    return 0;
}
