#include <jb/unit.hpp>

#include <iostream>

const jb::unit::CentiMeters cm(100);
const jb::unit::Meters m(100);
const jb::unit::KiloMeters km(100);

const jb::unit::Grams g(1000);

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

    std::cout << c.count() << "°C, " << f.count() << "°F" << std::endl;

    c = jb::unit::DegreeFarenheit(10);
    f = jb::unit::DegreeCelsius(10);

    std::cout << c.count() << "°C, " << f.count() << "°F" << std::endl;
}

int main() {
    implicitConversions();
    explicitConversions();
    conversionBetweenBaseUnits();

    return 0;
}