#!/usr/bin/env waf

import os.path as osp

VERSION='0.0.0'
APPNAME='zio'

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx')
    opt.load('waf_unit_test')

def configure(cfg):
    cfg.env.CXXFLAGS += ['-std=c++17', '-g', '-O2']
    cfg.load('compiler_cxx')
    cfg.load('waf_unit_test')

    cfg.env.LIBPATH_HDF5 = [osp.expandvars('$HOME/opt/hdf5/lib')]
    cfg.env.INCLUDES_HDF5 = [osp.expandvars('$HOME/opt/hdf5/include')]
    cfg.env.INCLUDES_H5CPPORG = [osp.expandvars('$HOME/opt/h5cpp/include')]

    cfg.check_cxx(
        msg = "Checking for HDF5",
        header_name = ["hdf5.h", "hdf5_hl.h"],
        lib = ['hdf5_hl', 'hdf5', 'z'],
        uselib_store = 'HDF5',
        use = ['HDF5'],
    )

    cfg.check_cxx(
        msg = "Checking for h5cpp.org",
        header_name = 'h5cpp/all',
        uselib_store = 'H5CPPORG',
        use = ['HDF5', 'H5CPPORG'],
    )

def build(bld):
    uses='HDF5 H5CPPORG'.split()

    rpath = [bld.env["PREFIX"] + '/lib', bld.path.find_or_declare(bld.out_dir)]
    print (rpath)
    rpath += [bld.env["LIBPATH_%s"%u][0] for u in uses if bld.env["LIBPATH_%s"%u]]
    rpath = list(set(rpath))
             
    tsources = bld.path.ant_glob('test/test*.cpp')
    for tmain in tsources:
        bld.program(features = 'test cxx',
                    source = [tmain], target = tmain.name.replace('.cpp',''),
                    ut_cwd = bld.path,
                    install_path = None,
                    includes = ['inc','build','test'],
                    rpath = rpath,
                    use = uses)
    
    from waflib.Tools import waf_unit_test
    bld.add_post_fun(waf_unit_test.summary)
