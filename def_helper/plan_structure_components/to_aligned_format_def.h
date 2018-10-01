
public:
cc64::Fixed2DimensionTable<std::string> to_2dimensiontable() const
{
    const static size_t gLengthofY = 0 +
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) 1
#define DEF_SEP(X) +
        
        PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;

    cc64::Fixed2DimensionTable<std::string> ret(2, gLengthofY);

    {
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
        LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::ReadScopeLockType lock(m_Protector);
#endif
        size_t yCount = 0;

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) ret.set_value(0, yCount, #NAME); ret.set_value(1, yCount++, cc64::to_string(MEM_NAME(NAME)) );
#define DEF_SEP(X)

        PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
            ;
    }

    return ret;
}



//=======================================================
//std::string to_csv_string() const
public:
static std::string to_csv_string_head()
{
    return
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) #NAME
#define DEF_SEP(X) X
        
        PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
}

public:
std::string to_csv_string() const
{
    std::ostringstream oss;
        
    {
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
        LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::ReadScopeLockType lock(m_Protector);
#endif

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) oss<< V_V_TOSTRING (MEM_NAME(NAME));
#define DEF_SEP(X) oss <<(X);

        PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
            ;
        
    }
    return oss.str();

}


public:
template<typename T>
T & to_formated_channel(T & aT) const
{
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) aT.push(std::string(#NAME), MEM_GETTER_FUN(NAME)());
#define DEF_SEP(X) aT.new_line();

    PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
    return aT;
}



