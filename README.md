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
* STL (is it really needed?)
* Stock allocators. Use custom bulk allocators.

These restrictions do not apply to tools, unless there are severe performance issues.

Graphic APIs
------------

At the moment, the only API used is OpenGL. Related code should reside under the 'cuttlefish::opengl' namespace. Additional implementations (such as Vulkan or DirectX) should go in a respective namespace.

Any usage of API specific symbols outside the appropriate namespace is forbidden, except the interface. Drivers will deal with graphics related game objects and optimizations for that driver. I'll try to avoid complicated OOP solutions here since OpenGL might be the only API used ever.

Building
--------

Custom libraries are in the `/home/dev/cuttlefish/lib` directory. Include the directory for both the complier and linker.

Configuration example, presuming `/home/dev/cuttlefis` is the project's absolute directory and the build directory is `/home/dev/cuttlefish/bin`:

```shell
$> export CUTTLEFISH_LIBS_DIR="/home/dev/cuttlefish/libs"
$> cd /home/dev/cuttlefish/bin
$> /home/dev/cuttlefish/configure --with-sdl-prefix=$CUTTLEFISH_LIBS_DIR \
                                 --with-boost=$CUTTLEFISH_LIBS_DIR \
                                 CXXFLAGS="-I$CUTTLEFISH_LIBS_DIR/include" \
                                 CPPFLAGS="-I$CUTTLEFISH_LIBS_DIR/include" \
                                 CFLAGS="-I$CUTTLEFISH_LIBS_DIR/include"
```

Note that the build directory can be outside the project's directory.

Run `autoreconf -vfi` first and then the `configure.sh` script. Without any arguments it will use the current directory as source and `./bin` as the build directory.

Change to the build directory and execute `make` there.

Custom Boost
------------

Clone the Github repository and make sure all submodules are initialized ([see this link](https://github.com/boostorg/boost/wiki/Getting-Started)). The compilation and installation guide for 1.68.0 can be found [here](http://www.boost.org/doc/libs/1_63_0/more/getting_started/unix-variants.html#prepare-to-use-a-boost-library-binary). Before initializing the submodules, make sure the version you require is checked out (currently, the minimum boost version required is 1.68.0). Another easier way is to simply grab a tar ball from [Boost.org](https://www.boost.org/users/download/).

There are two shell scripts provided that can help with compiling and installation: `boost-bootstrap.sh` and `boost-build.sh`. The first one prepares for compilation and the second one builds and installs the necessary libraries. Note that both scripts will need to be executed within Boost's source root directory and the `boost-bootstrap.sh` requires one argument - the absolute path to Cuttlefish's source directory. The compiler (toolset) currently set is clang. Simply modify the bootstrap script to change it.

```shell
$> cd /home/dev/boost_1_68_0
$> /home/dev/cuttlefish/boost-bootstrap.sh /home/dev/cuttlefish/lib
$> /home/dev/cuttlefish/boost-build.sh
```
The above example should install all necessary Boost files to `/home/dev/cuttlefish/libs/include` and `/home/dev/cuttlefish/libs/lib`. Make sure those folders are created prior to using the build script.

**Never run any of the scripts as root!**

TODOs
-----

* Update this document.
* What are average specifications of PCs used for gaming currently?
* What are the game needs in terms of performance?
* Use a logging library instead of standard error.
* ~~Remove all the std::exit() calls from the renderer constructor.~~ Class no longer exists, but it's probably a good idea to not abruptly terminate the program from within constructors.
* Namespace header file guards?
