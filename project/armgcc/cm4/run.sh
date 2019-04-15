#!/bin/sh

DEBUG=debug
RELEASE=release
GDB=/opt/arm-none-eabi-insight/bin/arm-none-eabi-insight

if [ "$2" = "--whit_no_gui" ]; then
GDB=arm-none-eabi-gdb
fi

if [ "$1" = "$DEBUG" ]; then
$GDB -x ./gdb.script ./debug/core0.elf
elif [ "$1" = "$RELEASE" ]; then
arm-none-eabi-gdb -x ./gdb.script ./release/core0.elf
else
echo "err!"
fi
