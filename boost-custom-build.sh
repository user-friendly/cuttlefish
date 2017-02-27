#!/usr/bin/env bash

INSTALL_DIR="/home/pivanov/workspace/cuttlefish/libs"
WITH_LIBS="--with-system --with-thread --with-date_time --with-regex --with-log --with-chrono --with-filesystem"

./b2 --prefix=$INSTALL_DIR dll-path=$INSTALL_DIR/lib $WITH_LIBS toolset=clang variant=release link=shared runtime-link=shared threading=multi $1
