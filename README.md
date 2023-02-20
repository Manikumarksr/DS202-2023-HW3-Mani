Run the following commands 
```
git clone https://github.com/Manikumarksr/DS202-2023-HW3-Mani.git
cd DS202-2023-HW3-Mani.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX=$PWD ..
cd ../examples
wget https://s3-us-west-2.amazonaws.com/human-pangenomics/T2T/CHM13/assemblies/chm13.chrX_v0.7.fasta.gz
gzip -d chm13.chrX_v0.7.fasta.gz
make
```

You should get `suffix_lcp` executable in `examples` folder.

