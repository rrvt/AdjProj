# Adjust Visual Studio 17 Project File

Sort the file names by the name of the file rather than the "path\filename".  Sorts the Resource Files
in the order "...rc", "...rc2", image file.  Unfortunately, the sections are sorted separately due
to the organization of the project file.

## Getting Started

Build with Visual Studio 2017.  Execute.  The open file icon is used to open the ".vcxproj" file.  The
crossed tools will do the adjustment.  The result can be examined in the window, the files are near the
bottom of the file, scroll down.  The third toolbar image of a floppy disk will save the file backing up
the original before writing.

### Installing

The ...msi file will install the application.

## Running the tests

Copy an vcxproj file into the data directory and practice with it.

## Updates

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
  * The library now contains logic to manage the actual size of fonts on the display and printed page.
  * Before the font point size was expressed as an integer 10 x font size (e.g. 120).  Now it is
    expressed as as a decimal number of the actual point size (eg. 12.0).
  * ManipT used during output was changed to remove a memory leak.
  * The Options feature was moved to the Extras and Library.  The options include an option to adjust
    the scale of the displayed and printed output.

### Update 11/25/20

Library improvement.  Added options for print orientation and margins.

### Update 11/07/20

Modified the way data is displayed and printed to avoid a conflict between the print thread and the
display thread.

### Update 9/10/20
Library improvement project.  Changed the Expandable Array classes, added templates for a pointer only
class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class many times
worrying about exactly how it should be defined.  So I turned it into a template, which of course then
I needed to go back and add it to all the programs.  Severl iterations later I added some documentation
and I am uploading the programs today.

### Update 7/30/20

Changed allmost all the startLoop, nextItem loops to iter(), iter++ loops.  The advantage is that there
can be many iterators in the same function for the same data (they are just named differently, eg. iter1,
inter2, etc.).

### Update 5/1/2020

Added logic so that between Open/Adjust/Save the data structures are cleared.  Fixec Resource adjustment.

## Authors

Bob -- K6RWY, romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

