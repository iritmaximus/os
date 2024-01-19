#!/bin/bash
set -e
. ./config.sh

cd libc && DESTDIR="$SYSROOT" make $1
