#include "stringification.hpp"
#include "CompilitimeOperatorTests.hpp"

#include <jb/unit.hpp>

#include <iostream>
#include <sstream>

const jb::unit::CentiMeters cm(100);
const jb::unit::Meters m(100);
const jb::unit::KiloMeters km(100);

const jb::unit::Grams g(1000);

const jb::unit::DegreeCelsius c(100);
const jb::unit::DegreeFarenheit f(100);


void implicitConversions() {
    using namespace jb::unit;
    jb::unit::Meters v(10);

    // Not allowed:
    static_assert(!IsAssignmentValidV<Meters, Grams>, "Meters should not be assignable from grams");
    // v = cm;
    // v = g;
    // v = 5;
    
    // Allowed:
    static_assert(IsAssignmentValidV<Meters, Meters>, "Meters should be assignable from meters");
    v = m;
    v = km;
}

void explicitConversions() {
    jb::unit::Meters v(10);

    // Not allowed:
    // static_cast<jb::unit::Meters>(jb::unit::Grams(5));
    
    // Allowed:
    static_cast<jb::unit::Meters>(cm);
}

void conversionBetweenBaseUnits() {
    jb::unit::DegreeCelsius c(10);
    jb::unit::DegreeFarenheit f(10);

    std::cout << c << ", " << f << std::endl;

    c = jb::unit::DegreeFarenheit(10);
    f = jb::unit::DegreeCelsius(10);

    std::cout << c << ", " << f << std::endl;

    jb::unit::Meters m(10);
    jb::unit::Grams g(10);

    // g = m;
    // m = g;

    std::cout << std::endl;
}



void comparisons() {
    using namespace jb::unit;
    static_assert(!IsComparisonValidV<Meters, Grams>, "Meters should not be comparable to grams");
    // different units
    // m == g;
    // m == c;
    // m == f;

    // same units
    static_assert(IsComparisonValidV<Meters, Meters>, "Meters should be comparable to meters");
    m == m;
    m == cm;
    cm == m;
    km == m;
    m == km;

    // different but comparable units
    c == f;
    f == c;
}

template<typename A, typename B>
void addsub(A a, B b) {
    std::cout << a << " + " << b << " = " << (a+b) << std::endl;
    if constexpr (!std::is_same_v<std::decay_t<A>, std::decay_t<B>>) {
        std::cout << b << " + " << a << " = " << (b+a) << std::endl;
    }
    
    std::cout << a << " - " << b << " = " << (a-b) << std::endl;
    if constexpr (!std::is_same_v<std::decay_t<A>, std::decay_t<B>>) {
        std::cout << b << " - " << a << " = " << (b-a) << std::endl;
    }
}
void addition() {
    using namespace jb::unit;

    jb::unit::CentiMeters cm(1000);
    jb::unit::Meters m(1000);
    jb::unit::KiloMeters km(1000);

    jb::unit::Grams g(10);
    jb::unit::DegreeCelsius c(10);
    jb::unit::DegreeFarenheit f(10);

    static_assert(IsAdditionValidV<Meters, CentiMeters>, "Meters should be addable to centimeters");

    addsub(m, m);
    addsub(cm, cm);
    addsub(km, km);
    
    addsub(m, cm);
    addsub(m, km);
    addsub(km, cm);


    static_assert(!IsAdditionValidV<Meters, Grams>, "Meters should not be addable to grams");
    // completely different units
    // addsub(g, m);
    // addsub(g, f);

    // implicitly convertible units, but with different base_units
    // Future: we can _maybe_ allow this for units with the same 0-element (so NOT fahrenheit and celsius)
    // addsub(c, f);
}

int main() {
    implicitConversions();
    explicitConversions();
    conversionBetweenBaseUnits();
    comparisons();
    addition();

    return 0;
}