Running in QEMU
~~~~~~~~~~~~~~~

.. note::

        This was inspired by buildroot's ```board/qemu/x86_64/readme.txt```


Run the emulation with:

.. code-block:: bash

        qemu-system-x86_64 -M pc -kernel buildroot/output/images/bzImage -drive file=buildroot/output/images/rootfs.ext2,if=virtio,format=raw -append "rootwait root=/dev/vda console=tty1 console=ttyS0" -serial stdio -net nic,model=virtio -net user


Optionally add -smp N to emulate a SMP system with N CPUs.

The login prompt will appear in the graphical window.


Challenge #5:
~~~~~~~~~~~~~

In this challenge I'm asked to load my dummy kernel module whenever a USB keyboard is attached to the system.
Since I'm using ```QEMU``` this requires adding a new flag (```-usb```) to the invokation of ```qemu``` like this:

.. code-block:: bash

        qemu-system-x86_64 -M pc -kernel buildroot/output/images/bzImage -drive file=buildroot/output/images/rootfs.ext2,if=virtio,format=raw -append "rootwait root=/dev/vda console=tty1 console=ttyS0" -usb -serial stdio -net nic,model=virtio -net user


Now we can tell ```qemu``` when to add the USB keyboard from it's monitoring interface.
On the newly openned window press Cntl-Alt-2 which will switch that window into the management interface of ```qemu```.
From within this interface type ```device_add usb-kbd```

