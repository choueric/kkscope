# kscope-4 #

A porting of kscope 1.6.2 based on Qt4 and KDE4.

The name of executable file is **husky**

# Build #

request:

- build-essential
- cmake
- kdelibs-dev
- bison
- flex
- ctags
- cscope

In Ubuntu 14.04, do:

```sh
sudo apt install build-essential cmake kde-developer-sdk bison flex \
  exuberant-ctags cscope
```

Below are instructions to build and use.

1. Make a build direcotry, such as "./build", and go into it.

    ```shell
    $ mkdir build
    $ cd ./build
    ```

2. Use cmake to build project. The default install path would be `/usr/local/bin`.

   `../src`, according to the build directory, for example, is the directory of
   CMakefile.

    ```shell
    $ cmake ../src
    $ make
    $ make install
    ```

   If you want to install *husky* to another path (etc. `./install`), specify
   the variable `CMAKE_INSTALL_PREFIX`:

	```shell
    $ cmake ../src -DCMAKE_INSTALL_PREFIX=`pwd`/_install
	```
3. run the programe.

    ```shell
    $ ./husky
    ```

# Development #

- icons' names are almost from /usr/share/icons/kde/oxygen
- ui file's path are showed by "kde4-config --path data".
  In the pregress of development, this program will check whether its ui file is in these paths.
  Now, we use a temporary method to run programe without installing XMLGUI file into /usr/share now.
