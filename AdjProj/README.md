# Adjust Visual Studio 17 Project File

Sort the file names by the name of the file rather than the "path\filename".  Sorts the Resource
Files in the order "...rc", "...rc2", image file.  Unfortunately, the sections are sorted
separately due to the organization of the project file.

## Getting Started

Build with Visual Studio 2017.  Execute.  The open file icon is used to open the ".vcxproj" file.
The crossed tools will do the adjustment.  The result can be examined in the window, the files are
near the bottom of the file, scroll down.  The third toolbar image of a floppy disk will save the
file backing up the original before writing.

### Installing

The ...msi file will install the application.

## Running the tests

Copy an vcxproj file into the data directory and practice with it.

## Updates

### Update 8/4/24

Library update.

### Update 6/22/24

Added an icon to the MIT License rtf file.

### Update 6/21/24

Added MIT License to installation.

### Update 4/18/24

Improved the way Toolbars and Window Position and size are handled.

### Update 2/16/24

Reorganized the Library so that it compiles once into Debug and Release directories under the
Library directory.

### Update 12/11/23

Improve ExpandableP (modify) and associated changes.

### Update 6/25/23

Library Update.

### Update 3/31/23

Add orientation dialog to application.

### Update 3/15/23

Complete move of orientation to reports.

### Update 3/13/23

When there are multiple reports the printed output orientation is by report, not the printer.  Thus
the orientation is associated with the report and the standard Options dialog contains the
orientation for the NotePad Report.  Other reports will need a way to designate the printer output
orietation.

The NotePad output managers have been moved into CScrView so that it is available in all
applications without further development.  Of course other reports may be written following the
pattern of the NotePad report.

Some additional bug fixes.

### Update 3/8/23

Added numbers to notepad archive output.

### Update 3/7/23

Fixed (hopefully) Print and Print Preview.  See MakeApp for details.

### Update 10/30/22

Add logic to start app in the same position and size as when it exited the previous time.  Update
the background of the toolbar.  Update the icons in the help file.

### Update 8/3/22

Minor Library updates.

### Update 4/15/22

Big adventure in February when I started moving to a new Win11 and Visual Studio 2022.  I now
feel that this version is working in the new environment.  There were several changes made to the
app in order to compile properly on VS22.

### Update 01/31/22

Updates to the library, mostly about the toolbar, but also NewAllocator, and a minor addition to
Expandable.

Also scrubbed the project files to remove all references to precompiled header files which I turned
off in VS17.  Unfortnately VS does not remove all references and pch files kept cropping up.  Not
only does that slow down the compiler but the files are large...

### Update 12/18/21

While creating a template for a dialog box only application with a toolbar the Library was added to
and changed to hopefully simplify toolbar creation.  This version of the toolbar includes buttons,
edit boxes, combo boxes and drop down menus as well as the traditional 16x15 icons.

AdjProj is a tradional App, has a traditional 16x15 pixel icon toolbar.

### Update 11/13/21

But the major changes are in the library:

  - Expandable and ExpandableP -- moved the functions out of the class to make the compilation
smaller, also fixed one bug (or feature) in the ExpandableP insert sorted function that would
throw out entries that were already in in the array.
  - FileIO -- Changed the type of path from "String&" to "TCchar*".  It turns out that automatic
conversion from String to TCchar* is easy, but the reverse is is not easy.  Also added a function
to get the length of a file given a path.
  - FineName -- Added a function to get the directory name of from a path
  - NewAllocator -- Corrected the debug dependency from if to ifdef
  - ToolBar -- Added data for drop down menus

### Update 10/31/21

Changed Resources (i.e. xxx.rc data) access so that it will work with a dll.  Changed the logic in
the About Box code.  Some other library changes.  Some corresponding changes in the application.

### Update 10/2/21

Library update only.

### Update 4/14/21

Minor updates due to changes in the library.

### Update 2/15/21

Fixed Backup date preparation to use 2 digit year instead of century.  Worked last year due to
coincidence (ugh!!!).

### Update 2/5/21

The library has new features for an Access database interface.  The Icons where changed.

### Update 1/20/21

Added Help file.  Cleaned up toolbar and menu commands.  Added flying comments for toolbar.

### Update 1/4/21

Most of the changes were to the Library which impacted Adjust Project File.

Library Changes:
  * CApp includes a function to identify the application to Windows.
  * CApp requires the application's "this" pointer at initialization.
  * CApp includes inline functions for retrieving a pointer to the document object and view object
  * The library now contains logic to manage the actual size of fonts on the display and printed
page.
  * Before the font point size was expressed as an integer 10 x font size (e.g. 120).  Now it is
    expressed as as a decimal number of the actual point size (eg. 12.0).
  * ManipT used during output was changed to remove a memory leak.
  * The Options feature was moved to the Extras and Library.  The options include an option to
adjust the scale of the displayed and printed output.

### Update 11/25/20

Library improvement.  Added options for print orientation and margins.

### Update 11/07/20

Modified the way data is displayed and printed to avoid a conflict between the print thread and the
display thread.

### Update 9/10/20
Library improvement project.  Changed the Expandable Array classes, added templates for a pointer
only class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class
many times worrying about exactly how it should be defined.  So I turned it into a template, which
of course then I needed to go back and add it to all the programs.  Severl iterations later I added
some documentation and I am uploading the programs today.

### Update 7/30/20

Changed allmost all the startLoop, nextItem loops to iter(), iter++ loops.  The advantage is that
there can be many iterators in the same function for the same data (they are just named
differently, eg. iter1, inter2, etc.).

### Update 5/1/2020

Added logic so that between Open/Adjust/Save the data structures are cleared.  Fixec Resource
adjustment.

## Authors

Bob -- K6RWY, romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

