yum install cmake mesa-libGL-devel libXrandr-devel freetype-devel glew-devel libjpeg-devel openal-soft-devel libsndfile-devel fontconfig-devel
wget https://github.com/LaurentGomila/SFML/tarball/master -O sfml.tgz
tar -xvzf sfml.tgz
cd LaurentGomila-SFML-4fbefe7
cmake .
make install
