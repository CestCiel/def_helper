#pragma once



#include <ostream>

#include <set>
#include <map>
#include <vector>
#include <deque>
#include <array>

#include <unordered_map>

#include <cstddef>
#include <cstring>
#include <type_traits>

namespace cc64
{

namespace estimate_mem_size_internal
{
        
template<typename> class estimate_mem_size_forwarder;


//=====================================================================
// const: null, true, false
//

inline size_t estimate_in_memory_size_pointer()
{
    return sizeof(nullptr);
}
    

//=====================================================================
// basic structure
//


template<typename T>
inline size_t estimate_in_memory_size_as_array (const T & aT)
{
    size_t ret = sizeof(aT);
    
    for (auto it = aT.begin(); it != aT.end(); ++it)
    {
        ret += estimate_mem_size_forwarder<typename std::decay < decltype(*it) > ::type>::call(*it);
    }    
    return ret;
    
}


template<typename N, typename T>
inline size_t estimate_in_memory_size_as_name_value (const N & a_name, const T & a_value)
{
    return estimate_mem_size_forwarder<typename std::decay < decltype(a_value) > ::type>::call(a_value) +
        estimate_mem_size_forwarder<typename std::decay < decltype(a_name) > ::type>::call(a_name);
}


template<typename T>
inline size_t estimate_in_memory_size_map(const T& t)
{
    size_t ret = sizeof(t);
    for (auto it = t.begin(); it != t.end(); ++it)
    {
        ret += estimate_in_memory_size_as_name_value (it->first, it->second);
    }
    return ret;
}

//=====================================================================
// default encode for general types
//

template<typename T>
inline size_t estimate_in_memory_size_as_pointer(const T& t)
{
    if (!t) {
        return sizeof(T);
    } else {
        return sizeof(T) + 
            estimate_mem_size_forwarder<typename std::remove_pointer<T>::type>::call (*t);
    }
}



template<typename T>
inline
size_t do_default_estimate_in_memory_size(const T& t, std::false_type)
{
    return sizeof(T);
}

// pointer. 
template<typename T>
inline
size_t do_default_estimate_in_memory_size(const T& t, std::true_type)
{
    return estimate_in_memory_size_as_pointer (t);
}



template<typename T> inline size_t estimate_in_memory_size( const T& t)
{
    return do_default_estimate_in_memory_size (t,typename std::is_pointer<T>::type{});
}


//=====================================================================
// predefined encode for specific
//


inline size_t estimate_in_memory_size(const std::string& t)
{
    return sizeof(t) + t.length() * sizeof(std::string::value_type);
}

inline size_t estimate_in_memory_size(const char* t)
{
    return strlen (t) * sizeof(char);
}



//=====================================================================
// default encode for container types
//


template<typename T>
inline size_t estimate_in_memory_size(const std::vector<T>& t)
{
    return estimate_in_memory_size_as_array(t);
}
template<typename T>
inline size_t estimate_in_memory_size(const std::set<T>& t)
{
    return estimate_in_memory_size_as_array(t);
}
template<typename T, size_t X>
inline size_t estimate_in_memory_size(const std::array<T, X>& t)
{
    return estimate_in_memory_size_as_array(t);
}
    
template<typename T> inline
size_t estimate_in_memory_size(const std::deque<T>& t)
{
    return estimate_in_memory_size_as_array(t);
}

template<typename T1, typename T2>
inline size_t estimate_in_memory_size(const std::map<T1, T2>& t)
{
    return estimate_in_memory_size_map(t);
}


    
template<typename T1, typename T2>
inline size_t estimate_in_memory_size(const std::unordered_map<T1, T2>& t)
{
    return estimate_in_memory_size_map(t);
}


//=====================================================================
// forwarder for type
//


template<typename T>
struct estimate_mem_size_forwarder {
private:

#define FNAME has_estimate_mem_size

#define FUNC_NAME estimate_mem_size

#define PLIST()

#define RET_TYPE size_t

#include "type_traits_helper/def_helper_class_func_callable_checker.h"

    //internal serialization
    static size_t call_inner(const T& t, std::true_type, std::false_type)
    {
        return t.estimate_mem_size();
    }
    //internal serialization
    static size_t call_inner(const T& t, std::false_type, std::true_type)
    {
        return estimate_in_memory_size_as_pointer (t);
    }
    //internal serialization
    static size_t call_inner(const T& t, std::true_type, std::true_type)
    {
        return t.estimate_mem_size ();
    }
    //external serialization
    static size_t call_inner(const T& t, std::false_type, std::false_type)
    {
        return estimate_in_memory_size(t);
    }
public:
    static size_t call(const T& t)
    {
        return call_inner(t, typename has_estimate_mem_size<T>::callable{}, typename has_estimate_mem_size<T>::pointer_callable{});
    }
};
    
} /* namespace estimate_mem_size_internal*/

//=====================================================================
// public interface
//
    

template<typename T>
size_t estimate_mem_size (const T& t)
{
    return estimate_mem_size_internal::estimate_mem_size_forwarder<T>::call (t);
}


} /*namespace cc64*/


