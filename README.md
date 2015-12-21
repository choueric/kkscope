#husky#

A porting of kscope 1.6.2 using Qt4 and KDE4.

#Build#

request:
- build-essential
- cmake
- kdelibs-dev
- bison, flex
- cscope
- ctags

1. make a build direcotry, such as "./build", and go into it.
    ```shell
    $ mkdir build
    $ cd ./build
    ```

2. use cmake to build project, and install to a temporary path (etc. `./install`). 
   `../husky/src`, for example, is the directory of CMakefile.
    ```shell
    $ cmake ../husky/src -DCMAKE_INSTALL_PREFIX=`pwd`/_install
    $ make
    $ make install
    ```
    
3. run the programe.
    ```shell
    $ ./husky
    ```

#Development#

- icons' names are almost from /usr/share/icons/kde/oxygen
- ui file's path are showed by "kde4-config --path data".
  In the pregress of development, this program will check whether its ui file is in these paths.
  Now, we use a temporary method to run programe without installing XMLGUI file into /usr/share now.
