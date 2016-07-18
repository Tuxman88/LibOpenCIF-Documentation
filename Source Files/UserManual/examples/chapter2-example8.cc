# include <iostream>
# include <string>
# include <vector>
# include <opencif>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main ()
{
   cout << "LibOpenCIF: How to access the raw commands." << endl;
   
   OpenCIF::File cif_file;
   string file_path;
   
   // Prepare the CIf file
   file_path = "inv_x1.cif";
   cif_file.setPath ( file_path );
   
   OpenCIF::File::LoadStatus status;
   
   // Try to open it
   status = cif_file.openFile ();
   
   if ( status != OpenCIF::File::AllOk )
   {
      cout << "LibOpenCIF: Error opening file.";
      return ( 1 );
   }
         
   // Validate the contents (this will load the
   // raw commands into memory)
   status = cif_file.validateSyntax ();
   
   // I'm not validating if the file is incomplete, since
   // such case isn't an error in this example.
   if ( status == OpenCIF::File::IncorrectInputFile )
   {
      cout << "LibOpenCIF: Error validating file.";
      return ( 1 );
   }
   
   // Prepare two vectors, one to store the raw commands
   // and the other to store the clean commands
   vector< string > raw_commands;
   vector< string > clean_commands;
   
   raw_commands = cif_file.getRawCommands ();
   
   // Clean the commands, this will replace the commands that
   // I just saved in the previous instruction
   cif_file.cleanCommands ();
   
   // Get the new commands
   clean_commands = cif_file.getRawCommands ();
   
   // I'm going to print the raw commands side by side with
   // the clean commands. I'm not validating the size of both
   // vectors since both must have the same amount of commands.
   for ( int i = 0; i < raw_commands.size (); i++ )
   {
      cout << "RAW:   " << raw_commands[ i ] << endl;
      cout << "CLEAN: " << clean_commands[ i ] << endl;
   }
   
   // I'm skiping the remaining steps on the loading chain because
   // they are not needed for this example.

   return ( 0 );
} 
