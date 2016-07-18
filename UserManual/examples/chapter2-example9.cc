# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <opencif>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::istringstream;

void PrintBoxCommand ( string command );

int main ()
{
   cout << "LibOpenCIF: An approach of using the clean commands with C++ string streams." << endl;
   
   OpenCIF::File cif_file;
   string file_path;
   
   // Prepare the CIf file
   file_path = "inv_x1.cif";
   cif_file.setPath ( file_path );
   
   OpenCIF::File::LoadStatus status;
   
   // Try to load the whole CIF file
   status = cif_file.loadFile ();
   
   if ( status == OpenCIF::File::IncorrectInputFile )
   {
      cout << "LibOpenCIF: Error loading file.";
      return ( 1 );
   }
   
   // Get the clean commands
   vector< string > clean_commands;
   clean_commands = cif_file.getRawCommands ();
   
   for ( int i = 0; i < clean_commands.size (); i++ )
   {
      PrintBoxCommand ( clean_commands[ i ] );
   }

   return ( 0 );
} 

void PrintBoxCommand ( string command )
{
   istringstream input ( command );
   string piece;
   
   // Get the command type. If the command isn't a Box command, return.
   input >> piece;
   
   if ( piece != "B" )
   {
      return;
   }
   
   // Get the size and position values
   long int size_width , size_height;
   input >> size_width >> size_height;
   
   long int position_x , position_y;
   input >> position_x >> position_y;
   
   // Create default rotation (neutral rotation)
   long int rotation_x = 1 , rotation_y = 0;
   
   // Validate the next component. If is a semicolon (;),
   // the Box doesn't have rotation. If is not a semicolon, the value
   // is the X component of the rotation vector.
   input >> piece;
   
   if ( piece != ";" )
   {
      // Create other input stream to convert the X component
      istringstream component ( piece );
      component >> rotation_x;
      input >> rotation_y;
   }
   
   cout << "--- Box command ---" << endl;
   
   cout << "Size:     " << size_width << "x" << size_height << endl;
   cout << "Position: (" << position_x << "," << position_y << ")" << endl;
   cout << "Rotation: (" << rotation_x << "," << rotation_y << ")" << endl;
   
   return;
}