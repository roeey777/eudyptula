Generate The Documentation
--------------------------

This project uses ``sphinx`` in order to generate it's documentation & hosts them on `Github Pages <https://roeey777.github.io/eudyptula/>`_.
There are a few steps for generating & hosting documentation.

Automatic generation of documentation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


.. note::

   For a clean/fresh clone of this repo one should execute the following command only **ONCE**
   **before** to the rest of the steps. The command is:

   .. code-block:: bash

      # from the repo's top directory
      git worktree add docs/build/html -B gh-pages

   The rest of the automatic *publishing* of the documentation heavily relies on ``git worktree`` feature.
   We expect to have a ``git worktree`` in ``docs/build/html/`` checkout on branch ``gh-pages``.
   You can verify it by the following commands:

   .. code-block:: bash

      # you should see 2 worktrees, one of the repo's top directory on your branch, i.e. ``master``, ``dev``, etc.
      # and another in ``docs/build/html/`` on ``gh-pages`` branch.
      git worktree list

   Another way to verify it is:

   .. code-block:: bash

      # should tell you are checked-out to your branch.
      git branch

      cd docs/build/html/
      # should tell you are checked-out to gh-pages branch.
      git branch

You should execute the following commands:

.. code-block:: bash

   # from docs/
   make clean
   
   # move to the repo top directory
   cd ..
   sphinx-build docs/source/ docs/build/html

And now your documentation is built!
You can inspect it as follows:

.. code-block:: bash

   firefox docs/build/html/index.html

Publishing the Documentation to Github Pages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Now since you've used the ``make clean`` command, the directory ``docs/build/html`` was automatically added
to git worktree for the branch ``gh-pages`` which is the default branch `Github <github.com>` uses for the pages feature.
All that is left to do is as follows:

.. code-block:: bash

   cd docs/build/html

Now you need to verify that your working on ``gh-pages`` branch, this can be validated as follows:

.. code-block:: bash

   # from docs/build/html
   git branch

After this verification we can add all the new documentation.

.. code-block:: bash

   # from docs/build/html
   git add -A .
   git commit -sm "update documentation"
   git push origin gh-pages

And Your'e Done!


Highly Autonomous Documentation Generation & Publication
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There is also another way which automates this procedure even further.
All one has to do is simply execute the following (from the top directory of the repository)

.. code-block:: bash

   make docs


This command will generate the documentation using ``sphinx``.
The following command will generate the documentation and publish them onto `Github Pages <https://roeey777.github.io/eudyptula/>`_.

.. code-block:: bash

   make publish-docs


