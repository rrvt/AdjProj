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

