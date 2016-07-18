# include <iostream>
# include <string>
# include <opencif>

using std::cout;
using std::endl;
using std::string;

int main ()
{
   cout << "LibOpenCIF: Manual loading example." << endl;
   
   OpenCIF::File cif_file;
   
   string file_path;
   file_path = "inv_x1.cif";
   
   cif_file.setPath ( file_path );
   
   OpenCIF::File::LoadStatus status;
   
   status = cif_file.openFile ();
   
   if ( status == OpenCIF::File::AllOk )
   {
      cout << "LibOpenCIF: All ok opening the CIF file." << endl;
   }
   else if ( status == OpenCIF::File::CantOpenInputFile )
   {
      cout << "LibOpenCIF: Can't open input file." << endl;
      
      return ( 1 );
   }
   
   status = cif_file.validateSyntax ();
   
   if ( status == OpenCIF::File::AllOk )
   {
      cout << "LibOpenCIF: CIF file valid." << endl;
   }
   else if ( status == OpenCIF::File::IncompleteInputFile )
   {
      cout << "LibOpenCIF: CIF file contents are valid, but no End command found." << endl;
   }
   else if ( status == OpenCIF::File::IncorrectInputFile )
   {
      cout << "LibOpenCIF: CIF file contents are invalid." << endl;
      
      return ( 1 );
   }
   
   cif_file.cleanCommands ();
   cout << "LibOpenCIF: CIF file commands cleaned." << endl;
   
   cif_file.convertCommands ();
   cout << "LibOpenCIF: CIF file commands converted." << endl;

   return ( 0 );
} 
