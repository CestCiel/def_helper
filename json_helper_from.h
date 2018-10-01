#pragma once



#include <ostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <array>

#include <unordered_map>

#include <sstream>
#include <cstddef>

#include <type_traits>

namespace cc64
{

namespace from_json_internal
{
        
template<typename> class from_json_forwarder;


//=====================================================================
// const: null, true, false
//

inline void json_decode_skip_space (std::istream & is)
{
    is>>std::ws;
}

inline bool skip_fixed_key (std::istream & is,
                            std::string const & a_key,
                            bool skip_space=true)
{
    if (skip_space) is>>std::ws;

    size_t len = a_key.length();
    char * buff = new char[len+1];
    is.get (buff, len+1);


    bool ret = false;
    if (((size_t)is.gcount() == len) && (a_key == buff))
    {
        ret = true;
    } 
    delete [] buff;
    
    return ret;
}

inline
bool peek_next(std::istream& is, char P, bool skip_space = true)
{
    if (skip_space) is>>std::ws;
    int next;
    try{
        next = is.peek();
        if (next == P) return true;
    }
    catch (...)
    {
        return false;
    }
    return false;
}


//=====================================================================
// field detector
//

inline
bool is_string_end (std::istream & is)
{
    return peek_next (is,'"',false);
}
    
inline
bool is_obj_end_eating_spaces (std::istream& is)
{
    return peek_next (is, '}', true);
}

inline
bool is_array_end_eating_spaces (std::istream& is)
{
    return peek_next (is, ']', true);
}

inline
bool is_null_eating_spaces (std::istream& is)
{
    return peek_next (is, 'n', true);
}

inline
bool is_true_eating_spaces (std::istream& is)
{
    return peek_next (is, 't', true);
}

inline
bool is_false_eating_spaces (std::istream& is)
{
    return peek_next (is, 'f', true);
}

//=====================================================================
// basic structure
//

inline
bool json_decode_null (std::istream & is)
{
    return skip_fixed_key (is, "null",true);
} 

inline
bool json_decode_true (std::istream & is)
{
    return skip_fixed_key (is, "true",true);
}
   
inline
bool json_decode_false (std::istream & is)
{
    return skip_fixed_key (is, "false",true);
}
    
inline
bool json_decode_string_begin (std::istream & is)
{
    return skip_fixed_key (is, "\"", true);
}

inline
bool json_decode_string_end (std::istream & is)
{
    return skip_fixed_key (is, "\"", true);
}

inline
bool json_decode_obj_begin (std::istream & is)
{
    return skip_fixed_key (is, "{", true);
}

inline
bool json_decode_obj_end (std::istream & is)
{
    return skip_fixed_key (is, "}", true);
}

inline
bool json_decode_array_begin (std::istream & is)
{
    return skip_fixed_key (is, "[", true);
}

inline
bool json_decode_array_end (std::istream & is)
{
    return skip_fixed_key (is, "]", true);
}

inline
bool json_decode_comma (std::istream & is)
{
    return skip_fixed_key (is, ",", true);
}

inline
bool json_decode_colon (std::istream & is)
{
    return skip_fixed_key (is, ":", true);
}
    
//=====================================================================
// basic structure
//
    
inline bool json_decode_as_string(std::istream& is, std::string& t)
{
    if (!json_decode_string_begin (is)) return false;


    if (!is_string_end (is))
    {
        try{
            std::stringbuf x;
            is.get (x,'"');
            t=x.str();
        }
        catch(...)
        {
            return false;
        }
    } else {
        t.clear();
    }
    return json_decode_string_end (is);
}


template<typename T>
inline
bool json_decode_as_array(std::istream & is, T& t)
{
    if (!json_decode_array_begin (is)) return false;

    size_t c = 0;
    while(! is_array_end_eating_spaces (is))
    {
        if (c && (!json_decode_comma (is))) return false;

        typedef typename std::decay < decltype(t) > ::type::value_type vType;
        vType tmp;
        if (!from_json_forwarder<vType>::call(is, tmp)) return false;
        t.insert (t.end(),tmp);
        c++;
    }
    return json_decode_array_end (is);
}

template<typename T>
inline
bool json_decode_as_name_value(std::istream& is, std::string& a_name, T&a_value)
{
    return json_decode_as_string (is, a_name) &&
        json_decode_colon (is) &&
        from_json_forwarder<typename std::decay < decltype(a_value) > ::type>::call(is,a_value);
}

template<typename N, typename T>
inline
bool json_decode_as_name_value(std::istream& is, N& a_name, T&a_value)
{
    std::string tmp;
    if (!json_decode_as_name_value (is, tmp, a_value)) return false;
    std::istringstream itmp (tmp);
    return from_json_forwarder<typename std::decay < decltype(a_name) > ::type>::call(itmp,a_name);
}



template<typename T>
inline bool json_decode_map(std::istream & is, T& t)
{
    if (!json_decode_obj_begin (is)) return false;
    
    size_t c = 0;
    while(!is_obj_end_eating_spaces (is))
    {
        if (c && (!json_decode_comma (is))) return false;
        
        typedef typename std::decay < decltype(t) > ::type::key_type kType;
        kType key;
        typedef typename std::decay < decltype(t) > ::type::mapped_type mType;
        mType mapped;

        if (!json_decode_as_name_value (is, key, mapped)) return false;

        typedef typename std::decay < decltype(t) > ::type::value_type vType;
        t.insert (t.end(),vType (key,mapped));
        c++;
    }
    return json_decode_obj_end (is);
}




//=====================================================================
// default encode for general types
//

template<typename T>
inline bool json_decode_as_pointer(std::istream & is, T& t)
{
    if (!t)
    {
        return json_decode_null(is);
    } else {
        return json_decode_obj_begin (is)  &&
            from_json_forwarder<typename std::remove_pointer<T>::type>::call (is, *t) &&
            json_decode_obj_end (is);
    }
}
    
    
template<typename T>
inline
bool do_default_json_decode(std::istream& is, T& t, std::false_type)
{
    try{
        is>> t;
    }
    catch (...)
    {
        return false;
    }
    return is.good() || is.eof();
}

// pointer. 
template<typename T>
inline
bool do_default_json_decode(std::istream& is, T& t, std::true_type)
{
    if (!t)
    {
        if(json_decode_null(is)) return true;
        return false;
    }
    
    return json_decode_obj_begin (is) &&
        from_json_forwarder<typename std::remove_pointer<T>::type>::call (is, *t) &&
        json_decode_obj_end (is);
}

    
template<typename T> inline bool json_decode(std::istream& is, T& t)
{
    return do_default_json_decode (is, t, typename std::is_pointer<T>::type{});
}


//=====================================================================
// predefined encode for specific
//
inline bool json_decode(std::istream& is, std::string& t)
{
    return json_decode_as_string (is, t);
}



inline bool json_decode(std::istream& is, char & t)
{
    std::string tmp;
    if (!json_decode (is, tmp)) return false;
    if (tmp.length()<1) return true;
    t=tmp.front();
    return true;
}


inline bool json_decode(std::istream& is, char* t)
{
    return false;
}


//=====================================================================
// default encode for container types
//
template<typename T> inline bool json_decode(std::istream & is, std::vector<T>& t)
{
    return json_decode_as_array(is, t);
}
template<typename T> inline bool json_decode(std::istream & is, std::set<T>& t)
{
    return json_decode_as_array(is, t);
}
template<typename T, size_t X> inline bool json_decode(std::istream & is, std::array<T, X>& t)
{
    return json_decode_as_array(is, t);
}
template<typename T> inline bool json_decode(std::istream & is, std::deque<T>& t)
{
    return json_decode_as_array(is, t);
}

template<typename T1, typename T2> inline bool json_decode(std::istream & is, std::map<T1, T2>& t)
{
    return json_decode_map(is, t);
}

template<typename T1, typename T2> inline bool json_decode(std::istream & is, std::unordered_map<T1, T2>& t)
{
    return json_decode_map(is, t);
}



//=====================================================================
// forwarder for type
//


template<typename T>
struct from_json_forwarder {
private:

#define FNAME has_from_json

#define FUNC_NAME from_json

#define PLIST()                                 \
    PLIST_ITEM (std::istream&)

#define RET_TYPE bool

#include "type_traits_helper/def_helper_class_func_callable_checker.h"

    //internal deserialization
    static bool call_inner(std::istream&is, T& t, std::true_type, std::false_type)
    {
        return t.from_json(is);
    }
    //internal deserialization
    static bool call_inner(std::istream&is, T& t, std::false_type, std::true_type)
    {
        return json_decode_as_pointer (is, t);
    }
    //internal deserialization
    static bool call_inner(std::istream&is, T& t, std::true_type, std::true_type)
    {
        return t.from_json (is);
    }
    //external deserialization
    static bool call_inner(std::istream&is, T& t, std::false_type, std::false_type)
    {
        return json_decode(is, t);
    }
public:
    static bool call(std::istream&is, T& t)
    {
        return call_inner(is, t, typename has_from_json<T>::callable{}, typename has_from_json<T>::pointer_callable{});
    }
};
    
} /* namespace from_json_internal*/

    
//=====================================================================
// public interface
//
    

template<typename T>
bool from_json (std::istream& is, T& t)
{
    return from_json_internal::from_json_forwarder<T>::call (is, t);
}

inline
bool from_json_skip_key (std::istream& is, std::string const & t)
{
    return from_json_internal::skip_fixed_key (is, t);
}

inline
bool from_json_skip_strkey (std::istream& is, std::string const & t)
{
    return from_json_skip_key (is, "\"") &&
        from_json_internal::skip_fixed_key (is, t, false) &&
           from_json_skip_key (is, "\"") ;
    
}

inline
bool from_json_peak_nextkey (std::istream& is, char p)
{
    return from_json_internal::peek_next(is, p, true);
}


template<typename T>
bool from_json_string (std::string const & s, T& a_t)
{
    std::istringstream tmp (s);
    return from_json (tmp, a_t);
}

        


} /*namespace cc64*/


