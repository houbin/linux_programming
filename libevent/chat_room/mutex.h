#ifndef UTIL_MUTEX_H_
#define UTIL_MUTEX_H_

#include <assert.h>
#include <pthread.h>

namespace util
{

class Mutex
{
private:
    const char *name_;
    pthread_mutex_t m_;

    // no copying allowed
    Mutex(const Mutex &);
    void operator=(const Mutex &);

public:
    friend class Cond;

    Mutex(const char *name) : name_(name)
    {
        int r = 0;
        r = pthread_mutex_init(&m_, NULL);
        assert(r == 0);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&m_);
    }

    void Lock()
    {
        int r = pthread_mutex_lock(&m_);
        assert(r == 0);
    }

    void Unlock()
    {
        int r = pthread_mutex_unlock(&m_);
        assert(r == 0);
    }

    class Locker
    {
    private:
        Mutex &mutex_;
    
    public:
        Locker(Mutex &mutex) : mutex_(mutex)
        {
            mutex_.Lock();
        }

        ~Locker()
        {
            mutex_.Unlock();
        }
    };
};

}
#endif
