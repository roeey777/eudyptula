.. _qemu:

Running in QEMU
~~~~~~~~~~~~~~~

.. note::

        This was inspired by buildroot's ```board/qemu/x86_64/readme.txt```


Run the emulation with:

.. code-block:: bash

        qemu-system-x86_64 -M pc -kernel buildroot/output/images/bzImage -drive file=buildroot/output/images/rootfs.ext2,if=virtio,format=raw -append "rootwait root=/dev/vda console=tty1 console=ttyS0" -serial stdio -net nic,model=virtio -net user


Optionally add -smp N to emulate a SMP system with N CPUs.

The login prompt will appear in the graphical window.

