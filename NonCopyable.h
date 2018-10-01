#pragma once


namespace cc64
{


template<class T>
class NonCopyable
{
protected:
    NonCopyable() { }

    ~NonCopyable() { }

private:
    NonCopyable(const NonCopyable &);

    NonCopyable & operator=(const NonCopyable &);

};


} /*namespace cc64*/

