wget http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/3.1.0/opencv-3.1.0.zip/download -O opencv-3.1.0.zip
unzip opencv-3.1.0.zip
cd opencv-3.1.0
mkdir release
cd release
cmake ../
ccmake ../
make -j4
sudo make install