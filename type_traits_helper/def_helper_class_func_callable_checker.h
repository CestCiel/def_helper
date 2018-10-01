



template<typename X>
struct FNAME
{

#define PLIST_ITEM(X) std::declval<X>()
#define PLIST_SEP() ,
    template<typename C>
    static auto check_callable(C*)
        -> typename std::is_same<decltype(std::declval<C>().
                                          FUNC_NAME(
                                              PLIST()
                                              )
        ), RET_TYPE>::type;


    template<typename C>
    static auto check_pointer_callable(C*)
        -> typename std::is_same<decltype(std::declval<C>()->
                                          FUNC_NAME(
                                              PLIST()
                                              )
        ), RET_TYPE>::type;


#undef PLIST_ITEM
#undef PLIST_SEP

    template<typename>
    static std::false_type check_callable(...);

    template<typename>
    static std::false_type check_pointer_callable(...);


    using callable = decltype(check_callable<X> (0));
    using pointer_callable = decltype(check_pointer_callable<X> (0));

};


#undef FNAME
#undef FUNC_NAME
#undef RET_TYPE
#undef PLIST
