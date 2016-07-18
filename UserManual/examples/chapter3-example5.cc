void OpenCIF::State::addOptions ( const std::string& new_options ,
                                  const int& exit_state )
{
   for ( unsigned int i = 0; i < new_options.size (); i++ )
   {
      state_options[ (int)(new_options[ i ]) ] = exit_state;
   }
   
   return;
}