# DataStructure_C [![Build Status](https://travis-ci.org/iamsubhranil/DataStructure_C.svg?branch=libify)](https://travis-ci.org/iamsubhranil/DataStructure_C)
### Implementation of specific data structures in C
The folders in this project acts as following :
##### `app`
Implementation of the libraries using a frontend application
##### `configs`
Configuration of apps and libraries (if the app or library supports) in a `PROPERTY=y`/`PROPERTY=n` manner, which later gets converted to `#define`s, much inspired by the linux kernel
##### `desc`
A collection of `PROPERTY` descriptors, to let the user select a `PROPERTY` in a user-friendly way, again inspired by the linux kernel
##### `include`
Custom headers for the libraries and apps, which later gets included as a default `include` location by `-I` switch
##### `lib`
The folder for backend libraries
##### `scripts`
Various scripts needed by the framework
##### `Makefile`
The deafult `make` targets
