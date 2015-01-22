CUTTLEFISH
======

ABOUT
-----

HTTP 1.1 Proxy server.

Purpose of this program is learning C++ & GNU Autotools.


CUSTOM BOOST BUILD
------------------

Building the Boost library:
```shell
$ cd /home/jerry/workspace/boost_1_55_0  
# Build the Boost builder, bjam.  
$ bootstrap.sh  
# Build all the binaries in the stage folder. Separate binaries can be build using --with-<library>.  
$ ./b2 -q -j 2 toolset=clang variant=debug link=shared threading=multi runtime-link=shared address-model=64 stage 2>&1 | tee staged.log  
# If all goes well, install the library. This should copy binary files from the stage/lib directory into the installation dir and all headers in the installation dir's include directory.
$ ./b2 -q -j 2 --prefix=/home/pivanov/workspace/boost_1_55_0/usr/local toolset=clang variant=debug link=shared threading=multi runtime-link=shared address-model=64 install 2>&1 | tee install.log  
```

USING THE CUSTOM BOOST BUILD
----------------------------
```shell
# Helper variable, set to the custom Boost's installation directory.  
$ export BOOST_ROOT=/home/jerry/workspace/boost_1_55_0/usr/local  
$ cd /tmp/build  
# Running the configure script.  
# TODO: Do we need the --with-boost* parameters? $BOOST_ROOT should be recognized by the Boost macros...  
$ /path/to/project/configure CFLAGS="-I${BOOST_ROOT}/include" CXXFLAGS="-I${BOOST_ROOT}/include" LDFLAGS="-L${BOOST_ROOT}/lib -rpath ${BOOST_ROOT}/lib" --enable-debug --enable-pedantic --with-boost=${BOOST_ROOT} --with-boost-libdir=${BOOST_ROOT}/lib  
```
