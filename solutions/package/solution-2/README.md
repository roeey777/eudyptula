The solution to this challenge is by suppling a custom kernel defconfig, using buildroot.

The CONFIG_LOCALVERSION_AUTO is already enabled by the base kernel config from buildroot itself.
Instead of enabling the already enabled configuration I've configured a different value:
CONFIG_LOCALVERSION="-eudyptula"

I've used ``buildroot`` config fragments mechanism to "overlay" a base defconfig from ``buildroot``.
Using config fragments will be easier for managing & keeping track of configuration changes over time.

The effect of this change can be seen while printing ``/proc/version`` or by executing ``uname -a``
