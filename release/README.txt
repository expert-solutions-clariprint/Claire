                                Sylvain Benilan - s.benilan@claire-language.com



                  Installation notice for XL claire v3.3



== Unix ==

	Linux, Darwin, Solaris, Aix, Cygwin ...

	./configure [--prefix=<claire_prefix>]
	make
	[sudo] make install

If you don't define a claire_prefix the default /usr/local is taken and, in
that case only, if no file or link exists with path /usr/local/bin/claire one
is created.




== Win32 - VisualC++ ==

	nmake /f Makefile.nt dirs
	nmake /f Makefile.nt
	nmake /f Makefile.nt install

Before running the install you may edit the init.cl file and overwrite the
default 'C:\\dev' installation path.




== Notes ==

	The 'install' target of the Makefile invoke the install.cl script. Have a look
to this file to learn more about the installation organization.
	Users familiar with the YCS CLAIRE distribution should notice that no env var
CLAIRE3_HOME is needed in the XL distribution. XL CLAIRE knows where it is installed.
	More informations are available in the HTML documentation located in the doc
folder. Last you may visit the www.claire-language.com web site where you'll find a
forum for claire users.
