

public:
inline void to_json (std::ostream& out) const
{
    cc64::to_json_internal::json_encode_obj_begin (out);

#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
    LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector);
#endif

    
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) cc64::to_json_internal::json_encode_as_name_value (out, std::string (#NAME), MEM_NAME(NAME)); 
        
#define DEF_SEP(X)     cc64::to_json_internal::json_encode_comma (out);

    PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
    cc64::to_json_internal::json_encode_obj_end (out);
}

public:
inline std::string to_json_string() const
{
    std::ostringstream out;
    to_json (out);
    return out.str();
}



public:
inline bool from_json (std::istream& is)
{
    if (!cc64::from_json_internal::json_decode_obj_begin (is)) return false;

    std::string nametmp;
    
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
    LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector);
#endif
    
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) cc64::from_json_internal::json_decode_as_name_value (is, nametmp, MEM_NAME(NAME))
        
#define DEF_SEP(X) X cc64::from_json_internal::json_decode_comma (is) X

    bool ret = PLAIN_STRUCTURE_FIELD_DECLARATION(&&)

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;

    if (!ret) return ret;
    return cc64::from_json_internal::json_decode_obj_end (is);    
}

public:
inline
bool from_json_string (std::string const & in)
{
    std::istringstream x (in);
    return from_json (x);
}
