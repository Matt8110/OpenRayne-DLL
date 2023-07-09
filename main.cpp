#include <windows.h>
#include <iostream>
#include "patcher.h"
#include "core/Actor.h"
#include "core/Character.h"
#include "engine/Mini3D.h"
#include "core/PortalSet.h"
#include "engine/BitFont.h"
#include "core/Barrier.h"
#include "core/Mission.h"
#include "core/Set.h"
#include "core/Particle.h"
#include "engine/Scratch.h"

BOOL WINAPI DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        AllocConsole();

        gBase = (uint32_t) GetModuleHandle("rayne1.exe");

        scratchPatchFuncs();
        CDemonSet::patchFuncs();
        CDemonMission::patchFuncs();
        CPortalSet::patchFuncs();
        CDemonActor::patchFuncs();
        CCharacter::patchFuncs();
        CBitFont::patchFuncs();
        CMini3D::patchFuncs();
        CBarrier::patchFuncs();
        CDemonParticle::patchFuncs();
    }
    return true;
}