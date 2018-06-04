CUTTLEFISH
======

ABOUT
-----

A game engine for OpenTTD/Simutrans like games.

The main drive for this project is learning C++, 3D computer graphics and game design.

Design direction
----------------

I would like for this project to be driven by a Data-Oriented Design. In it's essence DOD focuses on the data at hand and how to most efficiently transform it, not so much on the source code. This project's aim (apart from learning) is to build a game engine for a specific game and not a generic framework for any type of game.

See [Mike Acton](https://dataorientedprogramming.wordpress.com/tag/mike-acton/)'s blog page on DOD.

What hardware platform will this program be running on?
Currently, it is assumed it will only run on consumer desktop personal computers.

What are average specifications of PCs used for gaming currently?
TODO Find statistics.

What are the game needs in terms of performance?
TODO Based on features?

Code Standards
--------------

Code style? Not decided yet.

Not allowed, unless necessary:
* Exceptions
* Templates (except when really needed)
* iostream
* Multiple inheritance
* Operator overloading (unless very simple)
* RTTI
* STL (really?)
* Stock allocators. Use custom bulk allocators.

These restrictions do not apply to tools, unless there are severe performance issues.

Custom Boost
------------

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
