#include "Mini3D.h"

uint8_t** CMini3D::tempVertexBuffer;
float*    CMini3D::ambientRed;
float*    CMini3D::ambientGreen;
float*    CMini3D::ambientBlue;
int*      CMini3D::polyFlag;
int*      CMini3D::blendFlag;
int*      CMini3D::destBlendFlag;
int*      CMini3D::fogFlag;
int*      CMini3D::clipFlag;
float*    CMini3D::fogMin;
float*    CMini3D::fogMax;
float*    CMini3D::invFogMaxMin;

void CMini3D::patchFuncs()
{
    ambientRed = (float*)(gBase + 0x192CC3C);
    ambientGreen = (float*)(gBase + 0x192C404);
    ambientBlue = (float*)(gBase + 0x1934130);
    polyFlag = (int*)(gBase + 0x193412C);
    blendFlag = (int*)(gBase + 0x1934118);
    destBlendFlag = (int*)(gBase + 0x192C3FC);
    fogFlag = (int*)(gBase + 0x192CCF8);
    clipFlag = (int*)(gBase + 0x19333E4);
    fogMin = (float*)(gBase + 0x192D568);
    fogMax = (float*)(gBase + 0x1934120);
    invFogMaxMin = (float*)(gBase + 0x193494C);
    tempVertexBuffer = (uint8_t**)(gBase + 0x192C3F8);

    patchFunction(&CMini3D::alloc32, 0xD10B0);
    patchFunction(&CMini3D::disableBlend, 0xCEDF0);
    patchFunction(&CMini3D::enableBlend, 0xCEDE0);
    patchFunction(&CMini3D::enableFog, 0xCEDB0);
    patchFunction(&CMini3D::disableFog, 0xCEDD0);
    patchFunction(&CMini3D::setDestBlend, 0xCEAC0);
    patchFunction(&CMini3D::init, 0xD4790);
}

void CMini3D::setAmbientLight(float ambient)
{
    //CALL_FUNC(0xD0530);
}

void* CMini3D::alloc32(int size)
{

    if (size < 1 || size > 500000)
    {
        //gtfoSourceFile = "..\\engine\\MINI3D.CPP";
        //gtfoSourceLine = 0x19BA;
        CUtils::reallyGTFO("CMini3D::alloc32 - vertexCount=%d", size);
    } 

    void* newMem = malloc(size * 0x20 + 0x24);
    if (newMem == nullptr)
    {
        //gtfoSourceFile = "..\\engine\\MINI3D.CPP";
        //gtfoSourceLine = 0x19C8;
        CUtils::reallyGTFO("CMini3D::allocVertexBuffer - Allocation of %d vertex failed", size);
    }

    unsigned int temp = (unsigned int)newMem + 0x24 & 0xFFFFFFE0;
    *(unsigned int*) (temp-4) = size;
    *(unsigned char*)(temp-5) = temp - (unsigned int)newMem;

    return (void*)temp;
}

float CMini3D::getAmbientLight()
{
    return (*ambientRed + *ambientBlue + *ambientGreen) / 3.0f;
}

int CMini3D::init()
{
    printf("CMini3D::init\n");
    *tempVertexBuffer = (uint8_t*)alloc32(0x400);
    return 1;
}

void CMini3D::disableBlend()
{
    *blendFlag = false;
}

void CMini3D::enableBlend()
{
    *blendFlag = true;
}

void CMini3D::enableFog()
{
    *fogFlag = true;
}

void CMini3D::disableFog()
{
    *fogFlag = false;
}

void CMini3D::setDestBlend(int val)
{
    *destBlendFlag = val;

    //if (pAPIDLLsetDestBlend != nullptr)
    //{
    pAPIDLLsetDestBlend(val);
    //}
}

void CMini3D::pAPIDLLsetDestBlend(int val) 
{
    WRAP_JMPEAX(*(void**)(gBase + 0x1BB0EC8));
}