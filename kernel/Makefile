CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

HOSTARCH?=i386
ARCHDIR=arch/$(HOSTARCH)

KERNEL_ARCH_OBJS=\
	$(ARCHDIR)/boot.o \
	$(ARCHDIR)/page_enable.o \
	$(ARCHDIR)/paging.o \
	$(ARCHDIR)/tty.o \

KERNEL_OBJS=\
	$(KERNEL_ARCH_OBJS) \
	kernel/kernel.o \

OBJS=\
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o \

LINK_LIST=\
	$(LDFLAGS) \
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJS) \
	$(LIBS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .s

all: deros.kernel

deros.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot deros.kernel

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.s.o:
	$(AS) $< -o $@

.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f deros.kernel
	rm -f $(ARCHDIR)/*.{o,d}
	rm -f kernel/*.{o,d}

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -r include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: deros.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp deros.kernel $(DESTDIR)$(BOOTDIR)
