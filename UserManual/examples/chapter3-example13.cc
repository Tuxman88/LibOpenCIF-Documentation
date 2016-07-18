std::ostream& operator<< ( std::ostream& output_stream , 
                           const OpenCIF::Transformation& transformation )
{
   switch ( transformation.getType () )
   {
      case OpenCIF::Transformation::Displacement:
         output_stream << "T ";
         output_stream << transformation.getDisplacement ();
         break;
         
      case OpenCIF::Transformation::Rotation:
         output_stream << "R ";
         output_stream << transformation.getRotation ();
         break;
         
      case OpenCIF::Transformation::VerticalMirroring:
         output_stream << "M Y";
         break;
         
      case OpenCIF::Transformation::HorizontalMirroring:
         output_stream << "M X";
         break;
   }
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , 
                           OpenCIF::Transformation& transformation )
{
   std::string type;
   OpenCIF::Point point;
   
   input_stream >> type;
   
   switch ( type[ 0 ] )
   {
      case 'T':
         input_stream >> point;
         transformation.setDisplacement ( point );
         transformation.setType ( OpenCIF::Transformation::Displacement );
         break;
         
      case 'R':
         input_stream >> point;
         transformation.setRotation ( point );
         transformation.setType ( OpenCIF::Transformation::Rotation );
         break;
         
      case 'M':
         input_stream >> type;
         transformation.setType ( ( type == "X" ) 
                                  ? OpenCIF::Transformation::HorizontalMirroring 
                                  : OpenCIF::Transformation::VerticalMirroring );
         break;
   }
   
   return ( input_stream );
}