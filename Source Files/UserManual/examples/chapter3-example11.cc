std::istream& operator>> ( std::istream& input_stream ,
                           OpenCIF::Size& command )
{
   unsigned long int x , y;
   
   input_stream >> x >> y;
   command.size_height = y;
   command.size_width = x;
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream ,
                           const OpenCIF::Size& command )
{
   output_stream << command.getWidth () << " " << command.getHeight ();
   
   return ( output_stream );
}