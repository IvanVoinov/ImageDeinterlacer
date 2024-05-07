Simple console application to deintrlace image.
It is using C++14 and std library + and latest version of libjpeg library(downloading during cmake build).

Usage:
1. Open terminal inside project and run next commands:
  1.1.cmake -S. -B build
  1.2. cd build && make
2. Library will be donwloaded and compilation done.
3. Run application: cd ../ && ./build/picture_deinterlacer -i resource/interlaced.jpg -o ./

Application tested on Unix-based system(PopOs). Windows not probably supported yet.

Approximate application execution time is 35ms for image from the project(/resource/interlaced.jpg).

TODOs:
1.Ability to process several files per one cycle;
2. Add thread pool to parallelize image processing.
