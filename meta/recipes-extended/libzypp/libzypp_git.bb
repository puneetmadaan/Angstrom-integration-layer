HOMEPAGE = "http://en.opensue.org/Portal:Libzypp"
DESCRIPTION  = "The ZYpp Linux Software management framework"

LICENSE  = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=11fccc94d26293d78cb4996cb17e5fa7"

inherit cmake gettext

DEPENDS  = "rpm boost curl libxml2 zlib sat-solver expat openssl udev"

# rpmdb2solv from sat-solver is run from libzypp
RDEPENDS_${PN} = "sat-solver"

S = "${WORKDIR}/git"
SRCREV = "15b6c52260bbc52b3d8e585e271b67e10cc7c433"
PV = "0.0-git${SRCPV}"
PR = "r9"

SRC_URI = "git://gitorious.org/opensuse/libzypp.git;protocol=git \
           file://no-doc.patch \
           file://rpm5.patch \
           file://rpm5-no-rpmdbinit.patch \
	   file://config-release.patch \
	   file://libzypp-pokyarch.patch \
          "

SRC_URI_append_mips = " file://mips-workaround-gcc-tribool-error.patch"

# ARM specific global constructor workaround
SRC_URI_append_arm  = " file://arm-workaround-global-constructor.patch"

FILES_${PN} += "${libdir}/zypp ${datadir}/zypp ${datadir}/icons"
FILES_${PN}-dev += "${datadir}/cmake"

EXTRA_OECMAKE += "-DLIB=lib"

PACKAGE_ARCH = "${MACHINE_ARCH}"

AVOID_CONSTRUCTOR = ""

# Due to an ARM specific compiler issue
AVOID_CONSTRUCTOR_arm = "true"

# Due to a potential conflict with '_mips' being a define
AVOID_CONSTRUCTOR_mips = "true"

do_archgen () {
	# We need to dynamically generate our arch file based on the machine
	# configuration
	echo "/* Automatically generated by the libzypp recipes */" 		 > zypp/poky-arch.h
	echo "/* Avoid Constructor: ${AVOID_CONSTRUCTOR} */" 			 >> zypp/poky-arch.h
	echo ""									>> zypp/poky-arch.h
	echo "#ifndef POKY_ARCH_H"						>> zypp/poky-arch.h
	echo "#define POKY_ARCH_H 1"						>> zypp/poky-arch.h
	echo "#define Arch_machine Arch_${MACHINE_ARCH}"			>> zypp/poky-arch.h
	echo "#endif /* POKY_ARCH_H */"						>> zypp/poky-arch.h
	echo ""									>> zypp/poky-arch.h
	if [ "${AVOID_CONSTRUCTOR}" != "true" ]; then
	  echo "#ifdef DEF_BUILTIN"						>> zypp/poky-arch.h
	  echo "/* Specify builtin types */"					>> zypp/poky-arch.h
	  for each_arch in ${PACKAGE_ARCHS} ; do
		case "$each_arch" in
			all | any | noarch)
				continue;;
		esac
		echo "    DEF_BUILTIN( ${each_arch} );"				>> zypp/poky-arch.h
	  done
	  echo "#endif /* DEF_BUILTIN */"						>> zypp/poky-arch.h
	  echo ""									>> zypp/poky-arch.h
	fi
	echo "#ifdef POKY_EXTERN_PROTO"						>> zypp/poky-arch.h
	echo "/* Specify extern prototypes */"					>> zypp/poky-arch.h
	for each_arch in ${PACKAGE_ARCHS} ; do
		case "$each_arch" in
			all | any | noarch)
				continue;;
		esac
		echo "  extern const Arch Arch_${each_arch};"			>> zypp/poky-arch.h
	done
	echo "#endif /* POKY_EXTERN_PROTO */"					>> zypp/poky-arch.h
	echo ""									>> zypp/poky-arch.h
	echo "#ifdef POKY_PROTO"						>> zypp/poky-arch.h
	echo "/* Specify prototypes */"						>> zypp/poky-arch.h
	for each_arch in ${PACKAGE_ARCHS} ; do
		case "$each_arch" in
			all | any | noarch)
				continue;;
		esac
		if [ "${AVOID_CONSTRUCTOR}" != "true" ]; then
		  echo "  const Arch Arch_${each_arch} (_${each_arch});"		>> zypp/poky-arch.h
		else
		  echo "  const Arch Arch_${each_arch} ( IdString ( \"${each_arch}\" ) );"		>> zypp/poky-arch.h
		fi
	done
	echo "#endif /* POKY_PROTO */"						>> zypp/poky-arch.h
	echo ""									>> zypp/poky-arch.h
	echo "#ifdef POKY_DEF_COMPAT"						>> zypp/poky-arch.h
	echo "/* Specify compatibility information */"				>> zypp/poky-arch.h
	INSTALL_PLATFORM_ARCHS=""
	for each_arch in ${PACKAGE_ARCHS} ; do
		INSTALL_PLATFORM_ARCHS="$each_arch $INSTALL_PLATFORM_ARCHS"
	done

	COMPAT_WITH=""
	set -- ${INSTALL_PLATFORM_ARCHS}
	while [ $# -gt 0 ]; do
		case "$1" in
			all | any | noarch)
				shift ; continue;;
		esac
		if [ "${AVOID_CONSTRUCTOR}" != "true" ]; then
		  ARCH="_$1"
		else
		  ARCH="IdString(\"$1\")"
		fi
		shift
		COMPAT=""
		for each_arch in "$@"; do
			if [ -z "${AVOID_CONSTRUCTOR}" ]; then
			  arch_val="_${each_arch}"
			else
			  arch_val="IdString(\"${each_arch}\")"
			fi
			if [ -z "$COMPAT" ]; then
				COMPAT=${arch_val}
			else
				COMPAT="${arch_val},$COMPAT"
			fi
		done
		COMPAT_WITH="${ARCH},${COMPAT} $COMPAT_WITH"
	done
	for each_compat in ${COMPAT_WITH} ; do
		echo "        defCompatibleWith( ${each_compat} );"		>> zypp/poky-arch.h
	done
	echo "#endif /* DEF_COMPAT */"						>> zypp/poky-arch.h
	echo ""									>> zypp/poky-arch.h
}

addtask archgen before do_configure after do_patch
