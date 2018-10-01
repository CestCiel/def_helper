



#ifndef MEM_NAME
#define MEM_NAME(X) MACRO_COMBINE2(m_,X)
#endif /*MEM_NAME*/

#ifndef MEM_TYPE_NAME
#define MEM_TYPE_NAME(X) MACRO_COMBINE2(X,Type)
#endif /*MEM_TYPE_NAME*/

#ifndef MEM_DEFAULT_VALUE_FUN
#define MEM_DEFAULT_VALUE_FUN(X) MACRO_COMBINE2(X,_default)
#endif /*MEM_DEFAULT_VALUE_FUN*/


#ifndef MEM_DIRECT_ACCESS_FUN
#define MEM_DIRECT_ACCESS_FUN(X) X
#endif /*MEM_DIRECT_ACCESS_FUN*/


#ifndef MEM_GETTER_FUN
#define MEM_GETTER_FUN(X) MACRO_COMBINE2(get_,X)
#endif /*MEM_GETTER_FUN*/

#ifndef MEM_SETTER_FUN
#define MEM_SETTER_FUN(X) MACRO_COMBINE2(set_,X)
#endif /*MEM_SETTER_FUN*/

#ifndef MEM_RESET_FUN
#define MEM_RESET_FUN(X) MACRO_COMBINE2(reset_,X)
#endif /*MEM_RESET_FUN*/


#ifndef CLASS_RESET
#define CLASS_RESET() reset
#endif /*CLASS_RESET*/

#ifndef CLASS_CLEAR
#define CLASS_CLEAR() clear
#endif /*CLASS_CLEAR*/

#ifndef CLASS_DEFAULT
#define CLASS_DEFAULT() default_value
#endif /*CLASS_DEFAULT*/
