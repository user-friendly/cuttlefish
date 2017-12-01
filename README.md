CUTTLEFISH
======
---
ABOUT
-----

Learning C++ and software development in general.

Custom Boost
----------------

Clone the Github repository and make sure all submodules are initialized ([see this link](https://github.com/boostorg/boost/wiki/Getting-Started)). The compilation and installation guide for 1.63.0 can be found [here](http://www.boost.org/doc/libs/1_63_0/more/getting_started/unix-variants.html#prepare-to-use-a-boost-library-binary). Before initializing the submodules, make sure the version you require is checked out (currently, the minimum boost version required is 1.63.0).

There are two shell scripts provided that can help with compiling and installation: `boost-bootstrap.sh` and `boost-build.sh`. The first one prepares for compilation and the second one builds and installs the necessary libraries. Note that both scripts will need to be executed within Boost's source root directory and the `boost-bootstrap.sh` requires one argument - the absolute path to Cuttlefish's source directory.

```shell
$> cd /home/dev/boost_1_63_0
$> /home/dev/cuttlefish/boost-bootstrap.sh /home/dev/cuttlefish
$> /home/dev/cuttlefish/boost-build.sh
```
The above example should install all necessary Boost files to `/home/dev/cuttlefish/libs/include` and `/home/dev/cuttlefish/libs/lib`. Make sure those folders are created prior to using the build script.

**Never run any of the scripts as root!**

Compilation
-----------

Custom libraries are in the `./libs` directory. Include the directory
for both the complier and linker.

Configuration example, presuming `$PROJECT_SOURCE_DIR` is set as the
project's absolute home directory:

```shell
$> export CUTTLEFISH_LIBS_DIR="$PROJECT_SOURCE_DIR/libs"
$> cd $PROJECT_BUILD_DIR
$> $PROJECT_SOURCE_DIR/configure --with-sdl-prefix=$CUTTLEFISH_LIBS_DIR \
                                 --with-boost=$CUTTLEFISH_LIBS_DIR \
                                 CXXFLAGS="-I$CUTTLEFISH_LIBS_DIR/include" \
                                 CPPFLAGS="-I$CUTTLEFISH_LIBS_DIR/include" \
                                 CFLAGS="-I$CUTTLEFISH_LIBS_DIR/include"
```
