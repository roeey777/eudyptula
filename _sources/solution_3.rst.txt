Solution to Challenge #3 - patching the kernel code
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this challenge, I was asked to write a small patch to the kernel ``Makefile`` and modify the ``EXTRAVERSION`` field.
After the modification "-eudyptula" should be added to the version string.
The patch can be found at ``solutions/patches/linux/0001-Solution-to-challenge-3-Changed-EXTRAVERSION-variable-in-the-main-Makefile.patch``
In order for ``buildroot`` to apply this patch one must tell ``buildroot`` where to look for patches and this is done in the ``defconfig`` like this:

.. code-block::

   BR2_GLOBAL_PATCH_DIR="$(BR2_EXTERNAL_EUDYPTULA_PATH)/patches"

After rebuilding the kernel (so the source-code could be patched...) one can test the patch by executing:

.. code-block:: bash

   cat /proc/version

And there he expects to see the "-eudyptula" suffix.

