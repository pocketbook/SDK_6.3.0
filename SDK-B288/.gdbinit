set detach-on-fork on
set auto-load python-scripts off
#target remote 192.168.205.1:3333
set sysroot /tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot
add-auto-load-safe-path /tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/
set solib-search-path /tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/local/lib:/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/lib

