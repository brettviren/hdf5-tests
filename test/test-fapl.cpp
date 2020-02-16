/*
$ g++ -Wno-deprecated --std=c++17 -I$HOME/opt/h5cpp/include -I $HOME/opt/hdf5/include -o test-fapl test-fapl.cpp -L$HOME/opt/hdf5/lib -lhdf5 -lhdf5_hl -lz -ldl -lm -Wl,-rpath=$HOME/opt/hdf5/lib
 */

#include <h5cpp/all>
int main()
{
    h5::fapl_t fapl =
        //h5::fclose_degree_weak |
        h5::fapl_core{{2048,1}};

    

    h5::fcpl_t fcpl =
        h5::file_space_page_size{4096} |
        h5::userblock{512};

    // |
    //     h5::file_image{};

    return 0;
};
