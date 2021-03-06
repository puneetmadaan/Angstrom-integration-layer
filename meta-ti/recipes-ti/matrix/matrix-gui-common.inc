DESCRIPTION = "Common files for all versions of Matrix GUI"
HOMEPAGE = "https://gforge.ti.com/gf/project/matrix_gui/"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://main.cpp;beginline=1;endline=37;md5=a802a01a3a58f2ebb1e83c25f883f0c0"

SECTION = "multimedia"

INC_PR = "r10"

COMPATIBLE_MACHINE = "(dm365|omapl138|omap3|ti816x|ti814x)"

PLATFORM_dm365-evm = "dm365"
PLATFORM_dm368-evm = "dm368"
PLATFORM_omapl138 = "omapl138"
PLATFORM_omap3evm = "omap3530"
PLATFORM_dm37x-evm = "dm3730"
PLATFORM_am37x-evm = "am3715"
PLATFORM_beagleboard = "beagleboard"
PLATFORM_ti816x = "ti816x"
PLATFORM_ti814x = "ti814x"
PLATFORM_am180x-evm = "am180x"
PLATFORM_am181x-evm = "am181x"
PLATFORM_am3517-evm = "am3517"

#Checkout the project repository to get access to the scripts and data
#files.
SRC_URI = "svn://gforge.ti.com/svn/matrix_gui/;module=trunk;proto=https;user=anonymous;pswd='' "

S = "${WORKDIR}/trunk"

PACKAGE_ARCH = ${MACHINE_ARCH}

do_install() {
    install -d ${D}/${bindir}
    install -m 0755 ${S}/${PLATFORM}/bin/* ${D}/${bindir}/
    install -d ${D}/${datadir}/matrix/html
    install -m 0644 ${S}/${PLATFORM}/html/* ${D}/${datadir}/matrix/html
    install -d ${D}/${datadir}/matrix/images
    install -m 0644 ${S}/images/*.png ${D}/${datadir}/matrix/images/
    install -m 0644 ${S}/images/*.svg ${D}/${datadir}/matrix/images/

}

FILES_${PN} += "${datadir}/matrix/*"
