#include <iostream>
#include <type_traits>

// Type list container
template<typename... Types>
struct TypeList {
    static const int size = sizeof...(Types);
};

// Forward declarations
template <typename T, typename List>
struct Contains;

template <typename T, typename List>
struct Prepend;

template <typename List>
struct RemoveDuplicates;

// === Contains Implementation ===

// Base case: empty list doesn't contain anything
template <typename T>
struct Contains<T, TypeList<>> {
    static const bool value = false;
};

// Recursive case: check if T matches First, or if T is in Rest
template <typename T, typename First, typename... Rest>
struct Contains<T, TypeList<First, Rest...>> {
    static const bool value = std::is_same_v<T, First> || Contains<T, TypeList<Rest...>>::value;
};

// === Prepend Implementation ===

template <typename T, typename... Types>
struct Prepend<T, TypeList<Types...>> {
    using type = TypeList<T, Types...>;
};

// === RemoveDuplicates Implementation ===

// Base case: empty list has no duplicates
template <>
struct RemoveDuplicates<TypeList<>> {
    using type = TypeList<>;
};

// Recursive case
template <typename First, typename... Rest>
struct RemoveDuplicates<TypeList<First, Rest...>> {
private:
    // First, remove duplicates from the rest of the list
    using UniqueRest = typename RemoveDuplicates<TypeList<Rest...>>::type;
    
public:
    // If First already exists in UniqueRest, skip it; otherwise prepend it
    using type = std::conditional_t<
        Contains<First, UniqueRest>::value,
        UniqueRest,  // Skip First (it's a duplicate)
        typename Prepend<First, UniqueRest>::type  // Include First
    >;
};

// Helper alias
template <typename List>
using RemoveDuplicates_t = typename RemoveDuplicates<List>::type;

int main() {
    using Original = TypeList<int, double, int, char, double, int, float>;
    using NoDuplicates = RemoveDuplicates_t<Original>;
    
    std::cout << "Original size: " << Original::size << std::endl;  // 7
    std::cout << "After removing duplicates: " << NoDuplicates::size << std::endl;  // 4
    
    // Test that it worked correctly
    std::cout << std::is_same_v<NoDuplicates, TypeList<int, double, char, float>> << std::endl;  // 1
    
    return 0;
}