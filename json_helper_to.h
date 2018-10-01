#pragma once




#include <ostream>

#include <set>
#include <map>
#include <vector>
#include <deque>
#include <array>

#include <unordered_map>
#include <sstream>
#include <cstddef>

namespace cc64
{

namespace to_json_internal
{
        
template<typename> class to_json_forwarder;


//=====================================================================
// const: null, true, false
//

inline void json_encode_null (std::ostream& os)
{
    os<<"null";
}

inline void json_encode_true (std::ostream& os)
{
    os<<"true";
}

inline void json_encode_false (std::ostream& os)
{
    os<<"false";
}

inline void json_encode_string_begin (std::ostream& os)
{
    os<<"\"";
}

inline void json_encode_string_end (std::ostream& os)
{
    os<<"\"";
}

inline void json_encode_obj_begin (std::ostream& os)
{
    os<<"{";
}

inline void json_encode_obj_end (std::ostream& os)
{
    os<<"}";
}

inline void json_encode_array_begin (std::ostream& os)
{
    os<<"[";
}

inline void json_encode_array_end (std::ostream& os)
{
    os<<"]";
}

inline void json_encode_comma (std::ostream& os)
{
    os<<",";
}

inline void json_encode_colon (std::ostream& os)
{
    os<<":";
}

//=====================================================================
// basic structure
//

template<typename T>
inline void json_encode_as_string (std::ostream& os, const T & aT)
{
    json_encode_string_begin (os);
    os<<aT;
    json_encode_string_end (os);
}

template<typename T>
inline void json_encode_as_array (std::ostream& os, const T & aT)
{
    json_encode_array_begin (os);
    for (auto it = aT.begin(); it != aT.end(); ++it)
    {
        to_json_forwarder<typename std::decay < decltype(*it) > ::type>::call(os, *it);
        if (std::next(it) != aT.end()) json_encode_comma (os);
    }    
    json_encode_array_end (os);
}

template<typename T>
inline void json_encode_as_name_value (std::ostream& os, const std::string & a_name, const T & a_value)
{
    json_encode_as_string (os, a_name);
    json_encode_colon (os);
    to_json_forwarder<typename std::decay < decltype(a_value) > ::type>::call(os, a_value);
}

template<typename N, typename T>
inline void json_encode_as_name_value (std::ostream& os, const N & a_name, const T & a_value)
{
    std::ostringstream ot;
    to_json_forwarder<typename std::decay < decltype(a_name) > ::type>::call(ot,a_name);
    json_encode_as_name_value (os, ot.str(), a_value);
}


template<typename T> inline void json_encode_map(std::ostream& os, const T& t)
{
    json_encode_obj_begin (os);
    for (auto it = t.begin(); it != t.end(); ++it)
    {
        json_encode_as_name_value (os, it->first, it->second);
        if (std::next(it) != t.end()) json_encode_comma (os);
    }
    json_encode_obj_end (os);
}

//=====================================================================
// default encode for general types
//

template<typename T> inline void json_encode_as_pointer(std::ostream& os, const T& t)
{
    if (!t) {
        json_encode_null (os);
    } else {
        json_encode_obj_begin (os);
        to_json_forwarder<typename std::remove_pointer<T>::type>::call (os, *t);
        json_encode_obj_end (os);
    }
}



template<typename T>
inline
void do_default_json_encode(std::ostream& os, const T& t, std::false_type)
{
    try{
        os << t; /*T do not have to_json, thus try to use default stream*/
        return;
    }
    catch(...)
    {
    }
}

// pointer. 
template<typename T>
inline
void do_default_json_encode(std::ostream& os, const T& t, std::true_type)
{
    json_encode_as_pointer (os, t);
}



template<typename T> inline void json_encode(std::ostream& os, const T& t)
{
    return do_default_json_encode (os, t,typename std::is_pointer<T>::type{});
}


//=====================================================================
// predefined encode for specific
//


inline void json_encode(std::ostream& os, const std::string& t)
{
    json_encode_as_string (os, t);
}

inline void json_encode(std::ostream& os, const char* t)
{
    json_encode_as_string (os, t);
}

inline void json_encode(std::ostream& os, char t)
{
    char x[] = "b";
    x[0]=t;
    json_encode_as_string (os, x);
}



//=====================================================================
// default encode for container types
//

    

template<typename T> inline void json_encode(std::ostream& os, const std::vector<T>& t)
{
    json_encode_as_array(os, t);
}
template<typename T> inline void json_encode(std::ostream& os, const std::set<T>& t)
{
    json_encode_as_array(os, t);
}
template<typename T, size_t X> inline void json_encode(std::ostream& os, const std::array<T, X>& t)
{
    json_encode_as_array(os, t);
}
template<typename T> inline void json_encode(std::ostream& os, const std::deque<T>& t)
{
    json_encode_as_array(os, t);
}

template<typename T1, typename T2> inline void json_encode(std::ostream& os, const std::map<T1, T2>& t)
{
    json_encode_map(os, t);
}


    
template<typename T1, typename T2> inline void json_encode(std::ostream& os, const std::unordered_map<T1, T2>& t)
{
    json_encode_map(os, t);
}


//=====================================================================
// forwarder for type
//


template<typename T>
struct to_json_forwarder {
private:

#define FNAME has_to_json

#define FUNC_NAME to_json

#define PLIST()                                 \
    PLIST_ITEM (std::ostream&)

#define RET_TYPE void

#include "type_traits_helper/def_helper_class_func_callable_checker.h"

    //internal serialization
    static void call_inner(std::ostream&os, const T& t, std::true_type, std::false_type)
    {
        t.to_json(os);
    }
    //internal serialization
    static void call_inner(std::ostream&os, const T& t, std::false_type, std::true_type)
    {
        json_encode_as_pointer (os, t);
    }
    //internal serialization
    static void call_inner(std::ostream&os, const T& t, std::true_type, std::true_type)
    {
        t.to_json (os);
    }
    //external serialization
    static void call_inner(std::ostream&os, const T& t, std::false_type, std::false_type)
    {
        json_encode(os, t);
    }
public:
    static void call(std::ostream&os, const T& t)
    {
        call_inner(os, t, typename has_to_json<T>::callable{}, typename has_to_json<T>::pointer_callable{});
    }
};
    
} /* namespace to_json_internal*/

//=====================================================================
// public interface
//
    

template<typename T>
void to_json (std::ostream& os, const T& t)
{
    return to_json_internal::to_json_forwarder<T>::call (os, t);
}

template<typename T>
void to_json_key (std::ostream& os, const T& t)
{
    os<<t;
}


template<typename T>
std::string to_json_string (const T & aT)
{
    std::ostringstream ostr;
    to_json (ostr, aT);
    return ostr.str();
}


} /*namespace cc64*/


