

#include "../def_helper/plain_structure_pre.h"
#include <iostream>


//============================================================================
//a sample type

#define PLAIN_STRUCTURE_NAME SampleType


#define PLAIN_STRUCTURE_FIELD_DECLARATION(X)                            \
    PLAIN_STRUCTURE_FIELD_DEF (char,            char_variable,         'A')          DEF_SEP(X) \
    PLAIN_STRUCTURE_FIELD_DEF (int,             int_variable,           0)           DEF_SEP(X) \
    PLAIN_STRUCTURE_FIELD_DEF (std::set<int>,   set_variable,           std::set<int>())


#define PLAIN_STRUCTURE_EXTRA_DECLARATION() \
public: size_t count() const;


#include "../def_helper/plain_structure.h"

inline size_t SampleType::count() const
{
    return get_set_variable().size();
}


void some_action_on_sampletype()
{
    SampleType x;
    
    x.set_variable().insert (1);
    x.set_variable().insert (2);
    x.set_variable().insert (3);

    std::string l_json_str = x.to_json_string();

    SampleType y;

    cc64::from_json_string (l_json_str,y);

    x.to_json (std::cout);
    std::cout<<"\n";
    std::cout<<y.to_json_string ()<<"\n";
    

    return;
}

    


//============================================================================
//a pod type

#define PLAIN_STRUCTURE_NAME PODType

#define PLAIN_STRUCTURE_POD

#define PLAIN_STRUCTURE_UPDATE_NAME PODTypeUpdate


#define PLAIN_STRUCTURE_FIELD_DECLARATION(X)                            \
    PLAIN_STRUCTURE_FIELD_DEF (char,            char_variable,         'A')          DEF_SEP(X) \
    PLAIN_STRUCTURE_FIELD_DEF (int,             int_variable,           0)



#include "../def_helper/plain_structure.h"

void some_action_pod_type_and_update()
{
    PODType a = PODType::default_value();
    std::cout<<"is PODType a pod "<<std::is_pod<PODType>::value<<"\n";
    a.int_variable()=100;
    std::cout<<a.to_json_string()<<"\n";

    PODType b;
    b.set_char_variable ('C').set_int_variable (100);
    std::cout<<b.to_json_string()<<"\n";

    PODType::UpdateType a_b = a.diff (b);
    std::cout<<a_b.to_json_string()<<"\n";

    b.merge (a_b);
    std::cout<<b.to_json_string()<<"\n";

}

    
    

//============================================================================
//a sample filed type: NOTE: Mutex Dummy do not protect

#define PLAIN_STRUCTURE_NAME SampleTypeProtected

#define PLAIN_STRUCTURE_FIELD_PROTECTOR cc64::RWMutexDummy

#define PLAIN_STRUCTURE_FIELD_DECLARATION(X)                            \
    PLAIN_STRUCTURE_FIELD_DEF (char, char_name, PLAIN_STRUCTURE_NON_DEFAULT) DEF_SEP(X)         \
    PLAIN_STRUCTURE_FIELD_DEF (long, long_name, PLAIN_STRUCTURE_NON_DEFAULT)



#define PLAIN_STRUCTURE_EXTRA_DECLARATION() \
public: bool is_name() const;



#include "../def_helper/plain_structure.h"

inline bool SampleTypeProtected::is_name() const
{
    ProtectorType::ReadScopeLockType lock(m_Protector);
    return m_char_name == 'A';
}

void some_action_on_filed_protector()
{
    SampleTypeProtected x;
    std::cout<<"is name A -" <<x.is_name()<<"\n";
    std::cout<<"is name A -"<<x.set_char_name ('A').is_name()<<"\n";
}


//============================================================================
//a sample whole type: NOTE: Mutex Dummy do not protect

#define PLAIN_STRUCTURE_NAME SampleTypeWholeProtected

#define LOCAL_PLAIN_STRUCTURE_WHOLE_PROTECTOR cc64::RWMutexDummy

#define PLAIN_STRUCTURE_FIELD_DECLARATION(X)                            \
    PLAIN_STRUCTURE_FIELD_DEF (char, char_name, PLAIN_STRUCTURE_NON_DEFAULT) DEF_SEP(X)         \
    PLAIN_STRUCTURE_FIELD_DEF (long, long_name, PLAIN_STRUCTURE_NON_DEFAULT)



#include "../def_helper/plain_structure.h"


void some_action_on_whole_protector()
{
    SampleTypeWholeProtected x;

    {
        SampleTypeWholeProtected::WriteWholeProtector lock (x);
        x.set_char_name ('O').set_long_name (101);
    }

    {
        SampleTypeWholeProtected::ReadWholeProtector lock (x);
        std::cout<<x.to_json_string()<<"\n";
    }
    
}


    


int main()
{
    some_action_on_sampletype();
    some_action_pod_type_and_update();
    some_action_on_filed_protector();
    some_action_on_whole_protector();
    
    return 0;
}
