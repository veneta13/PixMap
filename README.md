# FinalProject

### Final Project for OOP course @FMI.

###### Run command:
```shell

g++ main.cpp src/binaryHandler.cpp src/command.cpp src/commandReader.cpp src/dithering.cpp src/ditheringGrayscale.cpp src/ditheringRGB.cpp src/executor.cpp src/fileManager.cpp src/handler.cpp src/image.cpp src/netpbm.cpp src/pbm.cpp src/pgm.cpp src/ppm.cpp src/textHandler.cpp src/validator.cpp src/baseHandler.cpp
```

## Supported file formats:

 - PBM (ASCII, binary - with ASCII header)
 - PGM (ASCII, binary - with ASCII header)
 - PPM (ASCII, binary - with ASCII header)

[**Results**](https://github.com/veneta13/PixMap/tree/main/images/ready)

## Supported commands: 
### exit
exits the program
 ```c++
  exit
 ```
 
 ### save 
 saves in current location
 ```c++
  save
 ```
 
  ### saveas
  saves in a different location
 ```c++
  saveas "C:\Temp\another file.xml"
 ```
 
  ### open 
  loads a new file
 ```c++
  open "C:\Temp\another file.xml"
 ```
 
  ### close 
  closes current file 
 ```c++
  close
 ```
 
  ### new
  creates a new file with a single color background
 ```c++
  new 1000 1000 #ffffff
 ```
 
  ### resize
  resizes an image to a percentage of its current size or to exact parameters
 ```c++
  resize 50
  resize 100 100
 ```
 
  ### crop 
  crops the image by upper left and lower right corner coordinates  
 ```c++
  crop 1 1 100 100
 ```
 
  ### dither
  dithers the image
 ```c++
  dither
 ```
 
 #### Supported dithering algorithms:
 - Floyd-Steinberg
 - False Floyd-Steinberg
 - Jarvis, Judice, and Ninke
 - Stucki
 - Atkinson
 - Burkes
 - Sierra
 - Two-Row Sierra
 - Sierra Lite
 - 4x4 Bayer matrix
 - 8x8 Bayer matrix 
