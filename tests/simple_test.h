#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

namespace simple_test {
struct Test {
    const char* name;
    std::function<void()> func;
};

inline std::vector<Test>& registry() {
    static std::vector<Test> tests;
    return tests;
}

inline void add(const char* name, std::function<void()> func) {
    registry().push_back({name, std::move(func)});
}

inline int run_all() {
    int failed = 0;
    for (auto& t : registry()) {
        try {
            t.func();
            std::cout << "[OK] " << t.name << std::endl;
        } catch (const std::exception& e) {
            std::cout << "[FAIL] " << t.name << ": " << e.what() << std::endl;
            ++failed;
        }
    }
    std::cout << registry().size() - failed << '/' << registry().size()
              << " tests passed" << std::endl;
    return failed;
}
} // namespace simple_test

#define TEST_CASE(name) \
    void name(); \
    namespace { struct name##_registrar { name##_registrar() { ::simple_test::add(#name, name); } } name##_registrar_instance; } \
    void name()

#define REQUIRE(cond) \
    do { if(!(cond)) throw std::runtime_error(#cond); } while(0)

#define TEST_MAIN() \
    int main() { return ::simple_test::run_all(); }
