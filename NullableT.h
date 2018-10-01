#pragma once


//#include "CompareValue.h"
#include "json_helper.h"

namespace cc64
{


template<typename VALUE_TYPE>
class NullableT
{
public:

    typedef NullableT<VALUE_TYPE> Type;

    typedef VALUE_TYPE UnderlyingType;

    NullableT()
            : m_HasValue(false) { }

    /*explicit*/ NullableT(VALUE_TYPE const & aValue)
    {
        set_value(aValue);
    }


    NullableT(NullableT<VALUE_TYPE> const & aOther)
            : m_HasValue(aOther.m_HasValue),
              m_Value(aOther.m_Value) { }


    NullableT<VALUE_TYPE> & operator=(NullableT<VALUE_TYPE> const & aOther);


    bool has_value() const { return m_HasValue; }

    bool try_get_value(VALUE_TYPE & aValue) const
    {
        if (!m_HasValue) {
            return false;
        }
        aValue = m_Value;
        return true;
    }

    VALUE_TYPE const & get_value() const
    {
        if (!m_HasValue) {
            throw std::runtime_error(__FUNCTION__);
        }
        return m_Value;
    }

    VALUE_TYPE & value()
    {
        if (!m_HasValue) {
            throw std::runtime_error(__FUNCTION__);
        }
        return m_Value;
    }


    NullableT<VALUE_TYPE> & promote()
    {
        if (has_value()) return *this;
        reset_value();
        m_HasValue = true;
        return *this;
    }

    NullableT<VALUE_TYPE> & set_value(VALUE_TYPE const & aValue)
    {
        m_Value = aValue;
        m_HasValue = true;
        return *this;
    }

    NullableT<VALUE_TYPE> & reset_value()
    {
        *this = NullableT<VALUE_TYPE>();
        return *this;
    }

    bool try_release_value(VALUE_TYPE & aValue)
    {
        if (!m_HasValue) {
            return false;
        }
        aValue = m_Value;
        m_HasValue = false;
        return true;
    }

    VALUE_TYPE release_value()
    {
        if (!m_HasValue) {
            throw std::runtime_error(__FUNCTION__);
        }
        m_HasValue = false;
        return m_Value;
    }

    operator VALUE_TYPE() const = delete;

    //int compare(NullableT<VALUE_TYPE> const & aOther) const;

    //CLASS_DEFFINITION_HELPER_COMPARISON_OPERATOR (NullableT<VALUE_TYPE>);


    std::string to_string() const
    {
        std::ostringstream ostr;
        to_json (ostr);
        return ostr.str();
        // if (!m_HasValue) {
        //     return "";
        // }
        // return cc64::to_string(m_Value);
    }

    void to_json(std::ostream & aOut) const
    {
        if (!m_HasValue) {
            cc64::to_json_internal::json_encode_null (aOut);
            return;
        }
        return cc64::to_json(aOut, m_Value);
    }
    
    bool from_json(std::istream & aIs)
    {
        if(cc64::from_json_internal::is_null_eating_spaces (aIs))
        {
            reset_value();
            return cc64::from_json_internal::json_decode_null (aIs);
        }
        return cc64::from_json (aIs,promote().value());
    }
            

private:
    bool m_HasValue;

    VALUE_TYPE m_Value;

};


template<typename VALUE_TYPE>
NullableT<VALUE_TYPE> & NullableT<VALUE_TYPE>::operator=(NullableT<VALUE_TYPE> const & aOther)
{
    if (this == &aOther)return *this;
    m_HasValue = aOther.m_HasValue;
    m_Value = aOther.m_Value;
    return *this;
}

// template<typename VALUE_TYPE>
// int NullableT<VALUE_TYPE>::compare(NullableT<VALUE_TYPE> const & aOther) const
// {
//     if (this == &aOther)return 0;
//     if (m_HasValue && aOther.m_HasValue) {
//         return compare_value(m_Value, aOther.m_Value);
//     }
//     return compare_value(m_HasValue, aOther.m_HasValue);
// }

}


