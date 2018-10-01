#pragma once



#define MACRO_TOSTR_HELPER(a) #a
#define MACRO_TOSTR(a) MACRO_TOSTR_HELPER(a)

#define COMBINE_HELPER(a,b) a##b
#define MACRO_COMBINE2(a,b) COMBINE_HELPER(a,b)
#define MACRO_COMBINE3(a,b,c ) MACRO_COMBINE2(a, MACRO_COMBINE2(b,c))


//define, a variable with diffcult name and two access function under a control
#define DEFINE_ANONYMOUS_VARIABLE(TYPE, NAME, ACCESS_CONTROL) ACCESS_CONTROL: TYPE MACRO_COMBINE3(m_, NAME ,__LINE__);   \
    ACCESS_CONTROL: inline  TYPE& NAME() { return MACRO_COMBINE3(m_, NAME,__LINE__);} \
    ACCESS_CONTROL: inline  const TYPE& MACRO_COMBINE2(get_, NAME)() const { return MACRO_COMBINE3(m_,NAME,__LINE__);} \
    ACCESS_CONTROL: inline  void MACRO_COMBINE2(set_, NAME)(TYPE const & a_v) { NAME() = a_v;}

