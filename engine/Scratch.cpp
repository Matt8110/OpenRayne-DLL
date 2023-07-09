#include "Scratch.h"

uint32_t* gScratchMemoryStackPtr;
uint32_t** gScratchMemory;

void scratchPatchFuncs()
{
    gScratchMemoryStackPtr = (uint32_t*)(gBase + 0x1A45748);
    gScratchMemory = (uint32_t**)(gBase + 0x1A45740);

    patchFunction(&pushScratchMemory, 0x109FA0);
    patchFunction(&popScratchMemory, 0x10A000);
}

void* pushScratchMemory(uint32_t size)
{
    uint32_t* tempStackPtr = gScratchMemoryStackPtr;
    *gScratchMemoryStackPtr = *gScratchMemoryStackPtr + (size + 0xF & 0xFFFFFFF0);
    if (*gScratchMemory + 0x3800 < gScratchMemoryStackPtr)
    {
        CUtils::reallyGTFO("pushScratchMemory - stack overflow");
    }

    return tempStackPtr;
}

void popScratchMemory(uint32_t size)
{
    *gScratchMemoryStackPtr = *gScratchMemoryStackPtr - (size + 0xF & 0xFFFFFFF0);
    if ((uint32_t*)*gScratchMemoryStackPtr < *gScratchMemory)
    {
        CUtils::reallyGTFO("popScratchMemory - stack imbalance");
    }
}