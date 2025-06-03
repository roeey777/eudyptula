Solution to Challenge #6
~~~~~~~~~~~~~~~~~~~~~~~~~

In this challenge, I was asked to implement a small misc char device which controls the
return code of the syscall ``write`` based on the given data from the user. If the given data
matches the secret then the return code should be valid, otherwise ``EINVAL`` should be returned,
The testing flow is as follows:

.. code-block:: bash

   dmesg -c > /dev/null                # clear the current kernel log.
   lsmod                               # see the module isn't loaded yet.
   ls /dev/eudyptula                   # verify there is no such device yet.

   modprobe solution_6                 # load the kernel module.
   dmesg -c                            # see the loading logs of the module.
   lsmod                               # see that the module is currently loaded.
   ls /dev/eudyptula                   # verify that there is char device.
   echo -n eudyptula > /dev/eudyptula  # write the "secret" into the device.
   echo $?                             # expect to see 0, indicating success.
   dmesg -c                            # verify there is no error logs.

   echo -n nonsense > /dev/eudyptula   # write something else than the "secret" into the device.
   echo $?                             # expect to see 1, indicating failure.
   dmesg -c                            # verify there is an error log indicating that nonsense isn't the "secret".

   modprobe -r solution_6              # unload the kernel module.
   dmesg -c                            # see the unloading logs of the module.
   lsmod                               # see that the module isn't loaded.
   ls /dev/eudyptula                   # verify that there is no such char device.

