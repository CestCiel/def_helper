
//SampleClass
class PLAIN_STRUCTURE_UPDATE_NAME
{
public:


#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) typedef cc64::NullableT<TYPE> MEM_TYPE_NAME(NAME); \
    static inline MEM_TYPE_NAME(NAME) MEM_DEFAULT_VALUE_FUN(NAME)() { return MEM_TYPE_NAME(NAME)();}
#define DEF_SEP(X)

    PLAIN_STRUCTURE_FIELD_DECLARATION (", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF


    
#define LOCAL_PLAIN_STRUCTURE_NAME PLAIN_STRUCTURE_UPDATE_NAME

//#if defined(PLAIN_STRUCTURE_POD)
//#define LOCAL_PLAIN_STRUCTURE_POD PLAIN_STRUCTURE_POD
//#endif  /*defined(PLAIN_STRUCTURE_POD)*/

//#if defined(PLAIN_STRUCTURE_FIELD_PROTECTOR)
//#define LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR PLAIN_STRUCTURE_FIELD_PROTECTOR
//#endif /*defined(PLAIN_STRUCTURE_FIELD_PROTECTOR)*/

#include "member_and_accessor_def.h"

#define LOCAL_USE_DEFAULT_STATIC_FOR_CONSTRUCT
#include "constructor_destructor_def.h"
#undef LOCAL_USE_DEFAULT_STATIC_FOR_CONSTRUCT

#include "assignment_and_value_Manipulator_def.h"



#include "plan_structure_to_json_def.h"


//#include "to_aligned_format_def.h"

#undef LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR
#undef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
#undef LOCAL_PLAIN_STRUCTURE_POD
#undef LOCAL_PLAIN_STRUCTURE_NAME


    size_t count_fields() const
    {
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) (MEM_NAME(NAME).has_value() ? 1 : 0)
#define DEF_SEP(X) +

        return (PLAIN_STRUCTURE_FIELD_DECLARATION(", "));

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
    }




    friend std::ostream &operator<<(std::ostream &, const PLAIN_STRUCTURE_UPDATE_NAME &);

    //=======================================================
    //std::string to_string() const

    std::string to_string() const
    {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }






};


inline std::ostream &operator<<(std::ostream &aOutStream, const PLAIN_STRUCTURE_UPDATE_NAME &aOther)
{
    aOther.to_json (aOutStream);
    return aOutStream;
}
