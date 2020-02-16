#include <h5cpp/all>
#include <string>


int main(int argc, char* argv[])
{
    std::string crash_after = "";
    if (argc > 1) {
        crash_after = argv[1];
    }

    std::string fname = argv[0];
    fname += ".hdf";
    auto fd = h5::create(fname.c_str(), H5F_ACC_TRUNC);
    if (crash_after == "open") {
        abort();
    }
    auto frame = h5::create<short>(fd,"big",
                                   h5::current_dims{2560, 6000},
                                   h5::chunk{10, 100});
    if (crash_after == "make") {
        abort();
    }

    H5Fflush(fd, H5F_SCOPE_LOCAL);

    if (crash_after == "flush") {
        abort();
    }

    return 0;
}
