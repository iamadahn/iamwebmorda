cd nuttx-apps
ln -s ../modules external
cd ..
cmake --build build -t menuconfig
rm nuttx-apps/external
