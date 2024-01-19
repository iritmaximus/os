#!/bin/bash
set -e
. ./iso.sh

qemu-system-i386 -cdrom deros.iso
