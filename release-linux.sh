VERSION=1.0.2.0
rm -rf ./release-linux
mkdir release-linux

cp ./src/pointsd ./release-linux/
cp ./src/points-cli ./release-linux/
cp ./src/qt/points-qt ./release-linux/
cp ./POINTSCOIN_small.png ./release-linux/

cd ./release-linux/
strip pointsd
strip points-cli
strip points-qt

#==========================================================
# prepare for packaging deb file.

mkdir pointscoin-$VERSION
cd pointscoin-$VERSION
mkdir -p DEBIAN
echo 'Package: pointscoin
Version: '$VERSION'
Section: base 
Priority: optional 
Architecture: all 
Depends:
Maintainer: Points
Description: Points coin wallet and service.
' > ./DEBIAN/control
mkdir -p ./usr/local/bin/
cp ../pointsd ./usr/local/bin/
cp ../points-cli ./usr/local/bin/
cp ../points-qt ./usr/local/bin/

# prepare for desktop shortcut
mkdir -p ./usr/share/icons/
cp ../POINTSCOIN_small.png ./usr/share/icons/
mkdir -p ./usr/share/applications/
echo '
#!/usr/bin/env xdg-open

[Desktop Entry]
Version=1.0
Type=Application
Terminal=false
Exec=/usr/local/bin/points-qt
Name=pointscoin
Comment= points coin wallet
Icon=/usr/share/icons/POINTSCOIN_small.png
' > ./usr/share/applications/pointscoin.desktop

cd ../
# build deb file.
dpkg-deb --build pointscoin-$VERSION

#==========================================================
# build rpm package
rm -rf ~/rpmbuild/
mkdir -p ~/rpmbuild/{RPMS,SRPMS,BUILD,SOURCES,SPECS,tmp}

cat <<EOF >~/.rpmmacros
%_topdir   %(echo $HOME)/rpmbuild
%_tmppath  %{_topdir}/tmp
EOF

#prepare for build rpm package.
rm -rf pointscoin-$VERSION
mkdir pointscoin-$VERSION
cd pointscoin-$VERSION

mkdir -p ./usr/bin/
cp ../pointsd ./usr/bin/
cp ../points-cli ./usr/bin/
cp ../points-qt ./usr/bin/

# prepare for desktop shortcut
mkdir -p ./usr/share/icons/
cp ../POINTSCOIN_small.png ./usr/share/icons/
mkdir -p ./usr/share/applications/
echo '
[Desktop Entry]
Version=1.0
Type=Application
Terminal=false
Exec=/usr/bin/points-qt
Name=pointscoin
Comment= points coin wallet
Icon=/usr/share/icons/POINTSCOIN_small.png
' > ./usr/share/applications/pointscoin.desktop
cd ../

# make tar ball to source folder.
tar -zcvf pointscoin-$VERSION.tar.gz ./pointscoin-$VERSION
cp pointscoin-$VERSION.tar.gz ~/rpmbuild/SOURCES/

# build rpm package.
cd ~/rpmbuild

cat <<EOF > SPECS/pointscoin.spec
# Don't try fancy stuff like debuginfo, which is useless on binary-only
# packages. Don't strip binary too
# Be sure buildpolicy set to do nothing

Summary: Points wallet rpm package
Name: pointscoin
Version: $VERSION
Release: 1
License: MIT
SOURCE0 : %{name}-%{version}.tar.gz
URL: https://www.pointscoin.net/

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root

%description
%{summary}

%prep
%setup -q

%build
# Empty section.

%install
rm -rf %{buildroot}
mkdir -p  %{buildroot}

# in builddir
cp -a * %{buildroot}


%clean
rm -rf %{buildroot}


%files
/usr/share/applications/pointscoin.desktop
/usr/share/icons/POINTSCOIN_small.png
%defattr(-,root,root,-)
%{_bindir}/*

%changelog
* Tue Aug 24 2021  Points Project Team.
- First Build

EOF

rpmbuild -ba SPECS/pointscoin.spec



