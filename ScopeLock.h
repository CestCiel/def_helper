#pragma once

#include "NonCopyable.h"
#include <cstddef>

namespace cc64
{


template<typename MutexType>
class ScopeLock : NonCopyable<ScopeLock<MutexType> >
{
public:
    ScopeLock(MutexType & aLock)
            : m_Lock(aLock)
    {
        m_Lock.lock();
    }

    ~ScopeLock()
    {
        m_Lock.unlock();
    }

private:
    MutexType & m_Lock;
};

template<typename MutexType>
class ScopeLockReleaser : NonCopyable<ScopeLockReleaser<MutexType> >
{
public:
    ScopeLockReleaser() : m_Lock(NULL)
    {
    }

    ~ScopeLockReleaser()
    {
        if (m_Lock) m_Lock->unlock();
    }

    bool has_lock() const { return m_Lock != NULL; }


    void set_lock(MutexType & aLock)
    {
        m_Lock = &aLock;
    }

private:
    MutexType *m_Lock;
};

}

#define SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(X)                           \
    int lock(X& a_releaser)                                             \
    {                                                                   \
        int ret = lock();                                               \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }                                                                   \
    int try_lock(X& a_releaser)                                          \
    {                                                                   \
        int ret = try_lock();                                            \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }/*                                                                   \
                                                                        \
    int timed_lock(cc64::ElapsedTime const & a_relative_time, X& a_releaser)   \
    {                                                                   \
        int ret = timed_lock(a_relative_time);                           \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }                                                                   \
    int abs_timed_lock(cc64::ElapsedTime const & a_absolute_time, X& a_releaser)   \
    {                                                                   \
        int ret = abs_timed_lock(a_absolute_time);                           \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }

     */







