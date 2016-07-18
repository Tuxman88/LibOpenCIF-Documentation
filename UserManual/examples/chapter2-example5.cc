# include <iostream>
# include <string>
# include <opencif>

using std::cout;
using std::endl;
using std::string;

int main ()
{
   cout << "LibOpenCIF: Automatic loading example." << endl;
   
   OpenCIF::File cif_file;
   string file_path;
   
   file_path = "inv_x1.cif";
   cif_file.setPath ( file_path );
   
   OpenCIF::File::LoadStatus status;
   
   status = cif_file.loadFile ();
   
   switch ( status )
   {
      case OpenCIF::File::AllOk:
         cout << "LibOpenCIF: All ok when loading the file";
         break;
         
      case OpenCIF::File::CantOpenInputFile:
         cout << "LibOpenCIF: Can't open input file";
         break;
         
      case OpenCIF::File::IncompleteInputFile:
         cout << "LibOpenCIF: Incomplete input file (missing End command)";
         break;
         
      case OpenCIF::File::IncorrectInputFile:
         cout << "LibOpenCIF: Incorrect input file";
         break;
   }

   return ( 0 );
} 
