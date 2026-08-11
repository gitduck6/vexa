#!/usr/bin/env bash

PROJ="game"
debug_bin="./build/linux/x86_64/debug/${PROJ}"
release_bin="./build/linux/x86_64/release/${PROJ}"

if [[ "$1" == "dev" ]]; then
    xmake config --mode=debug
    copy_bin="$debug_bin"
    shift
else
    xmake config --mode=release
    copy_bin="$release_bin"
fi

xmake build -j$(nproc) -v "${PROJ}" || exit $?
command cp "$copy_bin" ./"${PROJ}"
./"${PROJ}" "$@"
