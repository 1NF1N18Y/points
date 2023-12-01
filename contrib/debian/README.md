
Debian
====================
This directory contains files used to package pointsd/points-qt
for Debian-based Linux systems. If you compile pointsd/points-qt yourself, there are some useful files here.

## points: URI support ##


points-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install points-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your points-qt binary to `/usr/bin`
and the `../../share/pixmaps/points128.png` to `/usr/share/pixmaps`

points-qt.protocol (KDE)

