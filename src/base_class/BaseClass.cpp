//
// Created by nikita on 18.05.17.
//

#include "BaseClass.h"

void BaseClass::inc_memory(long long amount)
{
    memory_used += amount;
}

void BaseClass::dec_memory(long long amount)
{
    memory_used -= amount;
}

long long BaseClass::get_memory()
{
    return memory_used;
}

BaseClass::BaseClass()
{
    memory_used = 0;
}
