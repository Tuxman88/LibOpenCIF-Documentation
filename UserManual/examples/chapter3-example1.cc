std::string OpenCIF::File::cleanCommand ( std::string command )
{
   std::string final_command;
   
   switch ( command[ 0 ] )
   {
      case 'P':
      case 'B':
      case 'W':
      case 'R':
         final_command = clearNumericCommand ( command );
         break;
         
      case 'L':
         final_command = cleanLayerCommand ( command );
         break;
         
      case 'C':
         final_command = cleanCallCommand ( command );
         break;
         
      case 'D':
         final_command = cleanDefinitionCommand ( command );
         break;
         
      case 'E':
         final_command = "E ;";
         break;
         
      default:
         final_command = command.substr ( 0 , command.size () - 1 ) + " ;";
         break;
   }
   
   return ( final_command );
}