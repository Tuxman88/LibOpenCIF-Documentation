std::string OpenCIF::File::clearNumericCommand ( std::string command )
{
   std::string tmp = " ";
   std::string final_command;
            
   final_command = command[ 0 ];
   final_command += tmp;
   
   for ( unsigned int i = 0; i < command.size (); i++ )
   {
      if ( !std::isdigit ( command[ i ] ) && command[ i ] != '-' )
      {
         command[ i ] = ' ';
      }
   }
   
   std::istringstream iss ( command );
   
   while ( !iss.eof () )
   {
      iss >> tmp;
      
      if ( !iss.eof () )
      {
         final_command += tmp;
         tmp = " ";
         final_command += tmp;
      }
   }
   
   final_command += ";";
   
   return ( final_command );
}