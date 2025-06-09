#include "simple_test.h"
#include "../Source/Math/Math.h"
#include "../Source/Math/Vector.hpp"

TEST_CASE(math_dist_and_square) {
    REQUIRE(Math::Square(3.0f) == 9.0f);

    Vector v1{0,0,0};
    Vector v2{3,4,0};
    REQUIRE(Math::Dist(v1, v2) == 5.0f);
}

TEST_MAIN();
