#include <gtest/gtest.h>
#include <Tasks/Importance.hpp>

TEST(Importance, float_constructor){
    static constexpr float VALUE = 9863.f;
    Tasks::Importance importance(VALUE);

    EXPECT_EQ(importance.get(), VALUE);
    EXPECT_EQ(importance, VALUE);
}

TEST(Importance, importance_constructor){
    static constexpr float VALUE = 8762.f;
    Tasks::Importance base(VALUE);
    Tasks::Importance importance(base);
    
    EXPECT_EQ(importance.get(), base.get());
    EXPECT_EQ(importance, base);
}

TEST(Importance, default_constructor){
    Tasks::Importance importance;

    EXPECT_EQ(importance.get(), Tasks::Importance::DEFAULT);
    EXPECT_EQ(importance, Tasks::Importance::DEFAULT);
}