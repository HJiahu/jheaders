#include <gtest/gtest.h>

int main (int argc, char* argv[])
{
    testing::InitGoogleTest (&argc, argv);
    auto result = RUN_ALL_TESTS();
#ifdef _MSC_VER
    system ("pause");
#endif
    return result;
}