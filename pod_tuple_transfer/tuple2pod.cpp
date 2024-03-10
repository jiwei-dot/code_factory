#include <string>
#include <vector>
#include <tuple>
#include <iostream>

struct Custom1
{
    int i;
    std::string j;
    std::vector<int> k;
};

struct Custom2
{
    char x;
    float y;
    double z;
};

template <typename _Struct, std::size_t... _Is, typename... _Types>
_Struct tuple_to_pod_impl(std::index_sequence<_Is...>, const std::tuple<_Types...> &_tup)
{
    return {std::get<_Is>(_tup)...};
}

template <typename _Struct, typename... _Types>
_Struct tuple_to_pod(const std::tuple<_Types...> &_tup)
{
    // 1. get tuple size
    const std::size_t _tuple_size = std::tuple_size<std::tuple<_Types...>>::value;
    // 2. make index sequence
    auto _index_sequence = std::make_index_sequence<_tuple_size>{};
    // 3. call impl
    return tuple_to_pod_impl<_Struct>(_index_sequence, _tup);
}

int main()
{
    Custom1 c1 = tuple_to_pod<Custom1>(
        std::make_tuple(1024, std::string("hello"), std::vector<int>{1, 2, 3}));

    std::cout << c1.i << " " << c1.j << " [ ";
    for (const auto &n : c1.k)
        std::cout << n << " ";
    std::cout << " ]" << std::endl;

    Custom2 c2 = tuple_to_pod<Custom2>(
        std::make_tuple('x', 2.34f, 3.14159625));
    std::cout << c2.x << " " << c2.y << " " << c2.z << std::endl;
    return 0;
}