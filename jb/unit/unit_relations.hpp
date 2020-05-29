#pragma once

#include <type_traits>

namespace jb {
namespace unit {


// Every expression is expected to be normalized.
// A normalized expression has one of these forms:
// 1. Product<E1, ..., En> where each Ei is a Base Unit or the Inverse of a Base Unit
// 2. B where B is a Base Unit
// 3. Inverse<B> where B is a Base Unit


template<typename... FACTORS>
struct Product;
template<typename T>
struct IsProduct : public std::false_type {};
template<typename... FACTORS>
struct IsProduct<Product<FACTORS...>> : public std::true_type {};
template<typename T>
constexpr bool IsProductV = IsProduct<T>::value;

template<typename T>
struct Inverse;
template<typename T>
struct IsInverse : public std::false_type {};
template<typename BASE_UNIT>
struct IsInverse<Inverse<BASE_UNIT>> : public std::true_type {};
template<typename T>
constexpr bool IsInverseV = IsInverse<T>::value;

template<typename... FACTORS>
struct Product {
    template<typename... FACTORS>
    struct IsNormalized;
    template<typename FIRST, typename... REST>
    struct IsNormalized<FIRST, REST...> {
        static constexpr bool value = !IsProductV<FIRST> && IsNormalized<REST...>::value;
    };
    template<>
    struct IsNormalized<> {
        static constexpr bool value = true;
    };
    static_assert(IsNormalized<FACTORS...>::value, "Product must not contain more products");
};

template<typename B>
struct Inverse {
    static_assert(!IsProductV<B> && !IsInverseV<B>, "B must be a base unit");
};


namespace _helpers {
    template<typename PRODUCT, typename FACTOR>
    struct Prepend;
    template<typename NEW, typename... EXISTING>
    struct Prepend<Product<EXISTING...>, NEW> {
        using type = Product<NEW, EXISTING...>;
    };
}


/*
Cases for multiplication:
B1 * B2

I(B1) * B2
B1 * I(B2)
I(B1) * I(B2)

P * B
P * I
B * P
I * P
P1 * P2
*/
template<typename A, typename B>
struct Multiply;
template<typename E>
struct Invert {
    using type = Inverse<E>;
};
namespace _helpers {
    template<typename NEW_FACTOR, typename... REST>
    struct AddFactor;
    template<typename FACTOR, typename FIRST, typename... REST>
    struct AddFactor<FACTOR, FIRST, REST...> {
        using reducible = typename Invert<FACTOR>::type;

        using type = std::conditional_t<std::is_same_v<reducible, FIRST>, Product<REST...>, typename Prepend<typename AddFactor<FACTOR, REST...>::type, FIRST>::type>;
    };
    template<typename FACTOR>
    struct AddFactor<FACTOR> {
        using type = Product<FACTOR>;
    };

    
    template<typename F1, typename F2>
    struct AddFactors {
        using type = typename AddFactor<F1, F2>::type;
    };
    template<typename F1, typename FIRST, typename... REST>
    struct AddFactors<F1, Product<FIRST, REST...>> {
        using type = typename Multiply<typename Multiply<F1, FIRST>::type, Product<REST...>>::type;
    };
    template<typename F1>
    struct AddFactors<F1, Product<>> {
        using type = F1;
    };
    template<typename F2, typename... F1>
    struct AddFactors<Product<F1...>, F2> {
        using type = typename AddFactors<F2, Product<F1...>>::type;
    };

    template<typename PRODUCT>
    struct UnpackProduct;
    template<typename... FACTORS>
    struct UnpackProduct<Product<FACTORS...>> {
        using type = Product<FACTORS...>;
    };
    template<typename FACTOR>
    struct UnpackProduct<Product<FACTOR>> {
        using type = FACTOR;
    };
    template<>
    struct UnpackProduct<Product<>> {
        using type = void;
    };
    template<typename PRODUCT>
    using UnpackProductT = typename UnpackProduct<PRODUCT>::type;
}
template<typename A, typename B>
struct Multiply {
    /*
    B1 * B2

    I(B1) * B2
    B1 * I(B2)
    I(B1) * I(B2)
    
    P1 * P2
    */

    static_assert(IsProductV<A> == IsProductV<B>, "Wrong overload called for P * B or B * P");
    using type = _helpers::UnpackProductT<typename _helpers::AddFactors<A, B>::type>;
};
template<typename B, typename... FACTORS>
struct Multiply<Product<FACTORS...>, B> {
    /*
    P * B
    P * I
    */
    
    using type = _helpers::UnpackProductT<typename _helpers::AddFactor<B, FACTORS...>::type>;
};
template<typename A, typename... FACTORS>
struct Multiply<A, Product<FACTORS...>> {
    /*
    B * P
    I * P
    */
    using type = typename Multiply<Product<FACTORS...>, A>::type;
};
template<typename A, typename B>
using MultiplyT = typename Multiply<A, B>::type;



template<typename E>
struct Invert<Inverse<E>> {
    using type = E;
};
template<typename... FACTORS>
struct Invert<Product<FACTORS...>> {
    template<typename PRODUCT, typename FACTOR>
    struct Prepend;
    template<typename NEW, typename... EXISTING>
    struct Prepend<Product<EXISTING...>, NEW> {
        using type = Product<NEW, EXISTING...>;
    };

    template<typename FIRST, typename... REST>
    struct InvertFactors {
        using type = typename _helpers::Prepend<typename InvertFactors<REST...>::type, typename Invert<FIRST>::type>::type;
    };
    template<typename LAST>
    struct InvertFactors<LAST> {
        using type = Product<LAST>;
    };
    using type = Inverse<typename InvertFactors<FACTORS...>::type>;
};
template<typename E>
using InvertT = typename Invert<E>::type;


template<typename NUM, typename DEN>
struct Divide {
    using type = MultiplyT<NUM, InvertT<DEN>>;
};
template<typename NUM, typename DEN>
using DivideT = typename Divide<NUM, DEN>::type;


}
}