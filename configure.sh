cd nuttx-apps
ln -s ../modules modules
cd ../nuttx
make distclean
./tools/configure.sh -l ../board/configs/iamwebmorda
cd ../nuttx-apps
rm -rf modules

