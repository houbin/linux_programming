#ifndef UTIL_COND_H_
#define UTIL_COND_H_

#include <pthread.h>
#include "mutex.h"
#include "utime.h"

namespace util
{

class Cond
{
private:
    pthread_cond_t c_;
    Mutex *mutex_;

    // no copying allowed
    Cond(const Cond &);
    void operator=(const Cond &);

public:
    Cond()
    {
        pthread_cond_init(&c_, NULL);
    }

    ~Cond()
    {
        pthread_cond_destroy(&c_);
    }

    void Wait(Mutex *mutex)
    {
        assert(mutex_ == NULL || mutex_ == mutex);
        if (mutex_ == NULL)
        {
            mutex_ = mutex;
        }

        int r = pthread_cond_wait(&c_, &(mutex_->m_));
        assert(r == 0);
    }

    void WaitUtil(Mutex *mutex, UTime time)
    {
        assert(mutex_ == NULL || mutex_ == mutex);
        if (mutex_ == NULL)
        {
            mutex_ = mutex;
        }

        struct timespec time_spec;
        time.ToTimeSpec(&time_spec);

        int r = pthread_cond_timedwait(&c_, &(mutex_->m_), &time_spec);
        assert(r == 0);
    }

    void WaitAfter(Mutex *mutex, UTime time)
    {
        assert(mutex_ == NULL || mutex_ == mutex);
        if (mutex_ == NULL)
        {
            mutex_ = mutex;
        }

        UTime when = GetClockNow();
        when += time;

        WaitUtil(mutex_, when);
    }

    void Signal()
    {
        pthread_cond_signal(&c_);
    }

    void SignalAll()
    {
        pthread_cond_broadcast(&c_);
    }
};

}

#endif
