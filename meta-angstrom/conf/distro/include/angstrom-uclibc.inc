# uclibc:
require conf/distro/include/uclibc.inc

PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}binutils = "binutils-cross"
PREFERRED_PROVIDER_linux-libc-headers = "linux-libc-headers"

USE_NLS_glib-2.0 = "yes"
USE_NLS_glib-2.0-native = "yes"
USE_NLS_gcc-cross = "no"

TARGET_OS_bfin = "uclinux-uclibc"

#Gcc will die with 'internal consistency error when using the above optimizations
#with gcc-4.2.1-atmel.1.0.3 (and probably most other avr32 gcc ports).
#However, some packages require optimizations to compile (e.g. libmad).
#It appears the guilty optimization is "-frename-registers", leaving that one 
#out allows the build to proceed normally.  -fexpensive-optimizations may be OK,
#it was removed while debugging an issue that ultimately turned out to be due
#to the ICE fixed by gcc-pr32889.patch.  It needs to be tested again. 
#Note that this testing was done without the gcc-pr32889.patch.
FULL_OPTIMIZATION_avr32 = "-Os -pipe ${DEBUG_FLAGS}"

TARGET_LINK_HASH_STYLE = "${@['-Wl,--hash-style=gnu',''][bb.data.getVar('TARGET_ARCH',d,1) in ['mips', 'mipsel', 'mips64', 'mips64el', 'avr32']]}"
