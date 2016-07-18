/*
 * LibOpenCIF, a library to read the contents of a CIF (Caltech Intermediate
 * Form) file. The library also includes a finite state machine to validate
 * the contents, acording to the specifications found in the technical
 * report 2686, from february 11, 1980.
 * 
 * Copyright (C) 2014, Moises Chavez Martinez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// This file is an example of how to use the two-file version of the library.
// This example is intended for Microsoft Windows users, but also works for GNU/Linux and Mac OS X users.

// To compile, use these commands (in Windows, is recommended to install MinGW to have access to the G++ tool):

// $ g++ libopencif.cc -c                    <- This will generate a "libopencif.o" file.
// $ g++ twofile-version.cc libopencif.o     <- This will generate a binary file (or an EXE file)

// To use, in non-Windows systems, just run: ./a.out
// To use, in Windows systems, just run: a.exe

// NOTE: Is important for Windows users that you use a more advanced terminal than the default CMD
// provided with the system, specially for the window size.

# include <iostream>
# include <vector>
# include <string>

// Import directly the library file.
# include "libopencif.h"

using namespace std;

int main ()
{
   // Print some information about the library
   cout << "Library name: " << OpenCIF::LibraryName << endl;
   cout << "Library version: " << OpenCIF::LibraryVersion << endl;
   cout << "Library author: " << OpenCIF::LibraryAuthor << endl;
   cout << "Library CIF version: " << OpenCIF::LibraryCIFVersion << endl;
   cout << "Library support: " << OpenCIF::LibrarySupport << endl;
   
   OpenCIF::File file;

   // You can modify this line to try the other CIF file
   file.setPath ( "adder4_a2m_sin.cif" );
   
   OpenCIF::File::LoadStatus status;
   status = file.loadFile ();
   
   bool all_ok = false;
   
   switch ( status )
   {
      case OpenCIF::File::AllOk:
         cout << "All ok" << endl;
         all_ok = true;
         break;
         
      case OpenCIF::File::CantOpenInputFile:
         cout << "Can't open input file" << endl;
         break;
         
      case OpenCIF::File::IncompleteInputFile:
         cout << "Incomplete input file" << endl;
         break;
         
      case OpenCIF::File::IncorrectInputFile:
         cout << "Incorrect input file" << endl;
         break;
   }
   
   if ( all_ok )
   {
      cout << "--- File contents cleaned ---" << endl << endl;
      
      vector< string > commands;
      commands = file.getRawCommands ();
      
      for ( int i = 0; i < commands.size (); i++ )
      {
         cout << commands[ i ] << endl;
      }
   }
   
   return ( 0 );   
}
