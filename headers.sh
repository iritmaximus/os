#!/bin/bash
set -e
. ./config.sh

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
	(cd $PROJECT && DESTDIR="$SYSROOT" make install-headers);
done
