cd nuttx-apps
ln -s ../modules external
cd ..
cmake nuttx -B build -DBOARD_CONFIG=../board/configs/iamwebmorda -GNinja
rm nuttx-apps/external

