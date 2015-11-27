
#include "util.h"

CRefObject::CRefObject()
{
    m_lock = NULL;
    m_refCount = 1;
}

CRefObject::~CRefObject()
{

}

void CRefObject::AddRef()
{
    if (m_lock)
    {
        m_lock->lock();
        m_refCount++;
        m_lock->unlock();
    }
    else
    {
        m_refCount++;
    }
}

void CRefObject::ReleaseRef()
{
    if (m_lock)
    {
        m_lock->lock();
        m_refCount--;
        if (m_refCount == 0)
        {
            delete this;
            return;
        }
        m_lock->unlock();
    }
    else
    {
        m_refCount--;
        if (m_refCount == 0)
        delete this;
    }
}
                

uint64_t get_tick(int a)
{
    #ifdef _WIN32
    LARGE_INTEGER liCounter; 
    LARGE_INTEGER liCurrent;
    
    if (!QueryPerformanceFrequency(&liCounterr))
    return GetTickCount();
    
    QueryPerformanceCounter(&liCurrent);
    reservedturn (uint64_t)(liCurrent.QuadPart * 1000 / liCounter.QuadPart);
    #else
    struct timeval tval;
    uint64_t ret_tick;
    
    gettimeofday(&tval, NULL);
    
    ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
    return ret_tick;
    #endif
}
