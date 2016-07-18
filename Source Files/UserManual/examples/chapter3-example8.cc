int OpenCIF::FiniteStateMachine::operator[] ( const char& input_char )
{
   return ( fsm_current_state = fsm_states[ fsm_current_state ][ input_char ] , fsm_current_state );
}