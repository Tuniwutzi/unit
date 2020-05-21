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
struct AdditionTest {
    template<typename T = decltype(std::declval<A>() + std::declval<B>())>
    using type = T;
};
template<typename A, typename B>
constexpr bool IsAdditionValidV = IsFunctorValidV<AdditionTest<A, B>>;