#!/bin/sh

DEBUG=debug
RELEASE=release
GDB=/opt/arm-none-eabi-insight/bin/arm-none-eabi-insight

if [ "$2" = "--whit_no_gui" ]; then
GDB=arm-none-eabi-gdb
fi

if [ "$1" = "$DEBUG" ]; then
$GDB -x ./gdb_core1.script ./debug/core1.elf
elif [ "$1" = "$RELEASE" ]; then
arm-none-eabi-gdb -x ./gdb_core1.script ./release/core1.elf
else
echo "err!"
fi
