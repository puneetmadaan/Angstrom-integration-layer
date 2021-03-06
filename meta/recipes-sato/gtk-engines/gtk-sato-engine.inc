DESCRIPTION = "Sato theme engine for GTK"
HOMEPAGE = "http://www.o-hand.com"
BUGTRACKER = "http://bugzilla.openedhand.com/"

LICENSE = "LGPLv2.1 & LGPLv2+"

SECTION = "x11/base"
DEPENDS = "gtk+"
RDEPENDS_gtk-theme-sato = "gtk-sato-engine"

PACKAGES += "gtk-theme-sato"
FILES_${PN} = "${libdir}/gtk-2.0/*/engines/*.so "
FILES_${PN}-dev = "${libdir}/gtk-2.0/*/engines/*"
FILES_${PN}-dbg += " ${libdir}/gtk-2.0/*/engines/.debug"
FILES_gtk-theme-sato = "${datadir}/icons ${datadir}/themes"

inherit autotools  pkgconfig

do_configure_prepend() {
	for i in `ls gtk-common`; do
		ln -sf ../gtk-common/$i gtk2-engine/$i
	done
}
