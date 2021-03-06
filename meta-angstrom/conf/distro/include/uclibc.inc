require conf/distro/include/tclibc-uclibc.inc

# The things uclibc can provide.  We default to wanting uclibc to provide them.
PREFERRED_PROVIDER_virtual/libintl = "proxy-libintl"
PREFERRED_PROVIDER_virtual/gettext = "proxy-libintl"
#fix some iconv issues, needs to be adjusted when doing uclibc builds
PREFERRED_PROVIDER_virtual/libintl_avr32 = "proxy-libintl"
PREFERRED_PROVIDER_virtual/gettext_avr32 = "proxy-libintl"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}libc-initial = "uclibc-initial"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}libc-for-gcc = "uclibc"
PREFERRED_PROVIDER_virtual/libiconv-nativesdk = "eglibc-nativesdk"
PREFERRED_PROVIDER_virtual/libc-nativesdk = "eglibc-nativesdk"
PREFERRED_PROVIDER_virtual/${SDK_PREFIX}libc-initial-nativesdk  = "eglibc-initial-nativesdk"
PREFERRED_PROVIDER_virtual/${SDK_PREFIX}libc-nativesdk  = "eglibc-nativesdk"
PREFERRED_PROVIDER_virtual/${SDK_PREFIX}libc-for-gcc-nativesdk  = "eglibc-nativesdk"
# libc settings
DISTRO_FEATURES += "${@['', ' nls'][bb.data.getVar('ENABLE_BINARY_LOCALE_GENERATION', d, 1) == '1']}"
MACHINE_FEATURES += "${@['', ' bx'][bb.data.getVar('ARM_INSTRUCTION_SET', d, 1) == 'thumb']}"
# FIXME: We enable IPv4 per default to avoid alot of breakage.
# FIXME: Figure out an acceptable way to negotiate either
# FIXME: desired features or hard requirements, either top-down or bottom-up.
DISTRO_FEATURES += " ipv4"
