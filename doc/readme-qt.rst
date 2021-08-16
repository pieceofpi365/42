42-qt: Qt4 GUI for 42
===============================

Build instructions
===================

Debian
-------

First, make sure that the required packages for Qt5 development of your
distribution are installed, for Debian and Ubuntu these are:

::

    apt-get install qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools \
        build-essential libboost-dev libboost-system-dev \
        libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev \
        libssl-dev libdb++-dev

Install Git:

::

    sudo apt-get install git

clone the repository :

::

    git clone https://github.com/42-coin/42
   

delete ifaddrs.h and ifaddrs.c files in 42/src folder, then execute the following:

::

    cd 42
    qmake USE_O3=1 USE_ASM=1 RELEASE=1
    make

Alternatively, install Qt Creator and open the `42-qt.pro` file.

An executable named `42-qt` will be built.

To build 42d execute the following:

::

    cd src
    make -f makefile.unix USE_O3=1 USE_ASM=1 STATIC=1
    strip 42d


Windows
--------

Windows build instructions:

- Download the `QT Windows SDK`_ and install it. You don't need the Symbian stuff, just the desktop Qt.

- Download and extract the `dependencies archive`_  [#]_, or compile openssl, boost and dbcxx yourself.

- Copy the contents of the folder "deps" to "X:\\QtSDK\\mingw", replace X:\\ with the location where you installed the Qt SDK. Make sure that the contents of "deps\\include" end up in the current "include" directory.

- Open the .pro file in Qt Creator and build as normal (ctrl-B)

.. _`QT Windows SDK`: http://qt.nokia.com/downloads/sdk-windows-cpp
.. _`dependencies archive`: https://download.visucore.com/bitcoin/qtgui_deps_1.zip
.. [#] PGP signature: https://download.visucore.com/bitcoin/qtgui_deps_1.zip.sig (signed with RSA key ID `610945D0`_)
.. _`610945D0`: http://pgp.mit.edu:11371/pks/lookup?op=get&search=0x610945D0


macOS
-----

- Download and install the `Qt macOS SDK`_. It is recommended to also install Apple's Xcode with UNIX tools.

- Download and install `MacPorts`_.

- Execute the following commands in a terminal to get the dependencies:

::

	sudo port selfupdate
	sudo port install boost db48

- Open the .pro file in Qt Creator and build as normal (cmd-B)

.. _`Qt macOS SDK`: http://qt.nokia.com/downloads/sdk-mac-os-cpp
.. _`MacPorts`: http://www.macports.org/install.php


Build configuration options
============================

LevelDB transaction index
--------------------------

To use LevelDB for transaction index, pass the following argument to qmake:

::

    qmake "USE_LEVELDB=1"

No additional external dependencies are required. If you're running this on your current sources tree then don't forget to run

::

    make distclean

prior to running qmake.

Assembler implementation of scrypt hashing
------------------------------------------

To use optimized scrypt implementation instead of generic scrypt module, pass the following argument to qmake:

::

    qmake "USE_ASM=1"


If you're using clang compiler then you need to unroll macroses before compiling. Following commands will do this for you:

::

    cd src/
    ../contrib/clang/nomacro.pl

No additional external dependencies required. Note that only x86, x86_64 and ARM processors are supported.

Notification support for recent (k)ubuntu versions
---------------------------------------------------

To see desktop notifications on (k)ubuntu versions starting from 10.04, enable usage of the
FreeDesktop notification interface through DBUS using the following qmake option:

::

    qmake "USE_DBUS=1"

Generation of QR codes
-----------------------

libqrencode is used to generate QRCode images for payment requests.
It can be downloaded from http://fukuchi.org/works/qrencode/index.html.en, or installed via your package manager.

Berkely DB version warning
==========================

A warning for people using the *static binary* version of 42 on a Linux/UNIX-ish system (tl;dr: **Berkely DB databases are not forward compatible**).

The static binary version of 42 is linked against libdb5.3.

If the globally installed development package of Berkely DB installed on your system is 5.X, for example, any source you
build yourself will be linked against that. The first time you run with a 5.X version the database will be upgraded,
and 4.X cannot open the new format. This means that you cannot go back to the old statically linked version without
significant hassle!