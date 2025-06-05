.. _challenge_9:

Solution to Challenge #9 - sysfs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

   In the implementation of this module `Greg Kroah-Hartman's blog <http://kroah.com/log/blog/2013/06/26/how-to-create-a-sysfs-file-correctly/>`_
   was taken into considitation when it came to the race-condition between the publication of ``UEVENT_ADD`` of the ``struct kobject`` and
   the actual addition of files to ``sysfs``.

   This is the reason for creating the attributes groups and a custom ``struct ktype`` which uses them instead of simply using ``sysfs_create_group`` which is far easier to use.

In this challenge, I was asked to implement a small module which exposes various fields to user-space
via ``sysfs`` in a dedicated directory called ``/sys/kernel/eudyptula/``. In this directory would be 3 files:

#. ``id`` - behaves the same as misc char device from :ref:`challenge 6 <challenge_6>` (and the ``id`` file from :ref:`challenge 8 <challenge_8>`).
#. ``jiffies`` - exposes the internal jiffies counter (read-only).
#. ``foo`` - a special buffer which can be written into only by root and be read by all.

Basically it's the same challenge as :ref:`challenge 8 <challenge_8>` but with ``sysfs`` instead of ``debugfs``.

The testing flow is as follows:

#. Test the Initialization of the Module:

   .. code-block:: bash

      dmesg -c > /dev/null                           # clear the current kernel log.
      lsmod                                          # see the module isn't loaded yet.
      ls -la /sys/kernel/eudyptula                   # verify there is no such device yet.

#. Test the ``id`` file:

   .. code-block:: bash

      modprobe solution_9                            # load the kernel module.
      dmesg -c                                       # see the loading logs of the module.
      lsmod                                          # see that the module is currently loaded.
      ls -la /sys/kernel/eudyptula/id                # verify that there is a id file under eudyptula.
      cat /sys/kernel/eudyptula/id                   # see roeey777 (i.e. the id) printed out.
      echo -n eudyptula > /sys/kernel/eudyptula/id   # write the "secret" into the device.
      echo $?                                        # expect to see 0, indicating success.
      dmesg -c                                       # verify there is no error logs.

      echo -n nonsense > /sys/kernel/eudyptula/id    # write something else than the "secret" into the device.
      echo $?                                        # expect to see 1, indicating failure.
      dmesg -c                                       # verify there is an error log indicating that nonsense isn't the "secret".

#. Test the ``jiffies`` file:

   .. code-block:: bash

      ls -la /sys/kernel/eudyptula/jiffies           # verify that there is a jiffies file under eudyptula.
      cat /sys/kernel/eudyptula/jiffies              # see the number of passed jiffies.

#. Test the ``foo`` file:

   .. code-block:: bash

      ls -la /sys/kernel/eudyptula/foo               # verify that there is a foo file under eudyptula.
      echo test > /sys/kernel/eudyptula/foo          # write "test\n" into the exposed kernel buffer.
      cat /sys/kernel/eudyptula/foo                  # expect to see test printed out.

#. Test the Unloading of the Module:

   .. code-block:: bash

      modprobe -r solution_9                         # unload the kernel module.
      dmesg -c                                       # see the unloading logs of the module.
      lsmod                                          # see that the module isn't loaded.
      ls -la /sys/kernel/eudyptula                   # verify that there is no such char device.

