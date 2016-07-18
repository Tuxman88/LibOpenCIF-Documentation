std::istream& operator>> ( std::istream& input_stream ,
                           OpenCIF::Fraction& command )
{
   unsigned long int numerator, denominator;
   
   input_stream >> numerator >> denominator;
   
   command.set ( numerator , denominator );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream ,
                           const OpenCIF::Fraction& command )
{
   output_stream << command.getNumerator () << " " << command.getDenominator ();
   
   return ( output_stream );
}