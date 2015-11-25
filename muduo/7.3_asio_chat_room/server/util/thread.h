#ifndef UTIL_THREAD_H_
#define UTIL_THREAD_H_

#ifdef _WIN32
#define <windows.h>
#else
#include <pthread.h>
#endif
#include "base_types.h"
#include <stdlib.h>
#include <assert.h>

namespace util
{

class Thread
{
public:
    Thread() : thread_id_(0) { }
    virtual ~Thread()
    {
#ifdef _WIN32
        if (thread_id_ != 0)
        {
            CloseHandle(thread_id_);
            thread_id_ = 0;
        }
#endif
    }

    bool IsStarted() const
    {
        return (thread_id_ != 0);
    }

    void Create(size_t stack_size = 0)
    {
    
#ifdef _WIN32
        DWORD dw_thread;
        thread_id_ = CreateThread(NULL, 0, &EntryWrap, this, 0, &dw_thread);
        if (thread_id_ == 0)
        {
            assert("CreateThread error" == 0);
        }
#else
        int ret = 0;
        pthread_attr_t *attr = NULL;
        if (stack_size != 0)
        {
            attr = (pthread_attr_t *)malloc(sizeof(pthread_attr_t));
            if (attr == NULL)
            {
                assert("malloc error" == 0);
            }

            pthread_attr_init(attr);
            pthread_attr_setstacksize(attr, stack_size);
        }

        ret = pthread_create(&thread_id_, attr, &EntryWrap, this);
        if (ret != 0)
        {
            assert("pthread_create error" == 0);
        }

        if (attr != NULL)
        { 
            free(attr); 
        }
#endif

        return;
    }

    int Join(void **retval = 0)
    {
        int32_t ret = 0;

        if (thread_id_ == 0)
        {
            assert("join on thread that was never started" == 0);
            return -1;
        }

#ifdef _WIN32
        ret = WaitForSingleObject(thread_id_, INFINITE);
        if (thread_id_ != 0)
        {
            CloseHandle(thread_id_);
        }
#else
        ret = pthread_join(thread_id_, retval);
        assert(ret == 0);
#endif

        thread_id_ = 0;
        return 0;
    }

    virtual void* Entry() = 0;

    static void *EntryWrap(void *arg)
    {
        void *r = ((Thread *)arg)->Entry();
        return r;
    }

private:
#ifdef _WIN32
    HANDLE thread_id_;
#else
    pthread_t thread_id_;
#endif
};

}

#endif

