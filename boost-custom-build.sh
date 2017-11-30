#!/usr/bin/env bash

INSTALL_DIR="$1/cuttlefish/libs"
echo "install dir is $INSTALL_DIR"

if [ ! -d "$INSTALL_DIR" ]; then
    echo "install dir not found or not accessible"
    exit 1
fi

WITH_LIBS="--with-system --with-thread --with-date_time --with-regex --with-log --with-chrono --with-filesystem"

echo "will execute: "
echo "./b2 --prefix=$INSTALL_DIR dll-path=$INSTALL_DIR/lib $WITH_LIBS toolset=clang variant=release link=shared runtime-link=shared threading=multi $2"

while true; do
    read -p "do you want to compile and install Boost? " yn
    case $yn in
        [Yy]* )
            ./b2 --prefix=$INSTALL_DIR dll-path=$INSTALL_DIR/lib $WITH_LIBS toolset=clang variant=release link=shared runtime-link=shared threading=multi $2
            break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
done
