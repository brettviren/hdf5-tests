/*
$ g++ -Wno-deprecated --std=c++17 -I$HOME/opt/h5cpp/include -I $HOME/opt/hdf5/include -o test-hdf-serialize-speed test-hdf-serialize-speed.cpp -L$HOME/opt/hdf5/lib -lhdf5 -lhdf5_hl -lz -ldl -lm -Wl,-rpath=$HOME/opt/hdf5/lib

 */


#include <h5cpp/all>
#include "hdf5_hl.h" 

#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
#include <chrono>

// using file_image
// = impl::fapl_call< impl::fapl_args<hid_t,void*,size_t>,H5Pset_file_image>;



int main(int argc, char* argv[])
{
    assert(argc > 1);

    char* filename = argv[1];

    void* buf=0;
    size_t siz=0;
    h5::fd_t fd = h5::open(filename, H5F_ACC_RDWR);
    {
        const size_t siz1 = H5Fget_file_image(fd, NULL, 0);
        assert(siz1 > 0);
        buf = malloc(siz1);
        size_t siz2 = H5Fget_file_image(fd, buf, siz1);
        assert(siz1 == siz2);
        siz = siz1;
    }
    std::cout << "opened file " << filename << " of size " << siz << " B\n";

    int times = 1000;
    if (argc > 2) {
        times = atoi(argv[2]);
    }

    unsigned flags = H5LT_FILE_IMAGE_DONT_COPY | H5LT_FILE_IMAGE_DONT_RELEASE;
    h5::fcpl_t fcpl = h5::default_fcpl;
    h5::fapl_t fapl = h5::fclose_degree_weak | h5::fapl_core{{2048,false}} | h5::file_image{{buf, siz}};

    auto beg = std::chrono::high_resolution_clock::now();
    for (int count=0; count<times; ++count) {


        h5::fd_t fd2 = h5::create("in-memory.hdf",
                                  H5F_ACC_TRUNC,
                                  fcpl, 
                                  fapl);
        
        /// This works, but leaks like, ~1B per call.
        // hid_t file_id = H5LTopen_file_image(buf, siz, flags);
        // H5Fclose(file_id);

        // std::cout << "opened file image\n";
    }



    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-beg;
    double seconds = diff.count();
    double rate = times/seconds;

    std::cout << seconds << " s,\t"
              << times << "\t"
              << siz << " B,\t"
              << rate << " Hz,\t"
              << 1000./rate << " ms\n";
    return 0;
}
