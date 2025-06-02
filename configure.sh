cd nuttx-apps
ln -s ../app heartbeat_daemon
cd ../nuttx
make distclean
./tools/configure.sh -l ../board/configs/iamwebmorda
cd ../nuttx-apps
rm -rf heartbeat_daemon

