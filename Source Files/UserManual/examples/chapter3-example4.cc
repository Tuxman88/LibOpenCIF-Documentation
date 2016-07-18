// "command" is the partially cleaned command (string type)
// "final_command" is the result of the whole process, it
//                 already has the identification character.

for ( unsigned int i = 1; i < command.size (); i++ )
{
   // If the character is a digit, append it directly into
   // the final command.
   if ( std::isdigit ( command[ i ] ) )
   {
      final_command += command[ i ];
   }
   // Validate if the current character isn't a whitespace.
   else if ( command[ i ] != ' ' )
   {
      // Append the current character and also a whitespace.
      final_command += command[ i ];
      final_command += " "; 
   }
   // This else-if means that the current character is a whitespace.
   // If the final command doesn't have one at its end, add one.
   else if ( command[ i ] == ' ' && final_command[ final_command.size () - 1 ] != ' ' )
   {
      final_command += " ";
   }
}
