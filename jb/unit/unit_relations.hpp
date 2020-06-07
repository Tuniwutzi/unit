#pragma once

#include <type_traits>

namespace jb {
namespace unit {

// Valid Inverse: contains a base unit, no other relations
// Valid Product: only contains inverses and base units

// Trivial Product: a valid product that contains one or zero elements
// Ordered Product: a valid product with base units first and inverses later, as in Product<N1, N2, ..., Nn, Inverse<D1>, Inverse<D2>, ..., Inverse<Dd>>
// Normalized Product: an ordered, non-trivial product

// Expression: Anything that can be used as a base unit in the Unit-template, so either relations or base units
// Normalized Expression: an expression that is either void, a normalized product, a valid Inverse, or a base unit


/*
Representation of a valid product
*/
template<typename... FACTORS>
struct Product;
template<typename T>
struct IsProduct : public std::false_type {};
template<typename... FACTORS>
struct IsProduct<Product<FACTORS...>> : public std::true_type {};
template<typename T>
constexpr bool IsProductV = IsProduct<T>::value;

/*
Representation of a valid inverse
*/
template<typename T>
struct Inverse;
template<typename T>
struct IsInverse : public std::false_type {};
template<typename BASE_UNIT>
struct IsInverse<Inverse<BASE_UNIT>> : public std::true_type {};
template<typename T>
constexpr bool IsInverseV = IsInverse<T>::value;

namespace _helpers {
    template<typename A, typename B>
    struct ConcatFactors {
        private:
            template<typename LEFT>
            struct ConcatHelper {
                template<typename RIGHT>
                struct Append;
                
                template<typename... RIGHT_ELEMENTS>
                struct Append<Product<RIGHT_ELEMENTS...>> {
                    using type = Product<LEFT, RIGHT_ELEMENTS...>;
                };
                template<typename RIGHT>
                struct Append {
                    using type = Product<LEFT, RIGHT>;
                };
            };
            template<typename... LEFT_ELEMENTS>
            struct ConcatHelper<Product<LEFT_ELEMENTS...>> {
                template<typename RIGHT>
                struct Append {
                    using type = Product<LEFT_ELEMENTS..., RIGHT>;
                };
                template<typename... RIGHT_ELEMENTS>
                struct Append<Product<RIGHT_ELEMENTS...>> {
                    using type = Product<LEFT_ELEMENTS..., RIGHT_ELEMENTS...>;
                };
            };
        public:
            using type = typename ConcatHelper<A>::template Append<B>::type;
    };
    
    template<typename A, typename B>
    using ConcatFactorsT = typename ConcatFactors<A, B>::type;

    template<typename PRODUCT, typename FACTOR>
    struct ContainsFactor;
    template<typename NEEDLE, typename FIRST, typename... REST>
    struct ContainsFactor<Product<FIRST, REST...>, NEEDLE> {
        static const bool value = std::is_same_v<NEEDLE, FIRST> || ContainsFactor<Product<REST...>, NEEDLE>::value;
    };
    template<typename NEEDLE>
    struct ContainsFactor<Product<>, NEEDLE> {
        static const bool value = false;
    };
    template<typename PRODUCT, typename FACTOR>
    constexpr bool ContainsFactorV = ContainsFactor<PRODUCT, FACTOR>::value;

    template<typename PRODUCT>
    struct DistinctFactors;
    template<typename FIRST, typename... REST>
    struct DistinctFactors<Product<FIRST, REST...>> {
        using type = std::conditional_t<
            ContainsFactorV<Product<REST...>, FIRST>,
            typename DistinctFactors<Product<REST...>>::type,
            typename ConcatFactorsT<FIRST, typename DistinctFactors<Product<REST...>>::type>
        >;
    };
    template<>
    struct DistinctFactors<Product<>> {
        using type = Product<>;
    };
    template<typename PRODUCT>
    using DistinctFactorsT = typename DistinctFactors<PRODUCT>::type;
}

template<typename... FACTORS>
struct Product {
private:
    template<typename... FACTORS>
    struct IsValid;
    template<typename FIRST, typename... REST>
    struct IsValid<FIRST, REST...> {
        static constexpr bool value = !IsProductV<FIRST> && IsValid<REST...>::value;
    };
    template<>
    struct IsValid<> {
        static constexpr bool value = true;
    };
    static_assert(IsValid<FACTORS...>::value, "Product is not valid: must not contain more products");

    
    template<typename PRODUCT>
    struct NumDenSplit;
    template<typename FIRST, typename... REST>
    struct NumDenSplit<Product<FIRST, REST...>> {
        using numerators = _helpers::ConcatFactorsT<FIRST, typename NumDenSplit<Product<REST...>>::numerators>;
        using denominators = typename NumDenSplit<Product<REST...>>::denominators;
    };
    template<typename FIRST, typename... REST>
    struct NumDenSplit<Product<Inverse<FIRST>, REST...>> {
        using numerators = typename NumDenSplit<Product<REST...>>::numerators;
        using denominators = _helpers::ConcatFactorsT<Inverse<FIRST>, typename NumDenSplit<Product<REST...>>::denominators>;
    };
    template<>
    struct NumDenSplit<Product<>> {
        using numerators = Product<>;
        using denominators = Product<>;
    };

public:
    using numerators = typename NumDenSplit<Product<FACTORS...>>::numerators;
    using denominators = typename NumDenSplit<Product<FACTORS...>>::denominators;
    using distinct = typename _helpers::DistinctFactorsT<Product<FACTORS...>>;
    static constexpr size_t size = sizeof...(FACTORS);
};

template<typename B>
struct Inverse {
    static_assert(!IsProductV<B> && !IsInverseV<B>, "Inverse is not valid: B must be a base unit");
};

/*
Expects two normalized expressions as template arguments
The type definition contains a normalized a normalized expression that represents the result of the multiplication
*/
template<typename NORMALIZED_EXPRESSION_A, typename NORMALIZED_EXPRESSION_B>
struct Multiply;
/*
Expects a normalized expression as the template argument
The type definition contains a normalized expression representing the result of the inversion
*/
template<typename NORMALIZED_EXPRESSION>
struct Invert {
    using type = Inverse<NORMALIZED_EXPRESSION>;
};
namespace _helpers {
    template<typename PRODUCT>
    struct OrderProduct {
        using type = ConcatFactorsT<typename PRODUCT::numerators, typename PRODUCT::denominators>;
    };


    template<typename NEW_FACTOR, typename... REST>
    struct AddFactor;
    template<typename FACTOR, typename FIRST, typename... REST>
    struct AddFactor<FACTOR, FIRST, REST...> {
        using reducible = typename Invert<FACTOR>::type;

        using type = std::conditional_t<std::is_same_v<reducible, FIRST>, Product<REST...>, ConcatFactorsT<typename AddFactor<FACTOR, REST...>::type, FIRST>>;
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


    template<typename EXPRESSION>
    struct NormalizedExpression;
    // base unit, inverse or void:
    template<typename BASE_UNIT>
    struct NormalizedExpression {
        using type = BASE_UNIT;
    };
    // product:
    template<typename... FACTORS>
    struct NormalizedExpression<Product<FACTORS...>> {
        using type = typename UnpackProduct<typename OrderProduct<Product<FACTORS...>>::type>::type;
    };
    
    template<typename EXPRESSION>
    using NormalizedExpressionT = typename NormalizedExpression<EXPRESSION>::type;
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
    using type = _helpers::NormalizedExpressionT<typename _helpers::AddFactors<A, B>::type>;
};
template<typename B, typename... FACTORS>
struct Multiply<Product<FACTORS...>, B> {
    /*
    P * B
    P * I
    */
    
    using type = _helpers::NormalizedExpressionT<typename _helpers::AddFactor<B, FACTORS...>::type>;
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
    template<typename FIRST, typename... REST>
    struct InvertFactors {
        using type = _helpers::ConcatFactorsT<typename InvertFactors<REST...>::type, typename Invert<FIRST>::type>;
    };
    template<typename LAST>
    struct InvertFactors<LAST> {
        using type = Product<LAST>;
    };
    using type = Inverse<typename InvertFactors<FACTORS...>::type>;
};
template<typename E>
using InvertT = typename Invert<E>::type;


/*
Expects two normalized expressions as template arguments
The type definition contains the result of the division
*/
template<typename NUM, typename DEN>
struct Divide {
    using type = MultiplyT<NUM, InvertT<DEN>>;
};
template<typename NUM, typename DEN>
using DivideT = typename Divide<NUM, DEN>::type;


}
}
