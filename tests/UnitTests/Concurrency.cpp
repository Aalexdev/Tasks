#include <gtest/gtest.h>
#include <Tasks/Concurrency.hpp>

TEST(Concurrency, task_consructor){
    // TODO
}

TEST(Concurrency, taskid_constructor){
    Tasks::Concurrency concurrent(Tasks::TaskID(678));

    EXPECT_EQ(concurrent.id(), Tasks::TaskID(678));
    EXPECT_EQ(concurrent, Tasks::TaskID(678));
}

TEST(Concurrency, concurrency_constructor){
    Tasks::Concurrency base(Tasks::TaskID(678));
    Tasks::Concurrency concurrent(base);

    EXPECT_EQ(concurrent.id(), base.id());
    EXPECT_EQ(concurrent, base);
}

TEST(Concurrency, default_constructor){
    Tasks::Concurrency concurrent;

    EXPECT_EQ(concurrent.id(), Tasks::INVALID_TASK_ID);
    EXPECT_EQ(concurrent, Tasks::INVALID_TASK_ID);
}