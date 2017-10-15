#!/bin/bash
/mnt/big/work/mxe-linux/usr/bin/i686-w64-mingw32.static.posix-cmake . -Bbuild  && pushd build && make -j8; popd
