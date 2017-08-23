# kscope-4

A simple port of [kscope 1.6.2][1] onto QT4 and KDE4.

# Build

## Prepare

Requirment packages:

- build-essential
- cmake
- kdelibs-dev
- ctags
- cscope

In Ubuntu 14.04, do:

```sh
sudo apt install build-essential cmake kde-developer-sdk exuberant-ctags cscope
```

## Configurate

First run

```sh
$ make config
```
This will create a `_build` directory as the output dircetory of CMake, where 
contains the compile-generated files and the final executable file.

Right now, it just uses Qt4 by setting `QT_SELECT=4`. So if there is only Qt5,
you should install Qt4 tools.

## Build

```sh
$ make build
```

## Install

```sh
$ make install
```

The destination directory is `/usr/local/bin`.

# Development

- This project is also easy been imported and developped by QT Creator.
- icons' names are almost from /usr/share/icons/kde/oxygen
- ui file's path are showed by "kde4-config --path data".
  In the pregress of development, this program will check whether its ui file
  is in these paths.
  Now, we use a temporary method to run programe without installing XMLGUI file
  into /usr/share now.
  
[1]: https://sourceforge.net/projects/kscope/
