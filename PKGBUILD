# Maintainer : librewish <librewish@garudalinux.org>
# Maintainer : dr460nf1r3 <dr460nf1r3 at garudalinux dot org>
# Contributor : Ramon Buldo <ramon@manjaro.org>

pkgbase=garuda-settings-manager
pkgname=('garuda-settings-manager' 'garuda-settings-manager-kcm'
         'garuda-settings-manager-notifier' 'garuda-settings-manager-knotifier')
pkgver=1.0.0
pkgrel=1
pkgdesc="Garuda Linux system settings (Manjaro settings manager ported to work with Arch standards and limited to only DKMS drivers)"
arch=('i686' 'x86_64')
url="https://gitlab.com/garuda-linux/applications/$pkgbase"
license=("GPL")
depends=('icu' 'qt5-base>=5.12.3' 'hwinfo' 'kitemmodels' 'kauth'
         'kcoreaddons' 'ckbcomp' 'xdg-utils' 'mhwd-garuda-git')
optdepends=('garuda-settings-manager-notifier-git: qt-based'
            'garuda-settings-manager-knotifier-git: knotifications-based')
makedepends=('git' 'extra-cmake-modules' 'kdoctools' 'qt5-tools' 'knotifications'
             'kconfigwidgets' 'kcmutils')
conflicts=('kcm-msm')
source=("https://gitlab.com/garuda-linux/applications/$pkgbase/-/archive/$pkgver/garuda-settings-manager-$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
  cd "$srcdir/$pkgbase-$pkgver"
  mkdir -p build
  cd build
  cmake ../ \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DLIB_INSTALL_DIR=lib \
    -DKDE_INSTALL_USE_QT_SYS_PATHS=ON \
    -DSYSCONF_INSTALL_DIR=/etc
  CXXFLAGS+="-std=gnu++98" make
}

package_garuda-settings-manager() {
  provides=($pkgbase)
  conflicts=($pkgbase)
  cd "$srcdir/$pkgbase-$pkgver/build"
  make DESTDIR=${pkgdir} install 
  rm -rf $pkgdir/usr/bin/msm_notifier
  rm -rf $pkgdir/usr/bin/msm_kde_notifier
  rm -rf $pkgdir/usr/lib/qt
  rm -rf $pkgdir/usr/share/kservices5
  rm -rf $pkgdir/usr/share/applications/msm_notifier_settings.desktop
  rm -rf $pkgdir/usr/share/applications/msm_kde_notifier_settings.desktop
  rm -rf $pkgdir/etc/xdg
}

package_garuda-settings-manager-kcm() {
  pkgdesc="Garuda Linux system settings - KCM for Plasma 5"
  depends=('garuda-settings-manager' 'kcmutils' 'kconfigwidgets')
  replaces=('kcm-msm')
  cd "$srcdir/$pkgbase-$pkgver/build"
  make DESTDIR=${pkgdir} install
  rm -rf $pkgdir/etc  
  rm -rf $pkgdir/usr/bin
  rm -rf $pkgdir/usr/lib/kauth
  rm -rf $pkgdir/usr/share/{applications,dbus-1,icons,polkit-1}
}

package_garuda-settings-manager-notifier() {
  pkgdesc="Garuda Linux system settings - notifier"
  depends=('garuda-settings-manager')
  provides=('garuda-settings-manager-kde-notifier')
  conflicts=('garuda-settings-manager-kde-notifier')
  cd "$srcdir/$pkgbase-$pkgver/build"
  make DESTDIR=${pkgdir} install
  rm -rf $pkgdir/etc/dbus-1
  rm -rf $pkgdir/etc/xdg/autostart/msm_kde_notifier.desktop
  rm -rf $pkgdir/usr/lib/
  rm -rf $pkgdir/usr/share/{kservices5,dbus-1,icons,polkit-1}
  rm -rf $pkgdir/usr/share/applications/garuda*
  rm -rf $pkgdir/usr/share/applications/msm_kde_notifier_settings.desktop
  rm -rf $pkgdir/usr/bin/garuda*
  rm -rf $pkgdir/usr/bin/msm_kde_notifier
}

package_garuda-settings-manager-knotifier() {
  pkgdesc="Garuda Linux system settings - knotifier"
  depends=('garuda-settings-manager' 'knotifications')
  conflicts=('garuda-settings-manager-notifier')
  replaces=('garuda-settings-manager-kde-notifier')
  cd "$srcdir/$pkgbase-$pkgver/build"
  make DESTDIR=${pkgdir} install
  rm -rf $pkgdir/etc/dbus-1
  rm -rf $pkgdir/etc/xdg/autostart/msm_notifier.desktop
  rm -rf $pkgdir/usr/lib/
  rm -rf $pkgdir/usr/share/{kservices5,dbus-1,icons,polkit-1}
  rm -rf $pkgdir/usr/share/applications/garuda*
  rm -rf $pkgdir/usr/share/applications/msm_notifier_settings.desktop
  rm -rf $pkgdir/usr/bin/garuda*
  rm -rf $pkgdir/usr/bin/msm_notifier
} 
