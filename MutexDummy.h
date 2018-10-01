#pragma once

#include "ScopeLock.h"
#include "RWScopeLock.h"

#include "NonCopyable.h"

namespace cc64
{

class MutexDummy
{
public:

    typedef MutexDummy Type;

    typedef ScopeLock <Type> ScopeLockType;

    typedef ReadScopeLock <Type> ReadScopeLockType;

    typedef WriteScopeLock <Type> WriteScopeLockType;

    typedef ScopeLockReleaser <Type> ScopeLockReleaserType;

    typedef ReadScopeLockReleaser <Type> ReadScopeLockReleaserType;

    typedef WriteScopeLockReleaser <Type> WriteScopeLockReleaserType;

    inline int unlock() { return 0; }

    inline int lock() { return 0; }

    inline int try_lock() { return 0; }

    //inline int timed_lock(ElapsedTime const & a_relative_time) { return 0; }

    //inline int timed_till_lock(ElapsedTime const & a_relative_time) { return 0; }

    //inline int abs_timed_lock(ElapsedTime const & a_absolute_time) { return 0; }

    //inline int abs_timed_till_lock(ElapsedTime const & a_absolute_time) { return 0; }


    inline int read_unlock() { return unlock(); }

    inline int read_lock() { return lock(); }

    inline int try_read_lock() { return try_lock(); }

    //inline int read_timed_lock(ElapsedTime const & a_relative_time) { return timed_lock(a_relative_time); }

    //inline int read_timed_till_lock(ElapsedTime const & a_relative_time) { return timed_till_lock(a_relative_time); }

    //inline int read_abs_timed_lock(ElapsedTime const & a_absolute_time) { return timed_lock(a_absolute_time); }

    //inline int read_abs_timed_till_lock(ElapsedTime const & a_absolute_time) { return timed_till_lock(a_absolute_time); }



    inline int write_unlock() { return unlock(); }

    inline int write_lock() { return lock(); }

    inline int try_write_lock() { return try_lock(); }

    //inline int write_timed_lock(ElapsedTime const & a_relative_time) { return timed_lock(a_relative_time); }

    //inline int write_timed_till_lock(ElapsedTime const & a_relative_time) { return timed_till_lock(a_relative_time); }

    //inline int write_abs_timed_lock(ElapsedTime const & a_absolute_time) { return timed_lock(a_absolute_time); }

    //inline int write_abs_timed_till_lock(ElapsedTime const & a_absolute_time) { return timed_till_lock(a_absolute_time); }


    SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(ScopeLockReleaserType);

    READ_SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(ReadScopeLockReleaserType);

    WRITE_SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(WriteScopeLockReleaserType);


};


class MutexDummyNonCopyable : protected NonCopyable<MutexDummyNonCopyable>
{
public:

    typedef MutexDummyNonCopyable Type;

    typedef ScopeLock <Type> ScopeLockType;

    typedef ReadScopeLock <Type> ReadScopeLockType;

    typedef WriteScopeLock <Type> WriteScopeLockType;

    typedef ScopeLockReleaser <Type> ScopeLockReleaserType;

    typedef ReadScopeLockReleaser <Type> ReadScopeLockReleaserType;

    typedef WriteScopeLockReleaser <Type> WriteScopeLockReleaserType;


    inline int unlock() { return 0; }

    inline int lock() { return 0; }

    inline int try_lock() { return 0; }

    //inline int timed_lock(ElapsedTime const & a_relative_time) { return 0; }

    //inline int abs_timed_lock(ElapsedTime const & a_absolute_time) { return 0; }


    inline int read_unlock() { return unlock(); }

    inline int read_lock() { return lock(); }

    inline int try_read_lock() { return try_lock(); }

    //inline int read_timed_lock(ElapsedTime const & a_relative_time) { return timed_lock(a_relative_time); }

    //inline int read_abs_timed_lock(ElapsedTime const & a_absolute_time) { return timed_lock(a_absolute_time); }


    inline int write_unlock() { return unlock(); }

    inline int write_lock() { return lock(); }

    inline int try_write_lock() { return try_lock(); }

    //inline int write_timed_lock(ElapsedTime const & a_relative_time) { return timed_lock(a_relative_time); }

    //inline int write_abs_timed_lock(ElapsedTime const & a_absolute_time) { return timed_lock(a_absolute_time); }


    SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(ScopeLockReleaserType);

    READ_SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(ReadScopeLockReleaserType);

    WRITE_SCOPE_LOCK_RELEASER_SUPPORT_DEFINE(WriteScopeLockReleaserType);
};


} /* namespace cc64*/
