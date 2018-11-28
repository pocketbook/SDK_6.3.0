GENCCODE_ASSEMBLY_TYPE=-a gcc
SO=so
SOBJ=so
A=a
LIBPREFIX=lib
LIB_EXT_ORDER=.58.2
COMPILE=/srv/jenkins/workspace/SDK-GEN/output-iMX6/host/usr/bin/arm-obreey-linux-gnueabi-gcc -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_REENTRANT  -DU_HAVE_ELF_H=1 -DU_HAVE_ATOMIC=1 -DU_HAVE_STRTOD_L=1  -DU_ATTRIBUTE_DEPRECATED= -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os  -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings   -c
LIBFLAGS=-I/usr/include -DPIC -fPIC
GENLIB=/srv/jenkins/workspace/SDK-GEN/output-iMX6/host/usr/bin/arm-obreey-linux-gnueabi-gcc -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os  -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings    -shared -Wl,-Bsymbolic
LDICUDTFLAGS=
LD_SONAME=-Wl,-soname -Wl,
RPATH_FLAGS=
BIR_LDFLAGS=-Wl,-Bsymbolic
AR=/srv/jenkins/workspace/SDK-GEN/output-iMX6/host/usr/bin/arm-obreey-linux-gnueabi-ar
ARFLAGS=r
RANLIB=/srv/jenkins/workspace/SDK-GEN/output-iMX6/host/usr/bin/arm-obreey-linux-gnueabi-ranlib
INSTALL_CMD=/usr/bin/install -c
