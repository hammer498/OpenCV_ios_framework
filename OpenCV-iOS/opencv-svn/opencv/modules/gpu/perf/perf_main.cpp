#include "perf_precomp.hpp"

#ifdef HAVE_CUDA

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    perf::TestBase::Init(argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main()
{
    printf("OpenCV was built without CUDA support\n");
    return 0;
}

#endif
