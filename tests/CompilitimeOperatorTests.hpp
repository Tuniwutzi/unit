#pragma once



template<typename FUNCTOR_TEST>
struct IsFunctorValid {
    private:
        template<typename = typename FUNCTOR_TEST::type<>>
        static constexpr bool isFunctorValid(int) {
            return true;
        }
        static constexpr bool isFunctorValid(...) {
            return false;
        }

    public:
        static constexpr bool value = isFunctorValid(1);
};
template<typename FUNCTOR_TEST>
constexpr bool IsFunctorValidV = IsFunctorValid<FUNCTOR_TEST>::value;

template<typename FUNCTOR_TEST, bool VALID = IsFunctorValidV<FUNCTOR_TEST>>
struct FunctorResult {
    static_assert(VALID, "Functor is not valid, cannot get result type");
};
template<typename FUNCTOR_TEST>
struct FunctorResult<FUNCTOR_TEST, true> {
    using type = typename FUNCTOR_TEST::template type<>;
};
template<typename FUNCTOR_TEST>
using FunctorResultT = typename FunctorResult<FUNCTOR_TEST>::type;



template<typename A, typename B>
struct ComparisonTest {
    template<typename T = decltype(std::declval<A>() == std::declval<B>())>
    using type = T;
};
template<typename A, typename B>
constexpr bool IsComparisonValidV = IsFunctorValidV<ComparisonTest<A, B>>;


template<typename A, typename B>
struct AssignmentTest {
    template<typename T = decltype(std::declval<A>() = std::declval<B>())>
    using type = T;
};
template<typename A, typename B>
constexpr bool IsAssignmentValidV = IsFunctorValidV<AssignmentTest<A, B>>;


template<typename A, typename B>
struct CastTest {
    template<typename T = decltype(static_cast<A>(std::declval<B>()))>
    using type = T;
};
template<typename TO, typename FROM>
constexpr bool IsCastValidV = IsFunctorValidV<CastTest<TO, FROM>>;


template<typename A, typename B>
struct AdditionTest {
    template<typename T = decltype(std::declval<A>() + std::declval<B>())>
    using type = T;
};
template<typename A, typename B>
constexpr bool IsAdditionValidV = IsFunctorValidV<AdditionTest<A,B>>;
template<typename A, typename B>
using AdditionResultT = FunctorResultT<AdditionTest<A, B>>;
template<typename A, typename B, typename R>
constexpr bool ValidateAdditionResultV = std::is_same_v<AdditionResultT<A, B>, R>;


template<typename A, typename B>
struct SubtractionTest {
    template<typename T = decltype(std::declval<A>() - std::declval<B>())>
    using type = T;
};
template<typename A, typename B>
constexpr bool IsSubtractionValidV = IsFunctorValidV<SubtractionTest<A, B>>;
template<typename A, typename B>
using SubtractionResultT = FunctorResultT<SubtractionTest<A, B>>;
template<typename A, typename B, typename R>
constexpr bool ValidateSubtractionResultV = std::is_same_v<SubtractionResultT<A, B>, R>;


template<typename A, typename B>
struct MultiplicationTest {
    template<typename T = decltype(std::declval<A>() * std::declval<B>())>
    using type = T;
};
template<typename A, typename B>
constexpr bool IsMultiplicationValidV = IsFunctorValidV<MultiplicationTest<A, B>>;
template<typename A, typename B>
using MultiplicationResultT = FunctorResultT<MultiplicationTest<A, B>>;
template<typename A, typename B, typename R>
constexpr bool ValidateMultiplicationResultV = std::is_same_v<MultiplicationResultT<A, B>, R>;


template<typename A, typename B>
struct DivisionTest {
    template<typename T = decltype(std::declval<A>() / std::declval<B>())>
    using type = T;
};
template<typename A, typename B>
constexpr bool IsDivisionValidV = IsFunctorValidV<DivisionTest<A, B>>;
template<typename A, typename B>
using DivisionResultT = FunctorResultT<DivisionTest<A, B>>;
template<typename A, typename B, typename R>
constexpr bool ValidateDivisionResultV = std::is_same_v<DivisionResultT<A, B>, R>;
