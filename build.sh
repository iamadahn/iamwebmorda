cd nuttx-apps
ln -s ../app heartbeat_daemon
cd ../nuttx
make -j
cd ../nuttx-apps
rm -rf heartbeat_daemon
