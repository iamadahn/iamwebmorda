cd nuttx-apps
ln -s ../modules modules
cd ../nuttx
make -j
cd ../nuttx-apps
rm -rf modules
