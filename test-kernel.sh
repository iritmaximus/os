#!/bin/bash
set -e
. ./config.sh

cd kernel && DESTDIR="$SYSROOT" make $1
