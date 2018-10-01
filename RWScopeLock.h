#pragma once

#include "NonCopyable.h"

namespace cc64
{

template<typename MutexType>
class ReadScopeLock : NonCopyable<ReadScopeLock<MutexType> >
{
public:
    ReadScopeLock(MutexType & aLock)
            : m_Lock(aLock)
    {
        m_Lock.read_lock();
    }

    ~ReadScopeLock()
    {
        m_Lock.read_unlock();
    }

private:
    MutexType & m_Lock;
};


template<typename MutexType>
class ReadScopeLockReleaser : NonCopyable<ReadScopeLockReleaser<MutexType> >
{
public:
    ReadScopeLockReleaser()
            : m_Lock(NULL) { }

    ~ReadScopeLockReleaser()
    {
        if (m_Lock) m_Lock->read_unlock();
    }

    bool has_lock() const { return m_Lock != NULL; }

    void set_lock(MutexType & aLock)
    {
        m_Lock = &aLock;
    }

private:
    MutexType *m_Lock;
};


template<typename MutexType>
class WriteScopeLock : NonCopyable<WriteScopeLock<MutexType> >
{
public:
    WriteScopeLock(MutexType & aLock)
            : m_Lock(aLock)
    {
        m_Lock.write_lock();
    }

    ~WriteScopeLock()
    {
        m_Lock.write_unlock();
    }

private:
    MutexType & m_Lock;
};


template<typename MutexType>
class WriteScopeLockReleaser : NonCopyable<WriteScopeLockReleaser<MutexType> >
{
public:
    WriteScopeLockReleaser()
            : m_Lock(NULL)
    {
    }

    ~ WriteScopeLockReleaser()
    {
        if (m_Lock) m_Lock->write_unlock();
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

#define READ_SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(X)                      \
    int read_lock(X& a_releaser)                                         \
    {                                                                   \
        int ret = read_lock();                                           \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }                                                                   \
    int try_read_lock(X& a_releaser)                                      \
    {                                                                   \
        int ret = try_read_lock();                                        \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }/*                                                                   \
                                                                        \
    int read_timed_lock(cc64::ElapsedTime const & a_relative_time, X& a_releaser) \
    {                                                                   \
        int ret = read_timed_lock(a_relative_time);                       \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }                                                                   \
    int read_abs_timed_lock(cc64::ElapsedTime const & a_absolute_time, X& a_releaser) \
    {                                                                   \
        int ret = read_abs_timed_lock(a_absolute_time);                       \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }
     */

#define WRITE_SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(X)                     \
    int write_lock(X& a_releaser)                                        \
    {                                                                   \
        int ret = write_lock();                                          \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }                                                                   \
    int try_write_lock(X& a_releaser)                                     \
    {                                                                   \
        int ret = try_write_lock();                                       \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    } /*                                                                  \
    int write_timed_lock(cc64::ElapsedTime const & a_relative_time, X& a_releaser) \
    {                                                                   \
        int ret = write_timed_lock(a_relative_time);                      \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }                                                                   \
    int write_abs_timed_lock(cc64::ElapsedTime const & a_absolute_time, X& a_releaser) \
    {                                                                   \
        int ret = write_abs_timed_lock(a_absolute_time);                      \
        if (0 == ret) a_releaser.set_lock(*this);                       \
        return ret;                                                     \
    }
      */


