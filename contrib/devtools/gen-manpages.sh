#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

MEOWCOIND=${MEOWCOIND:-$SRCDIR/pointsd}
MEOWCOINCLI=${MEOWCOINCLI:-$SRCDIR/points-cli}
MEOWCOINTX=${MEOWCOINTX:-$SRCDIR/points-tx}
MEOWCOINQT=${MEOWCOINQT:-$SRCDIR/qt/points-qt}

[ ! -x $MEOWCOIND ] && echo "$MEOWCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
PNTVER=($($MEOWCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for pointsd if --version-string is not set,
# but has different outcomes for points-qt and points-cli.
echo "[COPYRIGHT]" > footer.h2m
$MEOWCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $MEOWCOIND $MEOWCOINCLI $MEOWCOINTX $MEOWCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${PNTVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${PNTVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
