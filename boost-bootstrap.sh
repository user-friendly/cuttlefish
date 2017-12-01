#!/usr/bin/env bash

INSTALL_DIR="$1/cuttlefish/libs"
echo "install dir is $INSTALL_DIR"

if [ ! -d "$INSTALL_DIR" ]; then
    echo "install dir not found or not accessible"
    exit 1
fi

WITH_LIBS="system,thread,date_time,regex,log,chrono,filesystem"

echo "will execute: "
echo "./bootstrap.sh --prefix=$INSTALL_DIR  --with-libraries=$WITH_LIBS -with-toolset=clang"

while true; do
    read -p "do you want to prepare Boost for building? " yn
    case $yn in
        [Yy]* )
            ./bootstrap.sh --prefix=$INSTALL_DIR  --with-libraries=$WITH_LIBS -with-toolset=clang
            break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
done
