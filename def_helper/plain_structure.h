#define PLAIN_STRUCTURE_NON_DEFAULT


#ifdef PLAIN_STRUCTURE_UPDATE_NAME
class PLAIN_STRUCTURE_UPDATE_NAME;
#endif


//name rule
#include "plan_structure_components/default_naming_rule.h"


//once define the whole protector, no field will defined. too dangerous!

#ifdef PLAIN_STRUCTURE_WHOLE_PROTECTOR

#undef PLAIN_STRUCTURE_FIELD_PROTECTOR

#endif





//SampleClass
class PLAIN_STRUCTURE_NAME

#ifdef PLAIN_STRUCTURE_PARENTS

#define PLAIN_STRUCTURE_P_DEF(X) public X
#define DEF_SEP(X) ,
        : PLAIN_STRUCTURE_PARENTS(X)
#undef DEF_SEP
#undef PLAIN_STRUCTURE_P_DEF

#endif


{
public:

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) typedef TYPE MEM_TYPE_NAME(NAME); \
    static inline MEM_TYPE_NAME(NAME) MEM_DEFAULT_VALUE_FUN(NAME)() {  typedef struct tmpstru{ tmpstru() : m_tmpv(DEFAULT) {} TYPE m_tmpv; } TmpType; return TmpType().m_tmpv;}

#define DEF_SEP(X)

    PLAIN_STRUCTURE_FIELD_DECLARATION (", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
        ;
    


#define LOCAL_PLAIN_STRUCTURE_NAME PLAIN_STRUCTURE_NAME

#if defined(PLAIN_STRUCTURE_POD)
#define LOCAL_PLAIN_STRUCTURE_POD PLAIN_STRUCTURE_POD
#endif  /*defined(PLAIN_STRUCTURE_POD)*/

#if defined(PLAIN_STRUCTURE_FIELD_PROTECTOR)
#define LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR PLAIN_STRUCTURE_FIELD_PROTECTOR
#endif /*defined(PLAIN_STRUCTURE_FIELD_PROTECTOR)*/

#if defined(PLAIN_STRUCTURE_WHOLE_PROTECTOR)
#define LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR PLAIN_STRUCTURE_WHOLE_PROTECTOR
#endif /*defined(PLAIN_STRUCTURE_WHOLE_PROTECTOR)*/


#include "plan_structure_components/member_and_accessor_def.h"

#include "plan_structure_components/protector_def.h"

#include "plan_structure_components/constructor_destructor_def.h"

#include "plan_structure_components/assignment_and_value_Manipulator_def.h"

    
//#ifdef PLAIN_STRUCTURE_TO_JSON
#include "plan_structure_components/plan_structure_to_json_def.h"
//#endif


#include "plan_structure_components/estimate_mem_size_def.h"

    
//#include "plan_structure_components/to_aligned_format_def.h"

    
#undef LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR
#undef LOCAL_PLAIN_STRUCTURE_FIELD_PROTECTOR
#undef LOCAL_PLAIN_STRUCTURE_POD
#undef LOCAL_PLAIN_STRUCTURE_NAME

    
 

    




    //=======================================================
    //std::string to_string() const

public:
    std::string to_string() const
    {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }



#if defined(PLAIN_STRUCTURE_EXTRA_DECLARATION)
PLAIN_STRUCTURE_EXTRA_DECLARATION()
#endif



friend std::ostream & operator<<(std::ostream &, const PLAIN_STRUCTURE_NAME &);

public:
#ifdef PLAIN_STRUCTURE_UPDATE_NAME
    typedef PLAIN_STRUCTURE_UPDATE_NAME UpdateType;

    PLAIN_STRUCTURE_NAME& merge(PLAIN_STRUCTURE_UPDATE_NAME const & aUpdate);
    PLAIN_STRUCTURE_UPDATE_NAME diff (PLAIN_STRUCTURE_NAME const & aLeft ) const;

#endif /*PLAIN_STRUCTURE_UPDATE_NAME*/


};


#ifdef PLAIN_STRUCTURE_UPDATE_NAME

#include "plan_structure_components/update_package.h"
#include "plan_structure_components/merge_diff_on_update_def.h"

#endif /*PLAIN_STRUCTURE_UPDATE_NAME*/


inline std::ostream & operator<<(std::ostream & aOutStream, const PLAIN_STRUCTURE_NAME & aOther)
{
    aOther.to_json (aOutStream);
    return aOutStream;
}



#undef PLAIN_STRUCTURE_FIELD_DECLARATION

#undef PLAIN_STRUCTURE_NAME
#undef PLAIN_STRUCTURE_UPDATE_NAME
#undef PLAIN_STRUCTURE_PARENTS

#undef PLAIN_STRUCTURE_FIELD_PROTECTOR
#undef PLAIN_STRUCTURE_WHOLE_PROTECTOR

#undef PLAIN_STRUCTURE_EXTRA_DECLARATION

#undef PLAIN_STRUCTURE_POD


#undef PLAIN_STRUCTURE_TO_JSON





//name rule


#undef MEM_NAME
#undef MEM_TYPE_NAME
#undef MEM_DEFAULT_VALUE_FUN

#undef MEM_DIRECT_ACCESS_FUN
#undef MEM_GETTER_FUN
#undef MEM_SETTER_FUN
#undef MEM_RESET_FUN

#undef CLASS_RESET
#undef CLASS_CLEAR
#undef CLASS_DEFAULT
