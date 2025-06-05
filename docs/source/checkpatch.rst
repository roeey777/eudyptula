.. _checkpatch:

Checkpatch
~~~~~~~~~~

Checkpatch is the code-linter used for enforcing the Linux kernel C-code conventions.
One can find more information about it in `here <https://docs.kernel.org/dev-tools/checkpatch.html>`_

.. code-block:: bash

	</path/to/>/checkpatch.pl --no-tree --file </path/to/examined/file.c>

If one shall desires to execute ``checkpatch`` on each & every ``.c`` file then he can use the following command:

.. code-block:: bash

        find . -type f | grep "\.c$" | xargs </path/to/>/checkpatch.pl --no-tree --file


In our case, ``checkpath`` has being copied into the repo so we can execute:

.. code-block:: bash

        find . -type f | grep "\.c$" | xargs ./scripts/checkpatch.pl --no-tree --file

