// "command" is the partially cleaned command (string type)
// "tmp" is a temporal variable (string type)
// "final_command" is the result of the whole process, it
//                 already has the identification character.

for ( unsigned int i = 1; i < command.size (); i++ )
{
   // Get the current character to validate.
   tmp = command[ i ];
      
   // If the character is a digit, append it directly into
   // the final command.
   if ( std::isdigit ( command[ i ] ) )
   {
      final_command += tmp;
   }
   // Validate if the current character isn't a whitespace.
   else if ( command[ i ] != ' ' )
   {
      // It isn't, so, whatever it is, validate if the final
      // command doesn't have a whitespace at its end. If it
      // doesn't have one, add one.
      if ( final_command[ final_command.size () - 1 ] != ' ' )
      {
         final_command += " ";
      }
         
      // Append the current character (it can be a minus or an
      // uppercase character.
      final_command += tmp;
         
      // If the current character is an uppercase character, add
      // a whitespace after it.
      if ( std::isupper ( command[ i ] ) )
      {
         final_command += " ";
      }
   }
   // This else-if means that the current character is a whitespace.
   // If the final command doesn't have one at its end, add one.
   else if ( final_command[ final_command.size () - 1 ] != ' ' )
   {
      final_command += " ";
   }
}