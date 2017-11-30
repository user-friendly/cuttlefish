CUTTLEFISH
======

ABOUT
-----

Learning C++ and software development in general.

Compilation
-----------

Custom libraries are in the ./libs directory. Include the directory
for both the complier and linker.

Configuration example, presuming $PROJECT_SOURCE_DIR is set as the
project's absolute home directory:

```
$> export CUTTLEFISH_LIBS_DIR="$PROJECT_SOURCE_DIR/libs"
$> cd $PROJECT_BUILD_DIR
$> $PROJECT_SOURCE_DIR/configure --with-sdl-prefix=$CUTTLEFISH_LIBS_DIR \
                                 --with-boost=$CUTTLEFISH_LIBS_DIR \
                                 CXXFLAGS="-I$CUTTLEFISH_LIBS_DIR/include" \
                                 CPPFLAGS="-I$CUTTLEFISH_LIBS_DIR/include" \
                                 CFLAGS="-I$CUTTLEFISH_LIBS_DIR/include"
```
