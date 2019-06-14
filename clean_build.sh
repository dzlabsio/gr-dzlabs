sudo rm -r build
mkdir build
cd build
cmake ..
make -j8
sudo make install
sudo ldconfig
cd ..

