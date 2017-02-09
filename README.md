Crimild Conversion Tool
=======================

Cloning
-------

 git clone <URL> --recursive

Requirements
------------

* CMake >= 3.1.0
* C++ build tools

Building
--------
 cmake .
 make clean all -j4

Usage
-----

 ./crimild-converter input=<INPUT_FILE> [output=<OUTPUT_FILE>]

* input: Path to input file (i.e. "modes/model.obj")
* ouput: (optional) Path to output file (default "scene.crimild")

Misc
-------------

* https://github.com/hhsaez/crimild/wiki/Export-FBX-models-from-Blender

* https://github.com/hhsaez/crimild/wiki/Export-OBJ-models-from-Blender

