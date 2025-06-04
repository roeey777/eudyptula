Solution to Challenge #8 - debugsfs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this challenge, I was asked to implement a small module which exposes various fields to user-space
via ``debugfs`` in a dedicated directory called ``/sys/kernel/debug/eudyptula/``. In this directory would be 3 files:

#. ``id`` - behaves the same as misc char device from challenge #6 (read-write for all).
#. ``jiffies`` - exposes the internal jiffies counter (read-only).
#. ``foo`` - a special buffer which can be written into only by root and be read by all.

The testing flow is as follows:

#. Test the Initialization of the Module:

   .. code-block:: bash

      dmesg -c > /dev/null                                # clear the current kernel log.
      lsmod                                               # see the module isn't loaded yet.
      mount -t debugfs none /sys/kernel/debug             # mount debugfs
      ls -la /sys/kernl/debug/eudyptula                   # verify there is no such device yet.

#. Test the ``id`` file:

   .. code-block:: bash

      modprobe solution_8                                 # load the kernel module.
      dmesg -c                                            # see the loading logs of the module.
      lsmod                                               # see that the module is currently loaded.
      ls -la /sys/kernl/debug/eudyptula/id                # verify that there is a id file under eudyptula.
      cat /sys/kernl/debug/eudyptula/id                   # see roeey777 (i.e. the id) printed out.
      echo -n eudyptula > /sys/kernl/debug/eudyptula/id   # write the "secret" into the device.
      echo $?                                             # expect to see 0, indicating success.
      dmesg -c                                            # verify there is no error logs.

      echo -n nonsense > /sys/kernl/debug/eudyptula/id    # write something else than the "secret" into the device.
      echo $?                                             # expect to see 1, indicating failure.
      dmesg -c                                            # verify there is an error log indicating that nonsense isn't the "secret".

#. Test the ``jiffies`` file:

   .. code-block:: bash

      ls -la /sys/kernl/debug/eudyptula/jiffies           # verify that there is a jiffies file under eudyptula.
      cat /sys/kernl/debug/eudyptula/jiffies              # see the number of passed jiffies.

#. Test the ``foo`` file:

   .. code-block:: bash

      ls -la /sys/kernl/debug/eudyptula/foo               # verify that there is a foo file under eudyptula.
      echo test > /sys/kernl/debug/eudyptula/foo          # write "test\n" into the exposed kernel buffer.
      cat /sys/kernl/debug/eudyptula/foo                  # expect to see test printed out.

#. Test the Unloading of the Module:

   .. code-block:: bash

      modprobe -r solution_8                              # unload the kernel module.
      dmesg -c                                            # see the unloading logs of the module.
      lsmod                                               # see that the module isn't loaded.
      ls -la /sys/kernl/debug/eudyptula                   # verify that there is no such char device.

