#pragma once

#include <windows.h>
#include <stdint.h>

#define WRAP_FUNC __attribute__((naked))
#define MOV_EAX 0xB8
#define JMPEAX 0xFF
#define JMPEAX2 0xE0
#define CALLEAX 0xFF
#define CALLEAX2 0xD0
#define WRAP_JMPEAX(a) asm volatile("movl %[funcPtr], %%eax;" "jmp *%%eax;" :: [funcPtr] "g" (a))

inline uint32_t gBase;

inline void writeByte(uint32_t address, uint8_t dat)
{
	*((uint8_t*)address) = dat;
}

inline void writeInt(uint32_t address, uint32_t dat)
{
	*((uint32_t*)address) = dat;
}

inline void nopSection(uint32_t address, uint32_t length)
{
    for (int i = 0; i < length; i++)
    {
        writeByte(address + i, 0x90);
    }
}

enum
{
	PATCH_CALL,
	PATCH_JUMP,
	PATCH_NOTHING,
};

template<typename AT, typename HT> inline void
InjectHook(AT address, HT hook, unsigned int nType=PATCH_NOTHING)
{
	DWORD		dwProtect[2];
	switch ( nType )
	{
	case PATCH_JUMP:
		VirtualProtect((void*)address, 6, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		*(BYTE*)address = 0xE9;
		break;
	case PATCH_CALL:
		VirtualProtect((void*)address, 6, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		*(BYTE*)address = 0xE8;
		break;
	default:
		VirtualProtect((void*)((DWORD)address + 1), 4, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
		break;
	}
	DWORD		dwHook;

    asm(
        "movl %[hook], %%eax;"
        "movl %%eax, %[dwHook];"
        : [dwHook] "=g" (dwHook)
        : [hook] "g" (hook)
    );

	*(ptrdiff_t*)((DWORD)address + 1) = (DWORD)dwHook - (DWORD)address - 5;
    *(uint8_t*)((DWORD)address + 5) = 0xC3;
	if ( nType == PATCH_NOTHING )
		VirtualProtect((void*)((DWORD)address + 1), 4, dwProtect[0], &dwProtect[1]);
	else
		VirtualProtect((void*)address, 6, dwProtect[0], &dwProtect[1]);
}

template<typename T>
inline void** getVTable(T* obj)
{
    return *((void***)obj);
}

inline void patchSecurityCookie(uint32_t initAddress, uint32_t checkAddress)
{
    DWORD old;
    DWORD fixedAddress = gBase + initAddress;

    //Init cookie
    VirtualProtect((LPVOID)fixedAddress, 2, PAGE_EXECUTE_READWRITE, &old);
    writeByte(fixedAddress, 0xF3);
    writeByte(fixedAddress + 1, 0xC3);
    VirtualProtect((LPVOID)fixedAddress, 2, old, nullptr);


    //Check cookie
    fixedAddress = gBase + checkAddress;
    VirtualProtect((LPVOID)fixedAddress, 6, PAGE_EXECUTE_READWRITE, &old);
    writeByte(fixedAddress, 0xF3);
    writeByte(fixedAddress + 1, 0xC3);
    nopSection(fixedAddress + 2, 4);
    VirtualProtect((LPVOID)fixedAddress, 6, old, nullptr);
}

template<typename FUNC>
inline void patchFunction(FUNC function, uint32_t address, uint32_t nopCount = 0)
{
    DWORD old;

    DWORD fixedFunc;
    /*asm(
        ".intel_syntax;"
        "mov eax, %1;"
        "mov %0, eax;"
        ".att_syntax;"
        : "=r"(fixedFunc)
        : "r"(function)
    );*/

    asm(
        "movl %[newFunc], %%eax;"
        "movl %%eax, %[fixed];"
        : [fixed] "=g" (fixedFunc)
        : [newFunc] "g" (function)
        : "eax"
    );

   
    DWORD fixedAddress = gBase + address;
    VirtualProtect((LPVOID)fixedAddress, 7 + nopCount, PAGE_EXECUTE_READWRITE, &old);

    writeByte(fixedAddress, MOV_EAX);
    writeInt(fixedAddress + 1, fixedFunc);
    writeByte(fixedAddress + 5, JMPEAX);
    writeByte(fixedAddress + 6, JMPEAX2);

    if (nopCount > 0)
    {
        nopSection(fixedAddress + 7, nopCount);
    }

    VirtualProtect((LPVOID)fixedAddress, 7 + nopCount, old, nullptr);
}