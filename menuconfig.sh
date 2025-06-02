cd nuttx-apps
ln -s ../app heartbeat_daemon
cd ../nuttx
make menuconfig
cd ../nuttx-apps
rm -rf heartbeat_daemon
