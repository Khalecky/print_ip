#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <tuple>


using namespace std;

//
template<class T>
constexpr bool is_integral_v = is_integral<T>::value;

template<typename T, typename ...Args>
struct is_one_of;

template<typename T>
struct is_one_of<T> : false_type {};

template<typename T, typename ...Args>
struct is_one_of<T, T, Args...> : true_type {};

template<typename T, typename U, typename ...Args>
struct is_one_of<T, U, Args...> : is_one_of<T, Args...> {};
//
//
template<class T>
using PrintIntegralType = enable_if_t<is_integral_v<T>>;

template<class T>
using PrintContainerType = enable_if_t<is_one_of<T, list<typename T::value_type>, vector<typename T::value_type> >::value>;

template<typename ...Args>
using PrintTupleType = enable_if_t< is_one_of<Args...>::value >;

//WHY????? Если эти две строчки переместить на самый верх - то ОШИБКА КОМПИЛЯЦИИ
template<bool P, class T = void>
using enable_if_t = typename enable_if<P, T>::type;
//

//****
template<int Index, class ...Types>
struct TupleIter
{
    static void print(const tuple<Types...> &t)
    {
        auto const i = sizeof...(Types) - Index - 1;
        cout << get<i>(t) << ".";
        TupleIter<Index-1, Types...>::print(t);
    }
};

template<typename ...Types>
struct TupleIter<0, Types...>
{
    static void print(const tuple<Types...> &t)
    {
        auto const i = sizeof...(Types) - 1;
        cout << get<i>(t) << endl;
    }
};
//****


//*************************************************
void print_ip(const string& s)
{
    cout << s << endl;
}

//print integral
template<typename T, typename IsValid = PrintIntegralType<T> >
void print_ip(T ip)
{
    const size_t n = sizeof(T);

    union {
        T val;
        unsigned char bytes[n];
    };
    val = ip;

    for(size_t i = 0; i < n; ++i) {
        if (i > 0)
            cout << ".";
        cout << static_cast<int>(bytes[n - i - 1]);
    }
    cout << endl;
}


//print list|vector
template<class T, class IsValid = PrintContainerType<T> >
void print_ip(const T& v)
{
    for(auto i = v.begin(); i != v.end(); ++i) {
        if (i != v.begin())
            cout << ".";
        cout << *i;
    }
    cout << endl;
}

//print tuple
template<typename ...Types, class IsValid = PrintTupleType<Types...> >
void print_ip(const tuple<Types...>& t)
{
    constexpr int sz = sizeof...(Types);
    TupleIter<sz-1, Types...>::print(t);
}


int main()
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip(list<string>{"234","987"});
    print_ip(vector<int>{234,34,567});

    print_ip(tuple<int, int>(10, 2));
    print_ip(make_tuple("100", "29", "98"));

    return 0;
}
