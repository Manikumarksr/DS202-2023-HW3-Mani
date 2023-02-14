Run the following commands 

git clone https://github.com/cjain7/libdivsufsort.git
cd libdivsufsort
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX=$PWD ..
make
```

You should get `ds202_sample1` and `ds202_sample2` executables in `build/examples` folder.

