#!/bin/bash
set -e
. ./build.sh

mkdir -p isodir/boot/grub

cp sysroot/boot/deros.kernel isodir/boot/deros.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "deros" {
	multiboot /boot/deros.kernel
}
EOF
grub-mkrescue -o deros.iso isodir
