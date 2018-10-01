







#ifdef PLAIN_STRUCTURE_UPDATE_NAME


inline PLAIN_STRUCTURE_NAME& PLAIN_STRUCTURE_NAME::merge(PLAIN_STRUCTURE_UPDATE_NAME const & aUpdate)
{
#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) if (aUpdate.MEM_GETTER_FUN(NAME)().has_value()) MEM_SETTER_FUN(NAME)(aUpdate.MEM_GETTER_FUN(NAME)().get_value());
#define DEF_SEP(X)

    PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF

return *this;
}

inline PLAIN_STRUCTURE_UPDATE_NAME PLAIN_STRUCTURE_NAME::diff (PLAIN_STRUCTURE_NAME const & aLeft ) const
{
PLAIN_STRUCTURE_UPDATE_NAME ret;
if (this == &aLeft) return ret;

#define PLAIN_STRUCTURE_FIELD_DEF(TYPE, NAME, DEFAULT) if (MEM_GETTER_FUN(NAME)() != aLeft.MEM_GETTER_FUN(NAME)()){ ret.MEM_SETTER_FUN(NAME)(MEM_GETTER_FUN(NAME)()); }else{ ret.MEM_RESET_FUN(NAME)();}
#define DEF_SEP(X)

    PLAIN_STRUCTURE_FIELD_DECLARATION(", ")

#undef DEF_SEP
#undef PLAIN_STRUCTURE_FIELD_DEF
    return ret;
}


#endif /*PLAIN_STRUCTURE_UPDATE_NAME*/



