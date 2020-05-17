#include "stringification.hpp"

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
    jb::unit::Meters v(10);

    // Not allowed:
    // v = cm;
    // v = g;
    // v = 5;
    
    // Allowed:
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
    // different units
    // m == g;
    // m == c;
    // m == f;

    // same units
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
    jb::unit::CentiMeters cm(1000);
    jb::unit::Meters m(1000);
    jb::unit::KiloMeters km(1000);

    jb::unit::Grams g(10);
    jb::unit::DegreeCelsius c(10);
    jb::unit::DegreeFarenheit f(10);

    addsub(m, m);
    addsub(cm, cm);
    addsub(km, km);
    
    addsub(m, cm);
    addsub(m, km);
    addsub(km, cm);

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