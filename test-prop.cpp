#include <h5cpp/all>
#if H5_VERSION_GE(1,10,1)
#else
error
#endif

int main()
{
    // h5::fapl_t fapl = h5::fclose_degree_weak |
    //     h5::fapl_core{2048,1} |
    //     h5::core_write_tracking{false,1} |
    //         h5::fapl_family{H5F_FAMILY_DEFAULT,0} ;
//    h5::fapl_t fapl = h5::fclose_degree_weak | h5::fapl_core{2048, true};
    size_t sz = 2048;
    hbool_t tf = true;
    h5::fcpl_t fcpl = h5::userblock{512};
    auto fapl = h5::default_fapl | h5::fapl_core{2048, true};
    return 0;
}
