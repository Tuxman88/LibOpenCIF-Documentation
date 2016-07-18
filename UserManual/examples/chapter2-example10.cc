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
vector< string> TokenizeCommand ( string command );
long int StringToValue ( string to_convert );

int main ()
{
   cout << "LibOpenCIF: Another approach of using the clean commands with a basic tokenizer algorithm." << std::endl;
   
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
   vector< string > command_tokens;
   command_tokens = TokenizeCommand ( command );
   
   // Get the command type. If the command isn't a Box command, return.
   if ( command_tokens[ 0 ] != "B" )
   {
      return;
   }
   
   // Get the size and position values
   long int size_width = StringToValue ( command_tokens[ 1 ] );
   long int size_height = StringToValue ( command_tokens[ 2 ] );
   
   long int position_x = StringToValue ( command_tokens[ 3 ] );
   long int position_y = StringToValue ( command_tokens[ 4 ] );
   
   // Create default rotation (neutral rotation)
   long int rotation_x = 1 , rotation_y = 0;
   
   // Validate the amount of tokens. If not enough, there is no
   // rotation.
   if ( command_tokens.size () > 6 ) // B W H X Y ;   <-- There are 6 elements
   {
      rotation_x = StringToValue ( command_tokens[ 5 ] );
      rotation_y = StringToValue ( command_tokens[ 6 ] );
   }
   
   cout << "--- Box command ---" << endl;
   
   cout << "Size:     " << size_width << "x" << size_height << endl;
   cout << "Position: (" << position_x << "," << position_y << ")" << endl;
   cout << "Rotation: (" << rotation_x << "," << rotation_y << ")" << endl;
   
   return;
}

vector< string> TokenizeCommand ( string command )
{
   istringstream tokenizer_stream ( command );
   string token;
   vector< string > tokens;
   
   do
   {
      tokenizer_stream >> token;
      tokens.push_back ( token );
   }
   while ( token != ";" );
   
   return ( tokens );
}

long int StringToValue ( string to_convert )
{
   istringstream converter ( to_convert );
   long int value;
   converter >> value;
   
   return ( value );
}