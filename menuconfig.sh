cd nuttx-apps
ln -s ../modules modules
cd ../nuttx
make menuconfig
cd ../nuttx-apps
rm -rf modules
