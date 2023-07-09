#pragma once

#include "../patcher.h"
#include "Utils.h"

extern uint32_t* gScratchMemoryStackPtr;
extern uint32_t** gScratchMemory;

void scratchPatchFuncs();

//These could be wrong...
void* pushScratchMemory(uint32_t size);
void popScratchMemory(uint32_t size);