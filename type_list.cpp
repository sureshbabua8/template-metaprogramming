#include <iostream>
#include <type_traits>
#include <typeinfo>

// Type list container
template<typename... Types>
struct type_list {};

// Predicate: is this type a pointer?
template<typename T>
struct is_pointer {
    static const bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

// Forward declaration
template <template <typename> class Predicate, typename List> 
struct find_first_if;

// Recursive case
template <template <typename> class Predicate, typename First, typename... Rest>
struct find_first_if<Predicate, type_list<First, Rest...>> {
    using type = std::conditional_t<
        Predicate<First>::value,
        First,
        typename find_first_if<Predicate, type_list<Rest...>>::type
    >;
};

// Base case
template <template <typename> class Predicate>
struct find_first_if<Predicate, type_list<>> {
    using type = void;
};

// Helper alias
template <template <typename> class Predicate, typename List>
using find_first_if_t = typename find_first_if<Predicate, List>::type;

int main() {
    using my_list = type_list<int, double, char*, float, int*>;
    
    using result = find_first_if_t<is_pointer, my_list>;
    
    std::cout << std::is_same_v<result, char*> << std::endl;  // 1 (true)
    
    return 0;
}