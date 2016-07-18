std::istream& operator >> ( std::istream& input_stream ,
                            OpenCIF::Point& point )
{
   long int x , y;
   
   input_stream >> x >> y;
   point.set ( x , y );
   
   return ( input_stream );
}

std::ostream& operator << ( std::ostream& output_stream ,
                            const OpenCIF::Point& point )
{
   output_stream << point.getX () << " " << point.getY ();
   
   return ( output_stream );
}