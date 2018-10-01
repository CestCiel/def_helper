


private:

size_t do_memory_estimate(std::true_type) const
{
    return sizeof(LOCAL_PLAIN_STRUCTURE_NAME);
}

size_t do_memory_estimate(std::false_type) const
{
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
    LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector);
#endif

    return 
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) cc64::estimate_mem_size (MEM_NAME(NAME)); 
        
#define DEF_SEP(X)     X

    PLAIN_STRUCTURE_FIELD_DECLARATION(+)

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
}




public:

inline
size_t estimate_mem_size() const
{
    return do_memory_estimate(std::is_pod<LOCAL_PLAIN_STRUCTURE_NAME>::type{})
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
        + cc64::estimate_mem_size (m_Protector)
#endif
#ifdef LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR
        + cc64::estimate_mem_size (m_W_Protector)
#endif
        ;
}
