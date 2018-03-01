#ifndef HORIZON_CORE_STRUCTURES_TYPELIST_HPP
#define HORIZON_CORE_STRUCTURES_TYPELIST_HPP

class TypeNull;

template<typename HEAD, typename TAIL>
struct TypeList
{
    typedef HEAD Head;
    typedef TAIL Tail;
};

#define TYPELIST_1(T1)                          TypeList<T1, TypeNull>
#define TYPELIST_2(T1, T2)                      TypeList<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3)                  TypeList<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4)              TypeList<T1, TYPELIST_3(T2, T3, T4) >
#define TYPELIST_5(T1, T2, T3, T4, T5)          TypeList<T1, TYPELIST_4(T2, T3, T4, T5) >
#define TYPELIST_6(T1, T2, T3, T4, T5, T6)      TypeList<T1, TYPELIST_5(T2, T3, T4, T5, T6) >
#define TYPELIST_7(T1, T2, T3, T4, T5, T6, T7)  TypeList<T1, TYPELIST_6(T2, T3, T4, T5, T6, T7) >

#endif /* HORIZON_CORE_STRUCTURES_TYPELIST_HPP */
