#
# This file is the qtapplication recipe.
#

SUMMARY = "mixfit qt application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://SpiTest.pro \
           file://main.cpp \
	   file://mainwindow.cpp \
	   file://spirpi.cpp \
	   file://bytedatarappresentation.cpp \
	   file://targetUiElement.cpp \
	   file://intelhex.cpp \
	   file://server.cpp \
	   file://mainwindow.h \
	   file://spirpi.h \
	   file://bytedatarappresentation.h \
	   file://targetUiElement.h \
	   file://intelhex.h \
	   file://server.h \
	   file://mainwindow.ui \
	   file://bytedatarappresentation.ui \
	   file://targetUiElement.ui \
           file://pixel_green.png \
           file://pixel_red.png \
           file://pixel_yellow.png \
           file://resources.qrc \
           file://makedrink.png \
           file://profileselection.png \
"


DEPENDS = "qtbase"
RDEPENDS_${PN} = "qtbase"

S = "${WORKDIR}"

#do_compile() {
#	     oe_runmake
#}


do_install() {
	     install -d ${D}${bindir}
             install -m 0755 qtapp ${D}${bindir}	     
}


inherit qmake5
