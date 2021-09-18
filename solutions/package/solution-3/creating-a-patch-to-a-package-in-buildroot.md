# Creating a Patch to a Package in Buildroot using ``Git``:

### First Step - getting a clone of the code.
There are 2 ways to do so:
- use ``buildroot`` to fetch the source code for us.
- fetch the source code manually.

#### Fetching Source Code Using ``Buildroot``:
```bash
	make <package-name>-source
```
OR
```bash
	make <package-name>-patch  # also apply all available patches from buildroot.
```

Let's assume that our package is called "linux" (in this challenge, challenge #3, it
actually is the name of our desired package for patching).
Then we should execute the following command:
```bash
	make linux-source
```
OR fetch the source code of linux manually:
```bash
	git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
```

In case we've used ``buildroot`` we should do the following step as well.
```bash
	cd </path/to/buildroot>/output/build/<package-name>
        git init
        git add .
        git commit -m "meaningless commit message"
```
In Linux case:
```bash
	cd </path/to/buildroot>/output/build/linux
        git init
        git add .
        git commit -m "meaningless commit message"
```


### Second Step - Modifying The Source Code:
In this stage we should modify source code as we like.
After all the modifications were saved a ``git`` commit should be created.
The commit message should be meaningless since it will be included in the patch file.
```bash
	git commit -s -m "some meaningless commit message"
```


### Third & Final Step - Creating The Patch File:
In order for us to create the patch file we will use ``git`` since ``git format-patch``
can create patch files which includes commit messages.
Creating patches is simple, it only requires executing the following command:
```bash
	git format-patch -M -N --signoff -1 HEAD -o <where to store the new pathc file>
```
