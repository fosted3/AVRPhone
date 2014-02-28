#!/bin/bash
# Yes, this is a Badly Written Script - it isn't supposed to be fancy

TOOLURL="http://www.atmel.com/System/GetBinary.ashx?target=tcm:26-51628&type=soft&actualTarget=tcm:26-51631"

mkdir "$HOME"/toolchains

wget "$TOOLURL" -O /tmp/avr8chain.tar.gz

tar xf /tmp/avr8chain.tar.gz -C "$HOME"/toolchains/

echo "If nothing blew up, the avr8 toolchain binaries should be installed to $HOME/toolchains/, and the project makefiles should find them."
