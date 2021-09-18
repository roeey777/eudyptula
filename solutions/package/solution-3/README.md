For this challenge a patch for the main Makefile of the kernel was required.
I've completed this challenge & the patch can be found
at ``solutions/patches/linux/0001-Solution-to-challenge-3-Changed-EXTRAVERSION-variable-in-the-main-Makefile.patch``
The effect of this patch can be seen by executing ``uname -a`` or by ``cat /proc/version`` & then you would see 
that "-eudyptula-challenge-solution-3" was added to the version name.
