cd build
cmake -T v141_xp ..
cmake --build . --target package --config release 
cd build
bash ./cloudsmith-upload.sh
