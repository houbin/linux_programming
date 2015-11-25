#ifndef UTIL_MUTEX_H_
#define UTIL_MUTEX_H_
#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
#include "base_types.h"

namespace util {

class Mutex
{
public:
    Mutex(const char *name)
    {
        name_ = name;
#ifdef _WIN32
        InitializeCriticalSection(&m_critical_section_);
#else
        pthread_mutex_init(&m_, NULL);
#endif
    }

    ~Mutex()
    {
#ifdef _WIN32
        DeleteCriticalSection(&m_critical_section_);
#else
        pthread_mutex_destroy(&m_);
#endif
    }

    void Lock()
    {
#ifdef _WIN32
        EnterCriticalSection(&m_critical_section_);
#else
        pthread_mutex_lock(&m_);
#endif
    
    }
    void Unlock()
    {
#ifdef _WIN32
        LeaveCriticalSection(&m_critical_section_);
#else
        pthread_mutex_unlock(&m_);
#endif
    }

    friend class Cond;

    class Locker
    {
    private:
        Mutex &m_;

    public:
        Locker(Mutex& m) : m_(m) { m_.Lock(); }
        ~Locker() { m_.Unlock(); }
    };

private:
    const char *name_;
#ifdef _WIN32
    CRITICAL_SECTION m_critical_section_;
#else
    pthread_mutex_t m_;
#endif

    // no copying
    Mutex(const Mutex &);
    void operator=(const Mutex &);
};

}

#endif

