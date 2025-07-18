cd nuttx-apps
ln -s ../modules external
cd ..
cmake --build output -t menuconfig
rm nuttx-apps/external
