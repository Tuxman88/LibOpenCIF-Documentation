# include <iostream>
# include <string>
# include <vector>
# include <opencif>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void PrintBoxCommand ( OpenCIF::Command* command );

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
   
   // Get the class instances
   vector< OpenCIF::Command* > command_instances;
   command_instances = cif_file.getCommands ();
   
   for ( int i = 0; i < command_instances.size (); i++ )
   {
      PrintBoxCommand ( command_instances[ i ] );
   }

   return ( 0 );
} 

void PrintBoxCommand ( OpenCIF::Command* command )
{
   // Get the command type. If the command isn't a Box command, return.
   if ( command->type () != OpenCIF::Command::Box )
   {
      return;
   }
   
   // Cast command
   OpenCIF::BoxCommand* box;
   box = (OpenCIF::BoxCommand*)command;
   
   cout << "--- Box command ---" << endl;
   
   cout << "Size:     " << box->getSize ().getWidth () << "x"
                        << box->getSize ().getHeight () << endl;
                        
   cout << "Position: (" << box->getPosition ().getX () << ","
                         << box->getPosition ().getY () << ")" << endl;
                         
   cout << "Rotation: (" << box->getRotation ().getX () << "," 
                         << box->getRotation ().getY () << ")" << endl;
   
   return;
}