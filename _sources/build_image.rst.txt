.. _build_image:

Building an Image
~~~~~~~~~~~~~~~~~

This project uses `Buildroot <https://gitlab.com/buildroot.org/buildroot>`_ in order to build all the solutions to the challenges.
Specifically the targeted platform is QEMU for x86 64-Bit architecture.

Build an image using Buildroot for emulation by QEMU is fairly simple, just follow these commands:

.. code-block:: bash

        # run from the repo top directory
        source activate.sh
	make -C buildroot/ eudyptula_qemu_x86_64_defconfig
	make -C buildroot all

