#include <cmath>
#include <cstdio>
#include <chrono>
#include <string>
#include <numbers>

constexpr double PI = std::numbers::pi;
constexpr double TWO_PI = 2.0 * PI;
constexpr double INV_TWO_PI = 1.0 / (2.0 * PI);
constexpr double SIX_PI = 6.0 * PI;
constexpr double SIX_HUNDRED_PI = 600.0 * PI;

double r1(double angle) {
    while (angle > TWO_PI)
        angle -= TWO_PI;
    while (angle < 0)
        angle += TWO_PI;
    return angle;
}

double r2(double angle) {
    angle = fmod(angle, TWO_PI);
    if (angle < 0.0)
        angle += TWO_PI;
    return angle;
}

double r3(double angle) {
    return angle - TWO_PI * std::floor(angle * INV_TWO_PI);
}

class Timer {
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    std::string elapsed_time() const {
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return std::to_string(elapsed.count()) + " us";
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
};

struct TestSet {
    double start, end, increment;
};

void tester(const std::string& tag, double (*test)(double), bool noisy) {
    static const TestSet tests[] = {
        { -SIX_PI, SIX_PI, 0.001 },
        // { -SIX_HUNDRED_PI, SIX_HUNDRED_PI, 0.1 },
    };

    Timer timer;
    timer.start();

    for (const auto& testSet : tests) {
        for (double angle = testSet.start; angle < testSet.end; angle += testSet.increment) {
            double result = test(angle);
            if (result < 0.0 || result >= TWO_PI)
                noisy = true;
            if (noisy)
                std::printf("%12.8f : %12.8f\n", angle, result);
        }
    }

    timer.stop();
    std::printf("%s %s\n", tag.c_str(), timer.elapsed_time().c_str());
}

int main() {
    tester("r1", r1, false);
    tester("r2", r2, false);
    tester("r3", r3, false);
    tester("r1", r1, false);
    tester("r2", r2, false);
    tester("r3", r3, false);
    tester("r1", r1, false);
    tester("r2", r2, false);
    tester("r3", r3, false);
    tester("r1", r1, false);
    tester("r2", r2, false);
    tester("r3", r3, false);
    return 0;
}
