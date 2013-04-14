rm -rf LaurentGomila-SFML-*
yum install -y cmake mesa-libGL-devel libXrandr-devel freetype-devel glew-devel libjpeg-devel openal-soft-devel libsndfile-devel fontconfig-devel
wget https://github.com/LaurentGomila/SFML/tarball/master -O sfml.tgz
tar -xvzf sfml.tgz
cd LaurentGomila-SFML-*
cmake .
make install -j 4
