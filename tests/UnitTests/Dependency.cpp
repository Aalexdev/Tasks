#include <gtest/gtest.h>
#include <Tasks/Dependency.hpp>

TEST(Dependency, task_consructor){
    // TODO
}

TEST(Dependency, taskid_constructor){
    Tasks::Dependency dependency(Tasks::TaskID(678));

    EXPECT_EQ(dependency.id(), Tasks::TaskID(678));
    EXPECT_EQ(dependency, Tasks::TaskID(678));
}

TEST(Dependency, concurrency_constructor){
    Tasks::Dependency base(Tasks::TaskID(678));
    Tasks::Dependency dependency(base);

    EXPECT_EQ(dependency.id(), base.id());
    EXPECT_EQ(dependency, base);
}

TEST(Dependency, default_constructor){
    Tasks::Dependency dependency;

    EXPECT_EQ(dependency.id(), Tasks::INVALID_TASK_ID);
    EXPECT_EQ(dependency, Tasks::INVALID_TASK_ID);
}