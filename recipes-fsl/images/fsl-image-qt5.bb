DESCRIPTION = "Freescale Image - Adds Qt5"
LICENSE = "MIT"

require fsl-image-gui.bb

inherit distro_features_check populate_sdk_qt5

CONFLICT_DISTRO_FEATURES = "directfb"

# Install fonts
QT5_FONTS = " \
    ttf-dejavu-mathtexgyre \
    ttf-dejavu-sans \
    ttf-dejavu-sans-condensed \
    ttf-dejavu-sans-mono \
    ttf-dejavu-serif \
    ttf-dejavu-serif-condensed \
"

# Install QT5 demo applications
#    packagegroup-qt5-demos 
QT5_IMAGE_INSTALL = " \
    ${QT5_FONTS} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'libxkbcommon', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'qtwayland qtwayland-plugins', '', d)} \
"

#QT5_IMAGE_INSTALL_append_imxgpu3d = " \
#    packagegroup-qt5-3d \
#    packagegroup-qt5-webkit \
#"

# Most of QtWebEngine demo are currently broken.
# If you want to test them uncomment the following line
# QT5_IMAGE_INSTALL_append_imxgpu3d = " packagegroup-qt5-webengine"

IMAGE_INSTALL += " \
    ${QT5_IMAGE_INSTALL} \
"

# Due to the Qt samples the resulting image will not fit the default NAND size.
# Removing default ubi creation for this image
IMAGE_FSTYPES_remove = "multiubi"

#PACKAGE_EXCLUDE = " packagegroup-qt5-webkit qtwebkit qtwebkit-examples qtwebsockets qwt-qt5 qtpurchasing qtquick1 qtquickcontrols qtmultimedia qtquickcontrols2 qtserialbus qtsmarthome qtconnectivity qtwebview qtserialport qtremoteobjects-native qtremoteobjects qtnetworkauth qtlocation qtconnectivity qtdeclarative qtdeclarative-native qtcharts qtcanvas3d qtwebchannel qtsensors qtserialbus qtsystems "
#IMAGE_INSTALL_remove += " packagegroup-qt5-webkit qtwebkit qtwebkit-examples qtwebsockets qwt-qt5 qtpurchasing qtquick1 qtquickcontrols qtmultimedia qtquickcontrols2 qtserialbus qtsmarthome qtconnectivity qtwebview  qtserialport qtremoteobjects-native qtcharts qtremoteobjects qtnetworkauth qtlocation qtconnectivity qtdeclarative  qtdeclarative-native qtcharts qtcanvas3d qtwebchannel qtsensors qtserialbus qtsystems "
