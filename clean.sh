#!/bin/bash
set -e
. ./config.sh

rm -f *.iso
rm -rf isodir
rm -rf sysroot

for PROJECT in $PROJECTS; do
	(cd $PROJECT && make clean)
done
