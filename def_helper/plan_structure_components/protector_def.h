

#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR

private:
mutable  LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR m_Protector;
typedef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR ProtectorType;

#endif /*LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR*/



#ifdef LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR

private:

mutable LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR m_W_Protector;


template<typename BasicClass, typename ProtectorType>
class ReadWholeProtectorT : private ProtectorType::ReadScopeLockType
{
public:
    ReadWholeProtectorT (BasicClass const & x)
        : ProtectorType::ReadScopeLockType (x.m_W_Protector)
        {}
};

template<typename BasicClass, typename ProtectorType>
class WriteWholeProtectorT : private ProtectorType::WriteScopeLockType
{
public:
    WriteWholeProtectorT (BasicClass const & x)
        : ProtectorType ::WriteScopeLockType (x.m_W_Protector)
        {}
};

friend class ReadWholeProtectorT<PLAIN_STRUCTURE_NAME, LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR>;
friend class WriteWholeProtectorT<PLAIN_STRUCTURE_NAME, LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR>;


public:

typedef ReadWholeProtectorT<PLAIN_STRUCTURE_NAME, LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR> ReadWholeProtector;
typedef WriteWholeProtectorT<PLAIN_STRUCTURE_NAME, LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR> WriteWholeProtector;


#else /*LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR*/

template<typename BasicClass>
class ReadWholeProtectorT
{
public:
    ReadWholeProtectorT(BasicClass const & x) { }
};

template<typename BasicClass>
class WriteWholeProtectorT
{
public:
    WriteWholeProtectorT(BasicClass const & x) { }
};


friend class ReadWholeProtectorT<PLAIN_STRUCTURE_NAME>;
friend class WriteWholeProtectorT<PLAIN_STRUCTURE_NAME>;


public:
    typedef ReadWholeProtectorT<PLAIN_STRUCTURE_NAME> ReadWholeProtector;
    typedef WriteWholeProtectorT<PLAIN_STRUCTURE_NAME> WriteWholeProtector;

#endif /*LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR*/


