#include <iostream>
#include <vector>
#include <tuple>
#include <span>
#include <chrono>

class Forces {
protected:
    std::vector<double> rod_force_x;
    std::vector<double> rod_force_y;
    std::vector<double> rod_torque;
public:
    Forces(size_t n) : rod_force_x(n, 1.0), rod_force_y(n, 1.0), rod_torque(n, 1.0) {}

    std::tuple<const std::vector<double>&, const std::vector<double>&, const std::vector<double>&> getForcesTie() const {
        return std::tie(rod_force_x, rod_force_y, rod_torque);
    }

    std::tuple<std::span<const double>, std::span<const double>, std::span<const double>> getForcesSpan() const {
        return std::make_tuple(std::span<const double>(rod_force_x), std::span<const double>(rod_force_y), std::span<const double>(rod_torque));
    }
};

void benchmarkTie(const Forces& forces, size_t iterations) {
    for (size_t i = 0; i < iterations; ++i) {
        auto [fx, fy, torque] = forces.getForcesTie();
        volatile double sum = 0;
        for (const auto& val : fx) sum += val;
        for (const auto& val : fy) sum += val;
        for (const auto& val : torque) sum += val;
    }
}

void benchmarkSpan(const Forces& forces, size_t iterations) {
    for (size_t i = 0; i < iterations; ++i) {
        auto [fx, fy, torque] = forces.getForcesSpan();
        volatile double sum = 0;
        for (const auto& val : fx) sum += val;
        for (const auto& val : fy) sum += val;
        for (const auto& val : torque) sum += val;
    }
}

int main() {
    const size_t n = 1000000;
    const size_t iterations = 1000;
    Forces forces(n);

    auto start = std::chrono::high_resolution_clock::now();
    benchmarkTie(forces, iterations);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tie method elapsed time: " << elapsed.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    benchmarkSpan(forces, iterations);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Span method elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}

