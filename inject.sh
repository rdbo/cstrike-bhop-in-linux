#/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo "[!] Run as root"
    exit 0
fi

if [ ! command -v gdb &> /dev/null ]; then
    echo "[!] Unable to find GDB, make sure you have it installed"
    exit 0
fi

proc_name="hl_linux"
proc_id=""
libpath="$(pwd)/build/libcshack.so"

if ! proc_id=$(pgrep $proc_name) > /dev/null 2>&1; then
    echo "[!] The target process is not running"
    exit 0
fi

if [ ! -f $libpath ]; then
    echo "[!] Invalid shared library file"
fi

gdb -n -q -batch \
  -ex "attach $proc_id" \
  -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
  -ex "call \$dlopen(\"$libpath\", 1)" \
  -ex "detach" \
  -ex "quit" > /dev/null 2>&1

echo "[*] done"

exit 1