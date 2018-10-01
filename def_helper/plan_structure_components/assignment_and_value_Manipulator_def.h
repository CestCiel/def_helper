

#ifndef LOCAL_PLAIN_STRUCTURE_POD

//=======================================================
//SampleClass& operator=(const SampleClass& aOther)

public: LOCAL_PLAIN_STRUCTURE_NAME & operator=(LOCAL_PLAIN_STRUCTURE_NAME const & aOther)
{
    if (this == &aOther) {
        return (*this);
    }
    
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
    LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector);
#endif


#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) MEM_NAME(NAME) = aOther.MEM_GETTER_FUN(NAME)();
#define DEF_SEP(X)

    PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
    return (*this);
}


//=======================================================
//void reset()
//void clear

public: inline LOCAL_PLAIN_STRUCTURE_NAME & CLASS_RESET()()
{
    *this = LOCAL_PLAIN_STRUCTURE_NAME();
    return *this;
}


#else /*LOCAL_PLAIN_STRUCTURE_POD*/

public: inline LOCAL_PLAIN_STRUCTURE_NAME & CLASS_RESET()()
{
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) MEM_SETTER_FUN(NAME) (MEM_DEFAULT_VALUE_FUN(NAME)());
#define DEF_SEP(X)

    PLAIN_STRUCTURE_FIELD_DECLARATION (", ") 

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
    
    return *this;
}

#endif /*LOCAL_PLAIN_STRUCTURE_POD*/


inline LOCAL_PLAIN_STRUCTURE_NAME & CLASS_CLEAR()() { return CLASS_RESET()(); }



inline static LOCAL_PLAIN_STRUCTURE_NAME  CLASS_DEFAULT()()  { return LOCAL_PLAIN_STRUCTURE_NAME().CLASS_RESET()();}

//=======================================================
// set (...)
LOCAL_PLAIN_STRUCTURE_NAME & set(

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) MEM_TYPE_NAME(NAME) const & MACRO_COMBINE2(a,NAME) = MACRO_COMBINE2(NAME, _default)()
#define DEF_SEP(X) ,

    PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
    )
{
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
    LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector);
#endif


#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) MEM_NAME(NAME) =  MACRO_COMBINE2(a,NAME);
#define DEF_SEP(X)

    PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
    
    return (*this);
}


