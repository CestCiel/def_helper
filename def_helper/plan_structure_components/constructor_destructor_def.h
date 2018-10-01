


#ifndef LOCAL_PLAIN_STRUCTURE_POD



//=======================================================
//~SampleClass()

public:
~LOCAL_PLAIN_STRUCTURE_NAME()
{
#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
    LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector);
#endif

#ifdef LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR
    WriteWholeProtector lock(*this);
#endif
}



//=======================================================
//SampleClass()

#ifdef LOCAL_USE_DEFAULT_STATIC_FOR_CONSTRUCT

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) MEM_NAME(NAME) (MEM_DEFAULT_VALUE_FUN(NAME)())

#else /*LOCAL_USE_DEFAULT_STATIC_FOR_CONSTRUCT*/

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) MEM_NAME(NAME) (DEFAULT)

#endif /*LOCAL_USE_DEFAULT_STATIC_FOR_CONSTRUCT*/

#define DEF_SEP(X) ,

public:
LOCAL_PLAIN_STRUCTURE_NAME()
    :
    PLAIN_STRUCTURE_FIELD_DECLARATION(", ") { }

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF



//=======================================================
//SampleClass(const SampleClass& aOther)

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) MEM_NAME(NAME) (aOther.MEM_GETTER_FUN(NAME)())
#define DEF_SEP(X) ,


public:
LOCAL_PLAIN_STRUCTURE_NAME(LOCAL_PLAIN_STRUCTURE_NAME const & aOther)
    :
    PLAIN_STRUCTURE_FIELD_DECLARATION(", ") {}

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF



#endif /* LOCAL_PLAIN_STRUCTURE_POD */
