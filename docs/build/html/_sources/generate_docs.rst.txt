Generate The Documentation
--------------------------

This project uses ``sphinx`` in order to generate it's documentation & hosts them on `Github Pages <https://roeey777.github.io/eudyptula/>`_.
There are a few steps for generating & hosting documentation.

Automatic generation of documentation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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


