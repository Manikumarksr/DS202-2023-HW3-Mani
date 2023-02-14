Run the following commands 
```
https://github.com/Manikumarksr/DS202-2023-HW3-Mani.git
cd DS202-2023-HW3-Mani.git
wget https://s3-us-west-2.amazonaws.com/human-pangenomics/T2T/CHM13/assemblies/chm13.chrX_v0.7.fasta.gz
gzip -d chm13.chrX_v0.7.fasta.gz
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX=$PWD ..
make
```

You should get `Suffix_a` executable in `build/examples` folder.

