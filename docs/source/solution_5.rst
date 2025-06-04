Solution to Challenge #5 - udev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this challenge I'm asked to load my dummy kernel module whenever a USB keyboard is attached to the system.
Since I'm using ```QEMU``` this requires adding a new flag (```-usb```) to the invokation of ```qemu``` like this:

.. code-block:: bash

        qemu-system-x86_64 -M pc -kernel buildroot/output/images/bzImage -drive file=buildroot/output/images/rootfs.ext2,if=virtio,format=raw -append "rootwait root=/dev/vda console=tty1 console=ttyS0" -usb -serial stdio -net nic,model=virtio -net user


Now we can tell ```qemu``` when to add the USB keyboard from it's monitoring interface.
On the newly openned window press Cntl-Alt-2 which will switch that window into the management interface of ```qemu```.
From within this interface type ```device_add usb-kbd```

This behavior was achieved by leveraging the functionality of ``eudev`` (which is ``udev`` extracted from ``systemd`` bloatware),
i.e. by adding a new ``udev`` rule for the USB keyboard supported by ``QEMU`` like this:

.. code-block::

   # contents of the file: /etc/udev/rules.d/99-qemu-usb-kbd.rules

   ACTION=="add", SUBSYSTEM=="usb", ATTR{idVendor}=="0627", ATTR{idProduct}=="0001", RUN+="/sbin/modprobe solution_1"

