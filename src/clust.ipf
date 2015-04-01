:userdoc.

.nameit symbol=progname text='Carrie R. Lust'
.nameit symbol=inifile text='CLUST.INI'

.nameit symbol=email1 text='thth@gmx.net'
.nameit symbol=fido text='2&colon.2452/455.999'
.nameit symbol=www text='http&colon.//www.informatik.uni-trier.de/CIP/thielen/'

:docprof.
:ctrldef.
:ctrl ctrlid=1 controls='ESC SEARCH CONTENTS BACK FORWARD' coverpage.
:ectrldef.

.*-------------------------------------------------------------------------
.*fold00.*About the program

:h1 id=about res=1000.About Carrie R. Lust
:artwork name='src/data/clust.bmp' align=center.
:p.Carrie R. Lust is a highly configurable phone-cost and online time
tracking utility for OS/2 in the tradition of Richard Papo's "MemSize"
systemresources monitor.
:p.You may choose freely which values out of 11 available should be displayed,
may let Carrie warn you in several ways (Beep, messagebox, etc.) when certain
events happen (end of current unit, user configured time limit reached, user
configured costs reached, etc.) and may log all connections to a file.
:p.The scheme, after which the charges to be applied are determined, may be
configured by the user to suits her/his needs (though especially this
feature is still far from what I want it to be ...)

:p.:hp2.What's new?:ehp2.

:p.If you want to find out, what is new or was changed in this release, see
the :link refid=history reftype=hd.version history:elink.

:p.Please note that there are more things that could (and will) be included
into the program in future versions. Send me your comments about what you
would like to have ... (though I do not promise anything ;-).

:p.:hp2."Registering":ehp2.

:p.&progname. is now released under the GPL, but as I'd still like to
know that it is used, the :link
refid=register reftype=hd."The Top 10 reasons why not to register &progname."
:elink.;-) still apply.

.*-------------------------------------------------------------------------
.*fold00.*The windows

:h1 id=windows res=2000.The windows
:p.This section should inform you about the various windows of &progname.,
what functions they offer and how to use them.
:p.But as most of them are pretty self-explaining and I am a little bit
overworked right now, it doesn't ;-)
:p.Anyway, if you have got a question, just :link refid=author
reftype=hd.write me a mail:elink.!
:p.Just a few short notes&colon.
:ul.
:li.You may change the font and color of the display window by drag'n'drop
from the appropriate palettes. This information will be automatically saved
and restored at the next start of the program.
:li.Pressing mousebutton 2 in the window will bring up a context menu, where
you can perform various interesting actions.
:li.You can drag the window across the screen by clicking inside and dragging
while holding the mousebutton. The position of the window on the screen
will also be saved.
:li.You can hide or show the titlebar by double clicking inside the window
with mousebutton 1. The state of the titlebar will also be saved.
:eul.

.*-------------------------------------------------------------------------
.*The settings

:h1 id=settings res=2001.The settings
:p.Press mousebutton 2 in the main window and choose settings from the
context menu. The settings window will appear, where you may adjust various,
well ... settings &colon.-)

.*-------------------------------------------------------------------------
.*fold00.*Commandline arguments
:h1 id=cmdlineargs res=3000.Commandline arguments
:p.&progname. accepts the following commandline arguments&colon.

:dl break=all tsize=5.

:dt.:hp2.-a [n]:ehp2.
:dd.If you give this parameter at program start, &progname. will
automatically start counting the connection time and you do not have to press
the "Go" button first. The optional parameter that may be given after "-a" is
the number of seconds &progname. shall wait before starting to count the
time. :p.:hp1.Example:ehp1.&colon. If you type "clust -a 10" on the command
line, &progname. will wait 10 seconds and then automatically start counting
the time. If you just type "clust -a", &progname. will start counting the
time, as soon as it is loaded. If you just type "clust" without the "-a"
parameter, you have to start the counter manually by pressing the "Go"
button. :p.:hp1.Note:ehp1.&colon. If you enabled the connection-autodetect
(see below) this feature will get disabled.

:dt.:hp2.-d [com [n]]:ehp2.
:dd.If you give this parameter at program start, &progname. will try to
automatically detect, when the connection starts and ends and start and stop
the counter accordingly. You may give the number of the com-port that should
be checked ("com"), 1 is the default. With "n" you may give the number of
seconds it takes from when the connection is established until a carrier is
available.
:p.:hp1.Example:ehp1.&colon. "clust -d 2 10" means "Check COM2 and as the
connection is actually running for some time until there is a carrier, add
this 10 seconds to the initial counter value".
:p.:hp1.Note:ehp1.&colon. This feature is still experimental and not
guaranteed to work.

:dt.:hp2.-D [com [n]]:ehp2.
:dd.Pretty much the same as "-d" above, with the exeption, that when the
connection ends, the counter is reset and the window is hidden. When the
connection starts the window is automatically shown. Useful if you start
&progname. from your startup folder or similar - just have it running and it
will automagically appear when you need it, do its work and vanish again
afterwards.

:dt.:hp2.-f filename:ehp2.
:dd.This parameter tells &progname., which file she shall read the charges
data from. If you do not give this parameter, &progname. will try to load
the data from the default file "charges.dat" in the current directory.

:dt.:hp2.-s filename:ehp2.
:dd.This parameter tells &progname., to what :link refid=savefile
reftype=hd.file:elink. the total connection time
shall be written to. This information is restored when you start the program
again. This may be useful e.g. when you have a certain amount of hours free
with your internet provider and want to keep track how much of that time you
already used. If you do not give this parameter, this information will not
be saved/restored.
:p.:hp1.Note:ehp1.&colon. You may change this also in the settings window.
The name will be stored in &inifile..

:dt.:hp2.-t:ehp2.
:dd.If you give this parameter, the timelimit will be applied to the total
connection time and not to the connection time of the current session. This
will not work (i.e. parameter will be ignored) when "units" is selected.

:dt.:hp2.-h:ehp2.
:dd.If you give this parameter, the online help will be disabled. Useful when
you start &progname. from some other directory, so she will not display the
"Help file not found" message.

:edl.

.*-------------------------------------------------------------------------
.*fold00.*Remote control
:h1 id=remotecontrol.Remote control
:p.An interesting feature of &progname. is the ability to control actions
of the program remotly via a named pipe ("\pipe\carrierlust"). Using the named
pipe, other processes can send commands to &progname. e.g. to start or stop
the counter. This works even if the process issuing the command is running
on a different computer (connected to the computer, the program is running on,
via a network).

:p.By now, &progname. understands the following commands&colon.
:dl compact.
:dt.:hp2.start:ehp2.
:dd.Starts the counter
:dt.:hp2.stop:ehp2.
:dd.Stops the counter
:dt.:hp2.reset:ehp2.
:dd.Resets the counter
:dt.:hp2.hide:ehp2.
:dd.Hides the display window
:dt.:hp2.show:ehp2.
:dd.Shows the display window
:dt.:hp2.exit:ehp2.
:dd.Quits &progname.
:edl.
:p.You can use OS/2's "echo" command, to control &progname. from a
commandline&colon.
:xmp.
[c&colon.\]echo start > \pipe\carrierlust
:exmp.
e.g. will start the counter.
:p.If &progname. would be running on a computer different from the one you
are using, the line should read&colon.
:xmp.
[c&colon.\]echo start > \\server\pipe\carrierlust
:exmp.
where "server" is the name of the computer &progname. is running on.

:p.This feature is very useful, if you want to include &progname. in your
login script; you can start the counter as soon as the connection is
established and stop it when you disconnect, simply by sending the
appropriate commands through the pipe.

.*-------------------------------------------------------------------------
.*fold00.*Past, present + future
:h1 id=pastpresentfuture res=5000.Past, present &amp. future
:p.This section provides info about the history of &progname., some info
about (bugs in) the current release and things that may be added or changed
in the future.

.*-------------------------------------------------------------------------
.*FOLD00.*Version history
:h2 id=history.Version history
:p.Here you can see what was added or changed in the different versions of
the program.

:dl break=all tsize=5.
:dt.:hp2.Version 1.17:ehp2.
:dd."I'm free!" ;-)
:ul compact.
:li.Carrie R. Lust becomes free software under the GPL.
:li.You may now give floating point numbers for the money per unit, which
makes it easier to configure for one second units e.g.
:li.Bugfix&colon. Window was one pixel "to long".
:li.Bugfix&colon. Window wasn't made the topmost one at startup.
:eul.

:dt.:hp2.Version 1.15:ehp2.
:dd."Bugfix!" the programmer cried ...
:ul compact.
:li.(Hopefully) fixed the bug that caused &progname. to sometimes crash on
exit.
:li.The limit can now be used with the total connection time rather than
with the session connection time if user wants (see :link refid=cmdlineargs
reftype=hd.commandline arguments:elink. for more info)
:li.Reduced the flickering of the display window.
:eul.

:dt.:hp2.Version 1.10:ehp2.
:dd.Well, I didn't expect it to come so soon, but here it is!
:ul compact.
:li.Implemented the much requested :link refid=cmdlineargs
reftype=hd.connection-autodetect:elink. feature (though it is
still only experimental and not guaranteed to work!)
:li.Connections where the counter never was started will no longer get logged.
:li.Extensive error messages that appeared when two instances of &progname.
were started and tried to access the pipe are now only shown once.
:li.Two new :link refid=remotecontrol reftype=hd.remote commands:elink.,
"hide" and "show" to hide and show the display window.
:li.The :link refid=savefile reftype=hd.total connection time savefile:elink.
now can be set in the settings window.
:li.Time- and currency-values are now displayed using your system's
country-settings.
:li.Better parsing of the charges-file.
:eul.

:dt.:hp2.Version 0.96:ehp2.
:dd.Just a bugfix release.
:ul compact.
:li.Added the example/default charges file "charges.dat" (I forgot to include
it in the 0.95 archive).
:li.Fixed a small bug.
:eul.

:dt.:hp2.Version 0.95:ehp2.
:dd.Several features were added&colon.
:ul compact.
:li.Possibility to :link refid=cmdlineargs reftype=hd.autostart counter:elink.
(possibly delayed) when program is loaded.
:li.Total connection time may be saved to a :link refid=savefile
reftype=hd.file:elink. and restored at the next program start.
:li.Added a popup menu to the window, so most actions can be performed this
way too.
:li.Added option to "count down" the last 10 seconds of every unit and
have &progname. output a beep for any of them.
:li.Added the online help (much improved version of the old "clust.doc").
:li.Improved the definition of the charges to be used, so charges for all
weekdays and special dates now can be stored in one single file and the right
charges will automatically be applied.
:li.Added the :link refid=remotecontrol reftype=hd.remote control feature:elink.,
that allows to control several actions of &progname. from outside.
:eul.

:dt.:hp2.Version 0.73b1:ehp2.
:dd.This was the first public version of &progname..

:edl.

.*-------------------------------------------------------------------------
.*FOLD00.*Bugs

:h2 id=bugs.Known bugs
:p.No "real" bugs are known at the moment, but there are still many things
that should be improved, e.g. the scheme for the charges requires still much
work. Other inconveniences include&colon.
:ul.
:li.&progname. may get "slightly confused" if you change the system
time while the program is running.
:li.What charges apply for the current day is only checked when the
program starts. If you use &progname. crossing midnight, the charges of the
day passed will still be used for the new day.
:li.The entry in the context menu does not reflect the state
(running/suspended) of the counter.
:li.The parsing routine for the charges file is still a little bit
error-prone in some cases when entries are not entered properly.
:li.When starting/stopping the counter remotly, the "stop/go" button does
not change it's text to reflect the state (running/suspended) of the counter.
:eul.

.*-------------------------------------------------------------------------
.*fold00.*Future enhancements

:h2 id=future.Future enhancements
:p.There are still :hp1.a lot:ehp1. of things to be done, especially the
handling of the data files for the information about the different charges
still needs much additional work. NLS support (language), possibility to
store all chargesinfo in one file with different providers &amp. zones,
automatic "detection" of special dates, possibility to change provider and
zone from inside the program, etc. are other things that will follow in the
future. If you have some other feature that you want to see included, just
:link refid=author reftype=hd.let me know:elink.!

:p.Addition for v1.15&colon. ... or look at the source and do it 
yourself! ;-)

.*-------------------------------------------------------------------------
.*fold00.*Files

:h1 id=files.Files
:p.This section informs you about some of the files that are used by
&progname.

.*-------------------------------------------------------------------------
.*fold00.*The charges data file

:h2 id=chargesfile.The charges data file
:p.This file is parsed by &progname. at program start, to load the various
charges that might be used. &progname. by default tries to load this
information from "charges.dat", but you may give any other filename, using
the "-f" :link refid=cmdlineargs reftype=hd.commandline argument:elink..

:p.The format for the file is as following&colon.
:xmp.
# Carrie R. Lust charges data for German Telekom, City region
# This and the line above are comments

# -------------------------------------------------------------------------

Day&colon. Monday
Day&colon. Tuesday
Day&colon. Wednesday
Day&colon. Thursday
Day&colon. Friday

Charge&colon. 00&colon.00&colon.00, 2400, 12, Mondschein
Charge&colon. 02&colon.00&colon.00, 2400, 12, Nacht
Charge&colon. 05&colon.00&colon.00, 1500, 12, Freizeit
Charge&colon. 09&colon.00&colon.00,  900, 12, Vormittag
Charge&colon. 12&colon.00&colon.00,  900, 12, Nachmittag
Charge&colon. 18&colon.00&colon.00, 1500, 12, Freizeit
Charge&colon. 21&colon.00&colon.00, 2400, 12, Mondschein

# -------------------------------------------------------------------------

Day&colon. Saturday
Day&colon. Sunday
Day&colon. Dec 24
Day&colon. Dec 25
Day&colon. Dec 26

Charge&colon. 00&colon.00&colon.00, 2400, 12, Mondschein
Charge&colon. 02&colon.00&colon.00, 2400, 12, Nacht
Charge&colon. 05&colon.00&colon.00, 1500, 12, Freizeit
Charge&colon. 09&colon.00&colon.00, 1500, 12, Vormittag
Charge&colon. 12&colon.00&colon.00, 1500, 12, Nachmittag
Charge&colon. 18&colon.00&colon.00, 1500, 12, Freizeit
Charge&colon. 21&colon.00&colon.00, 2400, 12, Mondschein

 ...
:exmp.
:p.The file is interpreted line by line. Comments (lines starting with '#')
and empty lines are ignored.

:p.Lines starting with "Day&colon." are used to determine for what weekdays
or dates the later following charges are to be used. The value after
"Day&colon." may be one out of "Monday", "Tuesday", "Wednesday", "Thursday",
"Friday", "Saturday" or "Sunday" meaning, the following charges should be used,
if &progname. is started on this day of the week, or a date in format "Mon nn"
where "Mon" is one out of "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
"Aug", "Sep", "Oct", "Nov" or "Dec" and nn is the day of the month.

:p.If you give a date, this has higher priority than the weekday, so if in
the above example, the 25th December would be a Tuesday e.g., &progname.
would still use the charges from the second "block".

:p.Lines starting with "Charge&colon." are used to define the various charges
that may be used for the days given before. The format of this line is
"Charge&colon. hh&colon.mm&colon.ss, ll, nn, name", where hh&colon.mm&colon.ss
is the time of day, from when on this charge applies, ll is the length of
one telephone unit in 10th of a second, nn is the costs for each unit (in the
smallest currency unit available) and name is the name of this charge (must
be present, even though it is not used by now &colon.-)

:p.So there ... I hope everyone understands what I mean. If not ... well, I'm
tired and it's pretty late already ... ;-)

.*-------------------------------------------------------------------------
.*fold00.*The save file

:h2 id=savefile.The save file
:p.If you give the "-s" :link refid=cmdlineargs reftype=hd.commandline
argument:elink., you may specify a file, where your total connection time
will be saved to, when the program ends. This data is reloaded, when you
start &progname. again.

:p.This may be useful e.g. when you have a certain amount of hours free
with your internet provider and want to keep track how much of that time you
already used.

:p.If you want to reset this time to 0, simply delete the file or set
the stored time to 0 (can be done with any text editor, the time is stored
as a simple ASCII number).

:p.:hp1.Note&colon.:ehp1. The time is stored in 10th of a second, not
seconds or whatever else!

.*-------------------------------------------------------------------------
.*fold00.*Disclaimer & legal stuff

:h1 id=disclaimer.Disclaimer &amp. legal stuff
:p.Following are the usual disclaimers. For those of you, who have read them
far too many times, here is just the short version&colon.

:p."I didn't do it! I didn't do it! Butthead did it!" ;-)

:p.Everyone else, please read this and keep in mind&colon.

:p.Though this program has been tested quite a lot, there may still be lots
of bugs in it (even serious ones - though I do not think so). Do not blame
me, if this program screws up your files or whatever.

:p.:hp2.YOU ARE USING THIS PROGRAM AT YOUR OWN RISK!:ehp2. I don't take any
responsibillity for damages, problems, custodies, marital disputes,
etc. resulting from use, inability to use, misuse, possession or
non-possession of this program directly or indirectly.
I also don't give any warranty for bug-free operation, fitness
for a particular purpose or the appropriate behaviour of the program
concerning animals, programers and little children.

:p.Or, in a few words&colon.
If its good, I am responsible.
If its bad, its all your fault. ;-)

:p.For the full disclaimer (yes, it's even bigger! ;-) read sections 11
and 12 of the GPL (following hereafter).

:p.All trademarks mentioned anywhere around her are property of their
owners and the like ...

.*fold00.*GNU Public License

:h1 id=gpl.GNU GENERAL PUBLIC LICENSE

:lines.
                    GNU GENERAL PUBLIC LICENSE
                       Version 2, June 1991

 Copyright (C) 1989, 1991 Free Software Foundation, Inc.
     59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.

                            Preamble

  The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
License is intended to guarantee your freedom to share and change free
software--to make sure the software is free for all its users.  This
General Public License applies to most of the Free Software
Foundation's software and to any other program whose authors commit to
using it.  (Some other Free Software Foundation software is covered by
the GNU Library General Public License instead.)  You can apply it to
your programs, too.

  When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
this service if you wish), that you receive source code or can get it
if you want it, that you can change the software or use pieces of it
in new free programs; and that you know you can do these things.

  To protect your rights, we need to make restrictions that forbid
anyone to deny you these rights or to ask you to surrender the rights.
These restrictions translate to certain responsibilities for you if you
distribute copies of the software, or if you modify it.

  For example, if you distribute copies of such a program, whether
gratis or for a fee, you must give the recipients all the rights that
you have.  You must make sure that they, too, receive or can get the
source code.  And you must show them these terms so they know their
rights.

  We protect your rights with two steps&colon. (1) copyright the software, and
(2) offer you this license which gives you legal permission to copy,
distribute and/or modify the software.

  Also, for each author's protection and ours, we want to make certain
that everyone understands that there is no warranty for this free
software.  If the software is modified by someone else and passed on, we
want its recipients to know that what they have is not the original, so
that any problems introduced by others will not reflect on the original
authors' reputations.

  Finally, any free program is threatened constantly by software
patents.  We wish to avoid the danger that redistributors of a free
program will individually obtain patent licenses, in effect making the
program proprietary.  To prevent this, we have made it clear that any
patent must be licensed for everyone's free use or not licensed at all.

  The precise terms and conditions for copying, distribution and
modification follow.
 
                    GNU GENERAL PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. This License applies to any program or other work which contains
a notice placed by the copyright holder saying it may be distributed
under the terms of this General Public License.  The "Program", below,
refers to any such program or work, and a "work based on the Program"
means either the Program or any derivative work under copyright law&colon.
that is to say, a work containing the Program or a portion of it,
either verbatim or with modifications and/or translated into another
language.  (Hereinafter, translation is included without limitation in
the term "modification".)  Each licensee is addressed as "you".

Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running the Program is not restricted, and the output from the Program
is covered only if its contents constitute a work based on the
Program (independent of having been made by running the Program).
Whether that is true depends on what the Program does.

  1. You may copy and distribute verbatim copies of the Program's
source code as you receive it, in any medium, provided that you
conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the
notices that refer to this License and to the absence of any warranty;
and give any other recipients of the Program a copy of this License
along with the Program.

You may charge a fee for the physical act of transferring a copy, and
you may at your option offer warranty protection in exchange for a fee.

  2. You may modify your copy or copies of the Program or any portion
of it, thus forming a work based on the Program, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions&colon.

    a) You must cause the modified files to carry prominent notices
    stating that you changed the files and the date of any change.

    b) You must cause any work that you distribute or publish, that in
    whole or in part contains or is derived from the Program or any
    part thereof, to be licensed as a whole at no charge to all third
    parties under the terms of this License.

    c) If the modified program normally reads commands interactively
    when run, you must cause it, when started running for such
    interactive use in the most ordinary way, to print or display an
    announcement including an appropriate copyright notice and a
    notice that there is no warranty (or else, saying that you provide
    a warranty) and that users may redistribute the program under
    these conditions, and telling the user how to view a copy of this
    License.  (Exception&colon. if the Program itself is interactive but
    does not normally print such an announcement, your work based on
    the Program is not required to print an announcement.)
 
These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Program,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Program, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote it.

Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Program.

In addition, mere aggregation of another work not based on the Program
with the Program (or with a work based on the Program) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

  3. You may copy and distribute the Program (or a work based on it,
under Section 2) in object code or executable form under the terms of
Sections 1 and 2 above provided that you also do one of the following&colon.

    a) Accompany it with the complete corresponding machine-readable
    source code, which must be distributed under the terms of Sections
    1 and 2 above on a medium customarily used for software interchange; or,

    b) Accompany it with a written offer, valid for at least three
    years, to give any third party, for a charge no more than your
    cost of physically performing source distribution, a complete
    machine-readable copy of the corresponding source code, to be
    distributed under the terms of Sections 1 and 2 above on a medium
    customarily used for software interchange; or,

    c) Accompany it with the information you received as to the offer
    to distribute corresponding source code.  (This alternative is
    allowed only for noncommercial distribution and only if you
    received the program in object code or executable form with such
    an offer, in accord with Subsection b above.)

The source code for a work means the preferred form of the work for
making modifications to it.  For an executable work, complete source
code means all the source code for all modules it contains, plus any
associated interface definition files, plus the scripts used to
control compilation and installation of the executable.  However, as a
special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary
form) with the major components (compiler, kernel, and so on) of the
operating system on which the executable runs, unless that component
itself accompanies the executable.

If distribution of executable or object code is made by offering
access to copy from a designated place, then offering equivalent
access to copy the source code from the same place counts as
distribution of the source code, even though third parties are not
compelled to copy the source along with the object code.
 
  4. You may not copy, modify, sublicense, or distribute the Program
except as expressly provided under this License.  Any attempt
otherwise to copy, modify, sublicense or distribute the Program is
void, and will automatically terminate your rights under this License.
However, parties who have received copies, or rights, from you under
this License will not have their licenses terminated so long as such
parties remain in full compliance.

  5. You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Program or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Program (or any work based on the
Program), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Program or works based on it.

  6. Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the
original licensor to copy, distribute or modify the Program subject to
these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties to
this License.

  7. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Program at all.  For example, if a patent
license would not permit royalty-free redistribution of the Program by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Program.

If any portion of this section is held invalid or unenforceable under
any particular circumstance, the balance of the section is intended to
apply and the section as a whole is intended to apply in other
circumstances.

It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system, which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.

This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.
 
  8. If the distribution and/or use of the Program is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Program under this License
may add an explicit geographical distribution limitation excluding
those countries, so that distribution is permitted only in or among
countries not thus excluded.  In such case, this License incorporates
the limitation as if written in the body of this License.

  9. The Free Software Foundation may publish revised and/or new versions
of the General Public License from time to time.  Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.

Each version is given a distinguishing version number.  If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation.  If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.

  10. If you wish to incorporate parts of the Program into other free
programs whose distribution conditions are different, write to the author
to ask for permission.  For software which is copyrighted by the Free
Software Foundation, write to the Free Software Foundation; we sometimes
make exceptions for this.  Our decision will be guided by the two goals
of preserving the free status of all derivatives of our free software and
of promoting the sharing and reuse of software generally.

                            NO WARRANTY

  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.

  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

                     END OF TERMS AND CONDITIONS
 
            How to Apply These Terms to Your New Programs

  If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these terms.

  To do so, attach the following notices to the program.  It is safest
to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least
the "copyright" line and a pointer to where the full notice is found.

    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


Also add information on how to contact you by electronic and paper mail.

If the program is interactive, make it output a short notice like this
when it starts in an interactive mode&colon.

    Gnomovision version 69, Copyright (C) year  name of author
    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.

The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License.  Of course, the commands you use may
be called something other than `show w' and `show c'; they could even be
mouse-clicks or menu items--whatever suits your program.

You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the program, if
necessary.  Here is a sample; alter the names&colon.

  Yoyodyne, Inc., hereby disclaims all copyright interest in the program
  `Gnomovision' (which makes passes at compilers) written by James Hacker.

  <signature of Ty Coon>, 1 April 1989
  Ty Coon, President of Vice

This General Public License does not permit incorporating your program into
proprietary programs.  If your program is a subroutine library, you may
consider it more useful to permit linking proprietary applications with the
library.  If this is what you want to do, use the GNU Library General
Public License instead of this License.

:elines.

.*-------------------------------------------------------------------------
.*fold00.*Author & Carrie R. Lust homepage

:h1 id=author.Author &amp. &progname. homepage
:p.:hp7.Author:ehp7.

:dl break=all tsize=5 compact.

:dt.:hp2.Snail mail:ehp2.
:dd.Thorsten Thielen c/o Sascha Weber, Postfach 3928, 54229 Trier, Germany

:dt.:hp2.e-Mail:ehp2.
:dd.&email1.

:dt.:hp2.WWW:ehp2.
:dd.&www.

:dt.:hp2.Fidonet:ehp2.
:dd.&fido. (I rarely check my Fido mail, only once per month or so, so 
answers here may take some time)

:edl.

:artwork name='src/data/teamlogo.bmp' align=center.
:p.Proud member of Team OS/2 Region Trier (:hp1.www.teamos2.ipcon.de:ehp1.), 
the makers of the "Team Trier Collection"-CDROM.

:lm margin=1.
:p.
Suggestions and bug-reports are always welcome. Well ... bug-reports
are perhaps not :hp1.that:ehp1. welcome ... ;-)
:p.
.br
:hp7.&progname. homepage:ehp7.
:p.Visit the &progname. homepage for info and new versions&colon.
&www./clust/

.*-------------------------------------------------------------------------
.*fold00.*Credits

:h1 id=credits.Credits
:p.I wish to thank the following people, for their help and support with
&progname.&colon.

:ul.
:li.Thanks got to :hp1.Sascha Weber:ehp1. for his wonderful beta testing of
&progname.
:li.This program does not only bear some resemblance to, but also uses some
code (the routines for window-draging and hiding/showing the titlebar) from
:hp1.Richard Papo's:ehp1. excellent "MemSize" systemressources monitor.
(You can find out more about MemSize at http&colon.//www.msen.com/~rpapo).
:li.Thanks also go to all the users who notified me of bugs, made suggestions
or just wrote me a mail about &progname.!
:eul.

.*-------------------------------------------------------------------------
.*fold00.*Registering
:h1 id=register."Registering"
:p.&progname. is now released under the GPL, but as I'd still like to know
who uses my programs, it would be nice, if you registered by :link
refid=author reftype=hd.sending an e-mail (or postcard or whatever) to
me:elink.. Just write something like "Hi, I use your program &progname.!"
and I'm satisfied. If you do :hp1.not:ehp1. want to be included in the mailing
list for news and infos about &progname. do not forget to tell me!

:p.But I guess there are a lot of people out there who have seen &progname.,
worked with it for a while but just don't want to register by writing me a
mail. Well, for you I've assembled this list of ...
:p.:hp2.The Top 10 reasons why not to register &progname.:ehp2.

:ul compact.

:li.In my opinion, &progname. is a pretty bad program. I don't like the color
or font of the windows (and far less I like the idea of being able to change
them!), I am not interested in any of the stats it can show me and I heard
that there once really was found a bug! Not to mention the crappy support;
writing an e-mail to get help is far to complicated.

:li.I'm totally satisfied with anything that &progname. 0.73b1 offers. I'll
find my own workarounds for this bugs that might be discovered! I'm never
going to use this unit countdown thing or the online help stuff! So spare
me by your updates ...

:li.Who cares for info on new releases? Why should I get on yet another of
these mailing-lists? My mailbox is overflowing on a regular base and I'm
daily checking the "incoming" directory of Hobbes anyway!

:li.I just can't spare the time to write a mail to you! See, I've got a job,
a wife, 10 kids or so, a girlfriend, a car, a house, a swimming pool and
1000 Webpages that I still haven't visited yet, so I'm really busy night
and day! I really don't want to think of what I would miss in this lost five
minutes ...

.*:li.$10 is far too much money for this program! For this big amount I could,
.*well, buy half of an audio CD! I could go out to dinner with my friend (well,
.*at least if we have already eaten before). I could think of thousand things
.*more ...

:li.Why should I make you feel that it's a good thing to develop software for
OS/2? There are far to many programs for OS/2 already, we don't want to get
the market oversupplied, do we?

:li.There are lot's of other programs out there, that do the thing! Well ok,
maybe they don't have that nice PM interface, might be that they are lacking
a lot of the functionallity that &progname. offers and maybe actually there
are only one or two of them, but at least I don't have to spend hours and
hours writing longish mails to their authors!

:li.I don't find supporting the mailware concept of any use. Developers
giving away fully working programs and then hoping that someone actually will
write a mail when using them, when (s)he can get away without, are an all too
trustfull bunch of fools!

:li.Why should I try to support OS/2 software? OS/2 is dead, believe me!
"I'm Bill Gates of MicroBorg. This OS will be assimilated. Development is
futile."

:li.This space is reserved for future use ;-) (will be filled, when NLS
for &progname. is working).

:li.I can't write! I don't know how to send e-mail!! I don't even have an
account!!! And I'm using Windows!!!!

:eul.

.*-------------------------------------------------------------------------
.*fold00.*Dedication

:h1 id=dedication.Dedication
:p.:artwork name='src/data/wow.bmp' align=center.
:hp2.
.ce Carrie R. Lust is dedicated to Wendy O. Williams.
:ehp2.
.ce (1950-1998)

.*-------------------------------------------------------------------------
.*There's more where that came from ...

:h1 id=moreprogs.There's more where that came from ...
:p.&progname. is by no means the only program for OS/2 that I have written.
Here is a little list of more :hp1.freely available:ehp1. programs out of
my editor&colon.

:dl break=all tsize=5.

:dt.:hp2.Gotcha!:ehp2. (Screencapture program)
:dd.Capture windows, window interiors, (parts of) the screen. Timer
controlled, automatic, repeated capturing. Saving to file or clipboard,
etc.

:dt.:hp2.Wanda:ehp2. ("Sticky notes" for the desktop)
:dd.Notes windows in all colors, sizes, etc. Large number of configuration
options. Printing, saving, etc.

:dt.:hp2.Minta:ehp2. (MP3 tagging, listing and information utility)
:dd.Creating, editing, removing of ID3 tags, listing and showing
MP3 audio files with their information, autorenaming function, etc.

:dt.:hp2.Xened:ehp2. ("Xenon II" editor)
:dd.Editing of weapon prices, editing of the maps, tips and tricks, etc.
Available also for DOS and Linux.

:dt.:hp2.CAD/Off:ehp2. ("Reboot disabler")
:dd.Deactivates the CTRL-ALT-DEL key-combination until system shutdown.

:dt.:hp2.Tomo:ehp2. (Tetris clone)
:dd.More "stones", configurable playground size, etc. Unfortunatly only for
DOS and only in german (I've lost the sources ...)

:edl.
:p.Apart from the programs listed here, there are others in developement
right now (even some games!). If you would like to get more information
just take a look at &www./projects.html !

.*-------------------------------------------------------------------------

:euserdoc.
