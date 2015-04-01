-- CARRIE R. LUST 1.17 --

 Carrie R. Lust is a highly configurable phone-cost and online time
tracking utility for OS/2 in the tradition of Richard Papo's "MemSize"
systemresources monitor.

 Carrie allows to automatically detect when a connection has been
established and starts the counter and stops it again afterwards.

 You may choose freely what values out of 11 available should be
displayed, may let Carrie warn you in several ways (Beep, messagebox,
etc.) when certain events happen (end of current unit, user configured
time limit reached, user configured costs reached, etc.) and may log all
connections to a file.

 The scheme, after which the charges to be applied are determined, may be
configured by the user to suits her/his needs (though especially this
feature is still far from what I want it to be ...)

 Since v1.17, Carrie R. Lust is free software released under the GPL.
See the file COPYING for details.


-- INSTALLATION --

 If you've unzipped the archiv (which seems to be the case, since you are
reading this file ;-) and copied the files to some appropriate directory,
you're done. You may run "install.cmd" to create a WPS-object for Carrie.

 ATTENTION: If you had installed a previous version (before 1.10) of
Carrie, *delete* the file CLUST.INI as it is not compatible with Carrie
R. Lust 1.17! Also *delete* the old files CHARGES.DAT/WEEKEND.DAT/etc.
(not compatible with 1.17 too).

Oh yes, and you safely may ignore those "cycle detected by make_type" :-)


-- BUILDING --

  Carrie was originally developed under OS/2 using emx/gcc 0.9d and
dmake 4.0. I can't say if it would be hard to adjust it for other
compilers or make utilities (though I guess it will need some work to
port it to another OS due to missing seperation of program logic and
system specific issues like e.g. windowing - aka: bad code). If you
want to recompile the program, take a look at the Makefile and adjust
the settings (probably only the "I" macro that tells where you keep
your include files) and then just run dmake.


-- MORE INFO --

For more information see the online help!

Have fun!
Thorsten Thielen <thth@gmx.net>
(Member of Team OS/2 Region Trier e.V.)
