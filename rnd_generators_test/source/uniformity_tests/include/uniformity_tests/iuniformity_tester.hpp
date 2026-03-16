#pragma once

#include <vector>

namespace rnd_generators_test {

class IUniformityTester {
public:
    virtual ~IUniformityTester() = default;
    // Возвращает только p-value
    virtual double Run(std::vector<double>& u_values) const = 0;
};

} // namespace rnd_generators_test {
