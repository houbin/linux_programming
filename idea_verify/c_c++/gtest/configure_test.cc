#include "configure.h"
#include "gtest/gtest.h"

TEST(Configure, addItem)
{
    Configure *pc = new Configure();

    ASSERT_TRUE(pc != NULL);

    pc->AddItem("A");
    pc->AddItem("B");
    pc->AddItem("C");
    pc->AddItem("A"); 

    EXPECT_EQ(pc->Size(), 3);
    EXPECT_EQ(pc->GetItem(0), "A");
    EXPECT_EQ(pc->GetItem(1), "B");
    EXPECT_EQ(pc->GetItem(2), "C");

    delete pc; 
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
