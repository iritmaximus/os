SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export HOST=i686-elf

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS="-O2 -g"
export CPPFLAGS=""

export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

export DESTDIR=$SYSROOT

if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
	export CC="$CC -isystem=$INCLUDEDIR"
fi
