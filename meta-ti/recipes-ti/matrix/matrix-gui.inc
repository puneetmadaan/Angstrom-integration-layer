DESCRIPTION = "Matrix GUI for Qt X11"
HOMEPAGE = "https://gforge.ti.com/gf/project/matrix_gui/"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://main.cpp;beginline=1;endline=37;md5=a802a01a3a58f2ebb1e83c25f883f0c0"

SECTION = "multimedia"

INC_PR = "r22"

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

SRC_URI = "svn://gforge.ti.com/svn/matrix_gui/;module=trunk;proto=https;user=anonymous;pswd='' "

S = "${WORKDIR}/trunk"

CXXFLAGS_omapl138_append = " -DPlatform_omapl138 "
CXXFLAGS_dm365_append = " -DPlatform_dm365 "
PACKAGE_ARCH = ${MACHINE_ARCH}

inherit qt4x11

do_install() {
	install -d ${D}/${bindir}
	install -m 0755 ${S}/matrix_gui ${D}/${bindir}
	install -d ${D}${sysconfdir}/init.d/
	install -c -m 0755 ${S}/${PLATFORM}/etc/x11/init ${D}${sysconfdir}/init.d/matrix-gui
	install -d ${D}/${sysconfdir}/xdg/autostart
	install -m 0755 ${S}/${PLATFORM}/etc/x11/matrix-gui.desktop ${D}/${sysconfdir}/xdg/autostart
}

FILES_${PN}-autostart = "${sysconfdir}/xdg/autostart/matrix-gui.desktop"

#Make autostart package depend on matrix-gui package.  Doesn't make sense
#to install the autostart package without the underlying matrix-gui package.
RDEPENDS_${PN}-autostart += "${PN}"
PACKAGES =+ "${PN}-autostart"

RDEPENDS_${PN} += "matrix-gui-common"
