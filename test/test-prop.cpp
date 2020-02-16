#include <h5cpp/all>
#if H5_VERSION_GE(1,10,1)
#else
error
#endif

int main()
{
    size_t sz = 2048;
    hbool_t tf = false;
    h5::fcpl_t fcpl = h5::userblock{512};
    h5::fapl_t fapl = h5::fapl_core{{sz, tf}};
    return 0;
}
