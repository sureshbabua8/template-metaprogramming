#include <iostream>
#include <type_traits>

// Type list container
template<typename... Types>
struct TypeList {
    static const int size = sizeof...(Types);
};

// Example transformations that users might want to apply

// Add pointer to a type
template<typename T>
struct AddPointer {
    using type = T*;
};

// Add const to a type
template<typename T>
struct AddConst {
    using type = const T;
};

// Remove pointer from a type (if it's a pointer)
template<typename T>
struct RemovePointer {
    using type = T;  // Default: no change
};

template<typename T>
struct RemovePointer<T*> {
    using type = T;  // Remove the pointer
};

template <template <typename> class Predicate, typename TypeList>
struct Transform;

template <template <typename> class Transformation, typename... Types>
struct Transform<Transformation, TypeList<Types...>> {
    using type = TypeList<typename Transformation<Types>::type...>;
};

// base case
template <template <typename> class Predicate>
struct Transform<Predicate, TypeList<>> {
    using type = TypeList<>;
};

template <template <typename> class Predicate, typename TypeList>
using Transform_t = typename Transform<Predicate, TypeList>::type;

// Your task: Implement Transform
// It should take a TypeList and a transformation template
// and apply the transformation to every type in the list

// Example usage (this should compile when you're done):
int main() {
    using Original = TypeList<int, double, char, float>;
    
    // Add pointer to every type
    using WithPointers = Transform_t<AddPointer, Original>;
    // Should be: TypeList<int*, double*, char*, float*>
    
    std::cout << "Original size: " << Original::size << std::endl;  // 4
    std::cout << "Transformed size: " << WithPointers::size << std::endl;  // 4
    
    // Test correctness
    std::cout << std::is_same_v<WithPointers, TypeList<int*, double*, char*, float*>> << std::endl;  // 1
    
    // Add const to every type
    using WithConst = Transform_t<AddConst, Original>;
    // Should be: TypeList<const int, const double, const char, const float>
    
    std::cout << std::is_same_v<WithConst, TypeList<const int, const double, const char, const float>> << std::endl;  // 1
    
    // Chain transformations: first add pointer, then add const
    using ConstPointers = Transform_t<AddConst, WithPointers>;
    // Should be: TypeList<const int*, const double*, const char*, const float*>
    
    std::cout << std::is_same_v<ConstPointers, TypeList<const int*, const double*, const char*, const float*>> << std::endl;  // 1
    
    // Remove pointers
    using PointerList = TypeList<int*, double*, char*, float*>;
    using WithoutPointers = Transform_t<RemovePointer, PointerList>;
    // Should be: TypeList<int, double, char, float>
    
    std::cout << std::is_same_v<WithoutPointers, TypeList<int, double, char, float>> << std::endl;  // 1
    
    return 0;
}