//=======================================================
//SampleFiledType& SampleFiled()
//const SampleFiledType& GetSampleFiled() const
//void SetSampleFiled(const SampleFiledType&)
//

#ifdef LOCAL_PLAIN_STRUCTURE_POD
#define MEMBER_ACCESS_CONTROL public
#else
#define MEMBER_ACCESS_CONTROL private
#endif


#ifdef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT)                  \
private: inline MEM_TYPE_NAME(NAME) & MEM_DIRECT_ACCESS_FUN (NAME) () { return MEM_NAME(NAME);} \
public: inline MEM_TYPE_NAME(NAME) MEM_GETTER_FUN(NAME)() const { LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::ReadScopeLockType lock(m_Protector); return MEM_NAME(NAME);} \
public: inline LOCAL_PLAIN_STRUCTURE_NAME & MEM_SETTER_FUN(NAME)(MEM_TYPE_NAME(NAME) const & aValue) { LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector); MEM_NAME(NAME) = aValue; return *this;} \
public: inline LOCAL_PLAIN_STRUCTURE_NAME & MEM_RESET_FUN(NAME)() { LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR::WriteScopeLockType lock(m_Protector); MEM_NAME(NAME) = MEM_DEFAULT_VALUE_FUN(NAME) (); return *this;} \
MEMBER_ACCESS_CONTROL: MEM_TYPE_NAME(NAME) MEM_NAME(NAME);

#else

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT)                  \
public: inline MEM_TYPE_NAME(NAME) & MEM_DIRECT_ACCESS_FUN (NAME)() { return MEM_NAME(NAME);} \
public: inline MEM_TYPE_NAME(NAME) const & MEM_GETTER_FUN(NAME)() const { return MEM_NAME(NAME);}       \
public: inline LOCAL_PLAIN_STRUCTURE_NAME & MEM_SETTER_FUN(NAME)(MEM_TYPE_NAME(NAME) const & aValue) { MEM_NAME(NAME) = aValue; return *this;} \
public: inline LOCAL_PLAIN_STRUCTURE_NAME & MEM_RESET_FUN(NAME)() {  MEM_NAME(NAME) = MEM_DEFAULT_VALUE_FUN(NAME) (); return *this;} \
MEMBER_ACCESS_CONTROL: MEM_TYPE_NAME(NAME) MEM_NAME(NAME);
#endif

#define DEF_SEP(X)

PLAIN_STRUCTURE_FIELD_DECLARATION (",")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF


#undef MEMBER_ACCESS_CONTROL

public:

