void OpenCIF::FiniteStateMachine::add ( const int& input_state , 
                                        const std::string& input_chars , 
                                        const int& output_state )
{
   fsm_states[ input_state ].addOptions ( input_chars , output_state );
   
   return;
}