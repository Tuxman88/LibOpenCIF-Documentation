/*
 * LibOpenCIF, a library to read the contents of a CIF (Caltech Intermediate
 * Form) file. The library also includes a finite state machine to validate
 * the contents, acording to the specifications found in the technical
 * report 2686, from february 11, 1980.
 * 
 * Copyright (C) 2014, Moises Chavez Martinez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// If you need to change the include path, modify the next line according to your needs.
# include "libopencif.hh" 

// To search over the contents of individual files, search for the word "FILE:"

// FILE: command.cc


/*
 * This constructor initialice the "command_type" attribute.
 */
OpenCIF::Command::Command ( void )
{
   command_type = PlainCommand;
}

/*
 * Nothing to do.
 */
OpenCIF::Command::~Command ( void )
{
}

/*
 * This member function return the type of the current command type.
 */
OpenCIF::Command::CommandType OpenCIF::Command::type ( void )
{
   return ( command_type );
}

/*
 * This member function converts a string into a long int value.
 */
long int OpenCIF::Command::toLInt ( const std::string& value )
{
   long int converted;
   std::istringstream iss ( value );
   iss >> converted;
   
   return ( converted );
}

/*
 * This member function converts a string into a unsigned long int value.
 */
unsigned long int OpenCIF::Command::toULInt ( const std::string& value )
{
   unsigned long int converted;
   std::istringstream iss ( value );
   iss >> converted;
   
   return ( converted );
}

void OpenCIF::Command::print ( std::ostream& output_stream )
{
   output_stream << "(OpenCIF:Command:print: Logical error. This function should not be used (maybe the user has instantiated a Command, instread of a leaf class)) ;";
   
   return;
}

void OpenCIF::Command::read ( std::istream& input_stream )
{
   // Dummy call to prevent a warning when compiling about input_stream not being used.
   input_stream.gcount ();
   
   return;
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::Command* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::Command* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

// FILE: primitivecommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::PrimitiveCommand::PrimitiveCommand ( void )
   : Command ()
{
   command_type = Primitive;
}

/*
 * Destructor.
 */
OpenCIF::PrimitiveCommand::~PrimitiveCommand ( void )
{
}

// FILE: point.cc


/*
 * Default constructor. Initialices the point with a 0,0 value.
 */
OpenCIF::Point::Point ( void )
{
   set ( 0 , 0 );
}

/*
 * Specialized constructor. Initialices a point with the values specified.
 */
OpenCIF::Point::Point ( const long int& new_x , const long int& new_y )
{
   set ( new_x , new_y );
}

/*
 * Nothing to do.
 */
OpenCIF::Point::~Point ( void )
{
}

/*
 * Returns the X position value of the actual point.
 */
long int OpenCIF::Point::getX ( void ) const
{
   return ( point_x );
}

/*
 * Returns the Y position value of the actual point.
 */
long int OpenCIF::Point::getY ( void ) const
{
   return ( point_y );
}

/*
 * This member function let the user to set a point in a single call.
 * The first argument is the X position value, the second is the Y position value.
 * Internally are called the member functions to set X and Y, indpendently. This
 * behavior is intended in case of adding some kind of checking for the values.
 */
void OpenCIF::Point::set ( const long int& new_x , const long int& new_y )
{
   setX ( new_x );
   setY ( new_y );
   
   return;
}

/*
 * This member functions receives the X position value and sets it to
 * the attribute "point_x".
 */
void OpenCIF::Point::setX ( const long int& new_x )
{
   point_x = new_x;
   
   return;
}

/*
 * This member functions receives the Y position value and sets it to
 * the attribute "point_y".
 */
void OpenCIF::Point::setY ( const long int& new_y )
{
   point_y = new_y;
   
   return;
}

/*
 * This function helps to load a point from an input stream.
 */
std::istream& operator >> ( std::istream& input_stream , OpenCIF::Point& point )
{
   long int x , y;
   
   input_stream >> x >> y;
   point.set ( x , y );
   
   return ( input_stream );
}

std::ostream& operator << ( std::ostream& output_stream , const OpenCIF::Point& point )
{
   output_stream << point.getX () << " " << point.getY ();
   
   return ( output_stream );
}

// FILE: pathbasedcommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::PathBasedCommand::PathBasedCommand ( void )
   : PrimitiveCommand ()
{
   command_type = PathBased;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::PathBasedCommand::~PathBasedCommand ( void )
{
}

/*
 * This member function returns the points stored in the command.
 */
std::vector< OpenCIF::Point > OpenCIF::PathBasedCommand::getPoints ( void ) const
{
   return ( command_points );
}

/*
 * This member function help to set the points for this command.
 */
void OpenCIF::PathBasedCommand::setPoints ( const std::vector< OpenCIF::Point >& new_points )
{
   command_points = new_points;
   
   return;
}

// FILE: polygoncommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::PolygonCommand::PolygonCommand ( void )
   : PathBasedCommand ()
{
   command_type = Polygon;
}

OpenCIF::PolygonCommand::PolygonCommand ( const std::string& str_command )
   : PathBasedCommand ()
{
   command_type = Polygon;
   
   std::istringstream input_stream ( str_command );
   std::string word;
   
   input_stream >> word >> word;
   
   while ( word != ";" )
   {
      std::istringstream iss ( word );
      long int x , y;
      
      iss >> x;
      input_stream >> y;
      OpenCIF::Point point ( x , y );
      
      command_points.push_back ( point );
      
      input_stream >> word;
   }
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::PolygonCommand::~PolygonCommand ( void )
{
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::PolygonCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::PolygonCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::PolygonCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::PolygonCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::PolygonCommand::print ( std::ostream& output_stream )
{
   output_stream << "P ";
   
   for ( unsigned long int i = 0; i < getPoints ().size (); i++ )
   {
      output_stream << getPoints ()[ i ] << " ";
   }
   
   output_stream << ";";
   
   return;
}

void OpenCIF::PolygonCommand::read ( std::istream& input_stream )
{
   std::string word;
   
   input_stream >> word >> word;
   
   while ( word != ";" )
   {
      std::istringstream iss ( word );
      long int x , y;
      
      iss >> x;
      input_stream >> y;
      OpenCIF::Point point ( x , y );
      
      command_points.push_back ( point );
      
      input_stream >> word;
   }
   
   return;
}

// FILE: wirecommand.cc


/*
 * Default constructor. Initialize command. The wire must have a size not equal to 0.
 */
OpenCIF::WireCommand::WireCommand ( void )
   : PathBasedCommand ()
{
   command_type = Wire;
   wire_width = 1;
}

/*
 * Non-Default constructor. Initialize the command instance using a string representing the command itself.
 */
OpenCIF::WireCommand::WireCommand ( const std::string& str_command )
   : PathBasedCommand ()
{
   command_type = Wire;
   
   std::string word;
   std::istringstream input_stream ( str_command );
   unsigned long int width;
   
   // Read the W and ID parts
   input_stream >> word >> width;
   
   setWidth ( width );
   
   input_stream >> word;
   
   while ( word != ";" )
   {
      std::istringstream iss ( word );
      long int x , y;
      iss >> x;
      input_stream >> y;
      
      OpenCIF::Point point ( x , y );
      
      command_points.push_back ( point );
      
      input_stream >> word;
   }
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::WireCommand::~WireCommand ( void )
{
}

/*
 * Member function to return the width of the wire.
 */
long unsigned int OpenCIF::WireCommand::getWidth ( void ) const
{
   return ( wire_width );
}

/*
 * Member function to set the width of the command.
 */
void OpenCIF::WireCommand::setWidth ( const long unsigned int& new_width )
{
   wire_width = new_width;
   
   return;
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::WireCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::WireCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::WireCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::WireCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::WireCommand::print ( std::ostream& output_stream )
{
   output_stream << "W " << wire_width << " ";
   
   for ( unsigned long int i = 0; i < command_points.size (); i++ )
   {
      output_stream << command_points.at ( i ) << " ";
   }
   
   output_stream << ";";
   
   return;
}

void OpenCIF::WireCommand::read ( std::istream& input_stream )
{
   std::string word;
   unsigned long int width;
   
   // Read the W and ID parts
   input_stream >> word >> width;
   
   setWidth ( width );
   
   input_stream >> word;
   
   while ( word != ";" )
   {
      std::istringstream iss ( word );
      long int x , y;
      iss >> x;
      input_stream >> y;
      
      OpenCIF::Point point ( x , y );
      
      command_points.push_back ( point );
      
      input_stream >> word;
   }
   
   return;
}

// FILE: positionbasedcommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::PositionBasedCommand::PositionBasedCommand ( void )
   : PrimitiveCommand ()
{
   command_type = PositionBased;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::PositionBasedCommand::~PositionBasedCommand ( void )
{
}

/*
 * Member function to return the current center of the figure.
 */
OpenCIF::Point OpenCIF::PositionBasedCommand::getPosition ( void ) const
{
   return ( command_position );
}

/*
 * Member function to set the center point of the figure.
 */
void OpenCIF::PositionBasedCommand::setPosition ( const OpenCIF::Point& new_position )
{
   command_position = new_position;
   
   return;
}

// FILE: size.cc


/*
 * Default constructor. Initialize the values of the size to a non-zero value.
 */
OpenCIF::Size::Size ( void )
{
   size_height = 1;
   size_width = 1;
}

/*
 * Non-Default constructor. Initialize the values of the size.
 */
OpenCIF::Size::Size ( const unsigned long int& new_width , const unsigned long int& new_height )
{
   set ( new_width , new_height );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::Size::~Size ( void )
{
}

/*
 * Member function to return the height of the size.
 */
long unsigned int OpenCIF::Size::getHeight ( void ) const
{
   return ( size_height );
}

/*
 * Member function to return the width of the size.
 */
long unsigned int OpenCIF::Size::getWidth ( void ) const
{
   return ( size_width );
}

/*
 * Member function to set both dimensions of the size at the same time.
 */
void OpenCIF::Size::set ( const long unsigned int& new_width , const long unsigned int& new_height )
{
   setWidth ( new_width );
   setHeight ( new_height );
   
   return;
}

/*
 * Member function to set the height of the size.
 */
void OpenCIF::Size::setHeight ( const long unsigned int& new_height )
{
   size_height = new_height;
   
   return;
}

/*
 * Member function to set the width of the size.
 */
void OpenCIF::Size::setWidth ( const long unsigned int& new_width )
{
   size_width = new_width;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::Size& command )
{
   unsigned long int x , y;
   
   input_stream >> x >> y;
   command.size_height = y;
   command.size_width = x;
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Size& command )
{
   output_stream << command.getWidth () << " " << command.getHeight ();
   
   return ( output_stream );
}

// FILE: boxcommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::BoxCommand::BoxCommand ( void )
   : PositionBasedCommand ()
{
   command_type = Box;
   box_rotation.set ( 1 , 0 ); // Neutral rotation
}

/*
 * Non-default constructor. Initialize the instance using a string that contains the command itself.
 */
OpenCIF::BoxCommand::BoxCommand ( const std::string& str_command )
   : PositionBasedCommand ()
{
   command_type = Box;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::BoxCommand::~BoxCommand ( void )
{
}

/*
 * Member function to return the rotation point.
 */
OpenCIF::Point OpenCIF::BoxCommand::getRotation ( void ) const
{
   return ( box_rotation );
}

/*
 * Member function to return the size.
 */
OpenCIF::Size OpenCIF::BoxCommand::getSize ( void ) const
{
   return ( box_size );
}

/*
 * Member function to set the rotation point.
 */
void OpenCIF::BoxCommand::setRotation ( const OpenCIF::Point& new_rotation )
{
   box_rotation = new_rotation;
   
   return;
}

/*
 * Member function to set the size.
 */
void OpenCIF::BoxCommand::setSize ( const OpenCIF::Size& new_size )
{
   box_size = new_size;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::BoxCommand::print ( std::ostream& output_stream )
{
   output_stream << "B " << getSize () << " " << getPosition () << " " << getRotation () << " ;";
   
   return;
}

void OpenCIF::BoxCommand::read ( std::istream& input_stream )
{
   std::string word;
   OpenCIF::Point position;
   OpenCIF::Size size;
   long int x , y;
   
   
   // Read the B part, then, the size, then the position.
   input_stream >> word >> size >> position;
   
   // Check if there is a rotation
   input_stream >> word;
   
   if ( word != ";" )
   {
      std::istringstream iss ( word );
      iss >> x;
      input_stream >> y;
      
      OpenCIF::Point rotation ( x , y );
      
      setRotation ( rotation );
   }
   else
   {
      OpenCIF::Point rotation ( 1 , 0 );
      
      setRotation ( rotation );
   }
   
   setPosition ( position );
   setSize ( size );
   
   return;
}

// FILE: roundflashcommand.cc


/*
 * Default constructor. Initialize the diameter to a non-zero value.
 */
OpenCIF::RoundFlashCommand::RoundFlashCommand ( void )
   : PositionBasedCommand ()
{
   command_type = RoundFlash;
   setDiameter ( 1 );
}

/*
 * Non-Default constructor. Initialize the command from a string that represents the command itself.
 */
OpenCIF::RoundFlashCommand::RoundFlashCommand ( const std::string& str_command )
   : PositionBasedCommand ()
{
   command_type = RoundFlash;
   
   std::istringstream input_stream ( str_command );
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::RoundFlashCommand::~RoundFlashCommand ( void )
{
}

/*
 * Member function to return the actual diameter of the command.
 */
long unsigned int OpenCIF::RoundFlashCommand::getDiameter ( void ) const
{
   return ( round_diameter );
}

/*
 * Member function to set the command diameter.
 */
void OpenCIF::RoundFlashCommand::setDiameter ( const long unsigned int& new_diameter )
{
   round_diameter = new_diameter;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::RoundFlashCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::RoundFlashCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::RoundFlashCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::RoundFlashCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::RoundFlashCommand::print ( std::ostream& output_stream )
{
   output_stream << "R " << getDiameter () << " " << getPosition () << " ;";
   
   return;
}

void OpenCIF::RoundFlashCommand::read ( std::istream& input_stream )
{
   unsigned long int diameter;
   std::string word;
   OpenCIF::Point point;
   
   input_stream >> word >> diameter >> point;
   
   setDiameter ( diameter );
   setPosition ( point );
   
   return;
}

// FILE: controlcommand.cc

/*
 * Default constuctor. Initialices the command ID with a value
 * of 1 and sets the needed Command Type.
 */
OpenCIF::ControlCommand::ControlCommand ( void )
   : Command ()
{
   command_id = 1;
   command_type = Control;
}

/*
 * Nothing to do.
 */
OpenCIF::ControlCommand::~ControlCommand ( void )
{
}

/*
 * Returns the ID of the command. For example, in a definition start
 * command, this returns the ID of the definition to create. In a call
 * command, this returns the ID of the definition to call.
 */
long unsigned int OpenCIF::ControlCommand::getID ( void ) const
{
   return ( command_id );
}

/*
 * Member function to set the ID of the definition specified. If the
 * command is a DefinitionStart, the ID will be the ID of the definition
 * to create. If the command is a Call, the ID will be the ID  of the
 * definition to call.
 */
void OpenCIF::ControlCommand::setID ( const long unsigned int& new_id )
{
   command_id = new_id;
   
   return;
}

// FILE: fraction.cc


/*
 * Default constructor. Sets the default values of 1/1 (a neutral fraction).
 */
OpenCIF::Fraction::Fraction ( void )
{
   set ( 1 , 1 );
}

/*
 * Non-Default constructor.
 */
OpenCIF::Fraction::Fraction ( const unsigned long int& new_numerator , const unsigned long int& new_denominator )
{
   set ( new_numerator , new_denominator );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::Fraction::~Fraction(void)
{
}

/*
 * This member function returns the denominator of the fraction.
 */
unsigned long int OpenCIF::Fraction::getDenominator ( void ) const
{
   return ( fraction_denominator );
}

/*
 * This member function returns the numerator of the fraction.
 */
unsigned long int OpenCIF::Fraction::getNumerator ( void ) const
{
   return ( fraction_numerator );
}

/*
 * This member function sets the denominator of the fraction
 */
void OpenCIF::Fraction::setDenominator ( const unsigned long int& new_denominator )
{
   fraction_denominator = new_denominator;
   
   return;
}

/*
 * This member function sets the numerator of the fraction.
 */
void OpenCIF::Fraction::setNumerator ( const unsigned long int& new_numerator )
{
   fraction_numerator = new_numerator;
   
   return;
}

/*
 * This member functions helps to set the whole value of the fraction in a single call.
 */
void OpenCIF::Fraction::set ( const long unsigned int& new_numerator , const long unsigned int& new_denominator )
{
   setNumerator ( new_numerator );
   setDenominator ( new_denominator );
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::Fraction& command )
{
   unsigned long int numerator, denominator;
   
   input_stream >> numerator >> denominator;
   
   command.set ( numerator , denominator );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Fraction& command )
{
   output_stream << command.getNumerator () << " " << command.getDenominator ();
   
   return ( output_stream );
}

// FILE: definitionstartcommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::DefinitionStartCommand::DefinitionStartCommand ( void )
   : ControlCommand ()
{
   command_type = DefinitionStart;
}

OpenCIF::DefinitionStartCommand::DefinitionStartCommand ( const std::string& str_command )
   : ControlCommand ()
{
   command_type = DefinitionStart;
   
   std::istringstream input_stream ( str_command );
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::DefinitionStartCommand::~DefinitionStartCommand ( void )
{
}

/*
 * This member function returns the AB value of this command.
 */
OpenCIF::Fraction OpenCIF::DefinitionStartCommand::getAB ( void ) const
{
   return ( command_ab );
}

/*
 * This member function sets the AB value of the command.
 */
void OpenCIF::DefinitionStartCommand::setAB ( const OpenCIF::Fraction& new_ab )
{
   command_ab = new_ab;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionStartCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionStartCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionStartCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionStartCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::DefinitionStartCommand::print ( std::ostream& output_stream )
{
   output_stream << "D S " << getID () << " " << getAB () << " ;";
   
   return;
}

void OpenCIF::DefinitionStartCommand::read ( std::istream& input_stream )
{
   // Read the first two useless parts and the ID
   std::string word;
   unsigned long int id;
   
   input_stream >> word >> word >> id;
   
   setID ( id );
   
   // Read the next components. If is a semicolon, do nothing. Otherwise, is an AB value
   input_stream >> word;
   
   if ( word != ";" )
   {
      std::istringstream iss ( word );
      unsigned long int a , b;
      iss >> a;
      input_stream >> b;
      
      OpenCIF::Fraction fraction;
      fraction.set ( a , b );
      
      setAB ( fraction );
   }
   
   return;
}

// FILE: definitiondeletecommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::DefinitionDeleteCommand::DefinitionDeleteCommand ( void )
   : ControlCommand ()
{
   command_type = DefinitionDelete;
}

/*
 * Non-default constructor. Initialice the command based on a string version of itself.
 */
OpenCIF::DefinitionDeleteCommand::DefinitionDeleteCommand ( const std::string& str_command ) 
   : ControlCommand ()
{
   command_type = DefinitionDelete;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Default constructor.
 */
OpenCIF::DefinitionDeleteCommand::~DefinitionDeleteCommand ( void )
{
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::DefinitionDeleteCommand::print ( std::ostream& output_stream )
{
   output_stream << "D D " << getID () << " ;";
   
   return;
}

void OpenCIF::DefinitionDeleteCommand::read ( std::istream& input_stream )
{
   // Load the "D D " part to read, after that, the ID
   std::string word;
   unsigned long int id;
   
   input_stream >> word >> word >> id;
   
   setID ( id );
   
   return;
}

// FILE: transformation.cc


/*
 * Constructor. Initialices the instance as a Displacement transformation,
 * with a displacement value of 0,0 (neutral movement).
 */
OpenCIF::Transformation::Transformation ( void )
{
   transformation_point.set ( 0 , 0 );
   setType ( Displacement );
}

/*
 * Nothing to do.
 */
OpenCIF::Transformation::~Transformation ( void )
{
}

/*
 * This member function returns the point stored in the instance. The point is the same
 * for the displacements and rotations, so, since the transformation can only be one or
 * another (but not both at the same time), there is only one point.
 */
OpenCIF::Point OpenCIF::Transformation::getDisplacement ( void ) const
{
   return ( transformation_point );
}

/*
 * This member function returns the point stored in the instance. The point is the same
 * for the displacements and rotations, so, since the transformation can only be one or
 * another (but not both at the same time), there is only one point.
 */
OpenCIF::Point OpenCIF::Transformation::getRotation ( void ) const
{
   return ( transformation_point );
}

/*
 * This member function returns the type of the current instance.
 */
OpenCIF::Transformation::TransformationType OpenCIF::Transformation::getType ( void ) const
{
   return ( transformation_type );
}

/*
 * This member function accepts a new point. Such point represents the displacement
 * to perform.
 */
void OpenCIF::Transformation::setDisplacement ( const OpenCIF::Point& new_displacement )
{
   transformation_point = new_displacement;
   
   return;
}

/*
 * This member function accepts a new point. Such point represents the rotation to
 * perform.
 */
void OpenCIF::Transformation::setRotation ( const OpenCIF::Point& new_rotation )
{
   transformation_point = new_rotation;
   
   return;
}

/*
 * This member function sets the type of the transformation.
 */
void OpenCIF::Transformation::setType ( const OpenCIF::Transformation::TransformationType& new_type )
{
   transformation_type = new_type;
   
   return;
}

/*
 * This overloaded operator writes a transformation instance into an output stream.
 */
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Transformation& transformation )
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

/*
 * This overloaded operator loads a transformation instance from an input stream.
 */
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Transformation& transformation )
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
         transformation.setType ( ( type == "X" ) ? OpenCIF::Transformation::HorizontalMirroring : OpenCIF::Transformation::VerticalMirroring );
         break;
   }
   
   return ( input_stream );
}

// FILE: callcommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::CallCommand::CallCommand ( void )
   : ControlCommand ()
{
   command_type = Call;
}

/*
 * Specialized constructor. Takes as argument a command in string form.
 * The commas must be clean. That means that, a command like this:
 * 
 *      C100muajajajaja,R100,-100T100,900MXMY;
 * 
 * Is correct, but is not supported. The correct format must be this:
 * 
 *      C 100 R 100 -100 T 100 900 M X M Y ;
 * 
 * That is neccesary since the command will used as the input of an
 * input stream, and the components will be loaded as individual strings.
 * 
 * Take in consideraton the previous indication, since the constructor
 * DONESN'T CHECK the command format.
 */
OpenCIF::CallCommand::CallCommand ( const std::string& str_command )
   : ControlCommand ()
{
   command_type = Call;
   
   std::istringstream input_stream ( str_command );
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::CallCommand::~CallCommand ( void )
{
}

/*
 * This member function returns a copy of the vector with the transformations.
 */
std::vector< OpenCIF::Transformation >& OpenCIF::CallCommand::getTransformations ( void )
{
   return ( call_transformations );
}

/*
 * This member function adds a single transformation to the transformation vector.
 */
void OpenCIF::CallCommand::addTransformation ( const OpenCIF::Transformation& new_transformation )
{
   call_transformations.push_back ( new_transformation );
   
   return;
}

/*
 * This member functions receives a new vector of transformations, and stores it.
 */
void OpenCIF::CallCommand::setTransformations ( const std::vector< OpenCIF::Transformation >& new_transformations )
{
   call_transformations.clear ();
   call_transformations = new_transformations;
   
   return;
}

/*
 * This overloaded operator helps to write a call command to a output stream.
 */
std::ostream& operator << ( std::ostream& output_stream , OpenCIF::CallCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

/*
 * This overloaed operator helps to read a call command from an input stream.
 */
std::istream& operator >> ( std::istream& input_stream , OpenCIF::CallCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

/*
 * This overloaded operator helps to write a call command to a output stream.
 */
std::ostream& operator << ( std::ostream& output_stream , OpenCIF::CallCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

/*
 * This overloaed operator helps to read a call command from an input stream.
 */
std::istream& operator >> ( std::istream& input_stream , OpenCIF::CallCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::CallCommand::print ( std::ostream& output_stream )
{
   output_stream << "C "; // Start of the command
   output_stream << getID () << " "; // ID of the call command.
   
   for ( unsigned int i = 0; i < call_transformations.size (); i++ )
   {
      output_stream << call_transformations.at ( i ) << " ";
   }
   
   output_stream << ";";
   
   return;
}

void OpenCIF::CallCommand::read ( std::istream& input_stream )
{
   std::string word;
   unsigned long int value;
   
   // Extract the "C", and then the ID
   
   input_stream >> word >> value;
   
   setID ( value );
   
   // Extract next part. It can be a semicolon (end of all) or transformations
   input_stream >> word;
   
   while ( word != ";" )
   {
      OpenCIF::Transformation new_transformation;
      
      if ( word == "R" )
      {
         OpenCIF::Point point;
         input_stream >> point;
         new_transformation.setType ( OpenCIF::Transformation::Rotation );
         new_transformation.setRotation ( point );
      }
      else if ( word == "T" )
      {
         OpenCIF::Point point;
         input_stream >> point;
         new_transformation.setType ( OpenCIF::Transformation::Displacement );
         new_transformation.setDisplacement ( point );
      }
      else
      {
         // Mirroring
         input_stream >> word;
         new_transformation.setType ( ( word == "X" ) ? OpenCIF::Transformation::HorizontalMirroring : OpenCIF::Transformation::VerticalMirroring );
      }
      
      addTransformation ( new_transformation );
      input_stream >> word;
   }
   
   return;
}

// FILE: definitionendcommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::DefinitionEndCommand::DefinitionEndCommand ( void )
   : ControlCommand ()
{
   command_type = DefinitionEnd;
}

/*
 * Non-Default constructor. Nothing to do.
 */
OpenCIF::DefinitionEndCommand::DefinitionEndCommand ( const std::string& str_command )
   : ControlCommand ()
{
   command_type = DefinitionEnd;
   str_command.size ();
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::DefinitionEndCommand::~DefinitionEndCommand ( void )
{
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionEndCommand& command )
{   
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionEndCommand& command )
{
   // Dummy call to prevent compilation warnings about command not being used
   if ( (&command) == 0 )
   {
      return ( input_stream );
   }
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionEndCommand* command )
{   
   command->print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionEndCommand* command )
{
   // Dummy call to prevent compilation warnings about command not being used
   if ( command == 0 )
   {
      return ( input_stream );
   }
   
   return ( input_stream );
}

void OpenCIF::DefinitionEndCommand::print ( std::ostream& output_stream )
{
   output_stream << "D F ;";
   
   // Since the command is not needed... well... do nothing...
   
   return;
}

void OpenCIF::DefinitionEndCommand::read ( std::istream& input_stream )
{
   input_stream.gcount ();
   
   return;
}

// FILE: endcommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::EndCommand::EndCommand ( void )
   : ControlCommand ()
{
   command_type = End;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::EndCommand::~EndCommand ( void )
{
}

unsigned long int OpenCIF::EndCommand::getID ( void ) const
{
   return ( ControlCommand::getID () );
}

void OpenCIF::EndCommand::setID ( const unsigned long int& new_id )
{
   ControlCommand::setID ( new_id );
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::EndCommand& command )
{
   // Dummy call to prevent warnings about command not being used
   command.getID ();
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::EndCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::EndCommand* command )
{
   // Dummy call to prevent warnings about command not being used
   command->getID ();
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::EndCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::EndCommand::print ( std::ostream& output_stream )
{
   output_stream << "E ;";
   
   return;
}

void OpenCIF::EndCommand::read ( std::istream& input_stream )
{
   // Dummy call to prevent warnings about input_stream not being used
   input_stream.gcount ();
   
   return;
}

// FILE: rawcontentcommand.cc


/*
 * Default contructor. Nothing to do.
 */
OpenCIF::RawContentCommand::RawContentCommand ( void )
   : Command ()
{
   command_type = RawContent;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::RawContentCommand::~RawContentCommand ( void  )
{
}

/*
 * This member function returns the contents of the command.
 */
std::string OpenCIF::RawContentCommand::getContent ( void ) const
{
   return ( command_content );
}

/*
 * This membet function helps to set the command contents.
 */
void OpenCIF::RawContentCommand::setContent ( const std::string& new_contents )
{
   command_content = new_contents;
   
   return;
}

// FILE: userextensioncommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::UserExtensionCommand::UserExtensionCommand ( void )
   : RawContentCommand ()
{
   command_type = UserExtension;
}

OpenCIF::UserExtensionCommand::UserExtensionCommand ( const std::string& str_command )
   : RawContentCommand ()
{
   command_type = UserExtension;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::UserExtensionCommand::~UserExtensionCommand ( void )
{
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::UserExtensionCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::UserExtensionCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::UserExtensionCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::UserExtensionCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::UserExtensionCommand::print ( std::ostream& output_stream )
{
   output_stream << getContent () << " ;";
   
   return;
}

void OpenCIF::UserExtensionCommand::read ( std::istream& input_stream )
{
   char character = ' ';
   std::string contents;
   
   while ( character == ' ' )
   {
      character = input_stream.get ();
   }
   
   contents = character;
   
   while ( character != ';' )
   {
      character = input_stream.get ();
      
      if ( character != ';' )
      {
         contents += character;
      }
   }
   
   while ( contents[ contents.size () - 1 ] == ' ' )
   {
      contents.erase ( contents.size () - 1 , 1 );
   }
   
   setContent ( contents );
   
   return;
}

// FILE: commentcommand.cc


/*
 * Default contructor. Nothing to do.
 */
OpenCIF::CommentCommand::CommentCommand ( void )
   : RawContentCommand ()
{
   command_type = Comment;
}

OpenCIF::CommentCommand::CommentCommand ( const std::string& str_command )
   : RawContentCommand ()
{
   command_type = Comment;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::CommentCommand::~CommentCommand ( void )
{
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::CommentCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CommentCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::CommentCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CommentCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::CommentCommand::print ( std::ostream& output_stream )
{
   output_stream << getContent () << " ;";
   
   return;
}

void OpenCIF::CommentCommand::read ( std::istream& input_stream )
{
   // Read chars until the parentheses end and I read the semicolon.
   
   char character = '_';
   std::string content;
   
   while ( character != '(' )
   {
      character = input_stream.get ();
   }
   
   content = "(";
   
   unsigned long int parentheses = 1;
   
   while ( parentheses != 0 )
   {
      character = input_stream.get ();
      content += character;
      
      parentheses += ( character == '(' ) ? 1 : ( character == ')' ) ? -1 : 0;
   }
   
   // Ok, I have the last parentheses. Read and omit unti the semicolon
   
   while ( character != ';' )
   {
      character = input_stream.get ();
   }
   
   setContent ( content );
   
   return;
}

// FILE: layercommand.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::LayerCommand::LayerCommand ( void )
   : Command ()
{
   command_type = Layer;
}

OpenCIF::LayerCommand::LayerCommand ( const std::string& str_command )
   : Command ()
{
   command_type = Layer;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::LayerCommand::~LayerCommand ( void )
{
}

/*
 * Member function that returns the name of the layer.
 */
std::string OpenCIF::LayerCommand::getName ( void ) const
{
   return ( layer_name );
}

/*
 * Member function to set the name of the layer.
 */
void OpenCIF::LayerCommand::setName ( const std::string& new_name )
{
   layer_name = new_name;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::LayerCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::LayerCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::LayerCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::LayerCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::LayerCommand::print ( std::ostream& output_stream )
{
   output_stream << "L " << getName () << " ;";
   
   return;
}

void OpenCIF::LayerCommand::read ( std::istream& input_stream )
{
   std::string word;
   
   // Read the "L" section of the command and the layer name
   input_stream >> word >> word;
   
   setName ( word );
   
   return;
}

// FILE: state.cc


/*
 * Default constructor. Initialice the vector of states.
 */
OpenCIF::State::State ( void )
{
   reset ();
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::State::~State ( void )
{
}

/*
 * Member function to reset the transitions.
 */
void OpenCIF::State::reset ( void )
{
   for ( int i = 0; i < 256; i++ )
   {
      state_options[ i ] = -1;
   }
   
   return;
}

/*
 * Member function to add transitions based in some strings, to some state.
 */
void OpenCIF::State::addOptions ( const std::string& new_options , const int& exit_state )
{
   for ( unsigned int i = 0; i < new_options.size (); i++ )
   {
      state_options[ (int)(new_options[ i ]) ] = exit_state;
   }
   
   return;
}

/*
 * Overloaded operator to access the transition based on the input char.
 */
int OpenCIF::State::operator[] ( const char& input_char )
{
   return ( state_options[ (int)input_char ] );
}

// FILE: finitestatemachine.cc


/*
 * Constructor. Initialice the FSM.
 */
OpenCIF::FiniteStateMachine::FiniteStateMachine ( const int& state_amount )
{
   for ( int i = 0; i < ( state_amount + 1 ); i++ )
   {
      OpenCIF::State state;
      fsm_states.push_back ( state );
   }
   
   fsm_current_state = 1;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::FiniteStateMachine::~FiniteStateMachine ( void )
{
}

/*
 * Member function to return the current state of the FSM.
 */
int OpenCIF::FiniteStateMachine::currentState ( void ) const
{
   return ( fsm_current_state );
}

/*
 * Member function to add a new state transition.
 */
void OpenCIF::FiniteStateMachine::add ( const int& input_state , const std::string& input_chars , const int& output_state )
{
   fsm_states[ input_state ].addOptions ( input_chars , output_state );
   
   return;
}

/*
 * Member function to get the new state of the FSM based in an input char.
 */
int OpenCIF::FiniteStateMachine::operator[] ( const char& input_char )
{
   return ( fsm_current_state = fsm_states[ fsm_current_state ][ input_char ] , fsm_current_state );
}

/*
 * Member function to reset the FSM.
 */
void OpenCIF::FiniteStateMachine::reset ( void )
{
   fsm_current_state = 1;
   
   return;
}

// FILE: ciffsm.cc


/*
 * Default contructor. This constructor prepares the FSM to have enough
 * states (constructor of the father class). After setting such things,
 * the constructor adds enough transitions to represent a valid FSM to
 * validate the contents of a CIF file.
 * 
 * Refer to the documentation to see a visual representation of the FSM.
 */
OpenCIF::CIFFSM::CIFFSM ( void )
   : FiniteStateMachine ( 92 ) ,// The finite state machine designed requires such amount of states to validate the contents of the CIF file.
     parentheses ( 0 )
{
   /*
    * The process to add states will be this:
    * 
    * For every state, there will be added every transition from such state.
    * After that, there will be added a new state.
    * 
    * To this point, thanks to the constructor of the father class,
    * the FSM is ready to be configured (there is enough transitions and states).
    * 
    * By default, every "jump" (transition) not configured is an invalid transition.
    * 
    * There are defined some strings and constants to ease the process of coding the transitions.
    * For example, there is a KeyValue named "LayerNameChar", that represents a digit (0 to 9) or
    * and upper char (A to Z).
    */
   
   add ( 1 , BlankChar , 1 );
   add ( 1 , "P" , 2 );
   add ( 1 , "B" , 14 );
   add ( 1 , "R" , 31 );
   add ( 1 , "W" , 40 );
   add ( 1 , "L" , 54 );
   add ( 1 , "D" , 57 );
   add ( 1 , "C" , 70 );
   add ( 1 , Digit , 88 );
   add ( 1 , "(" , 89 );
   add ( 1 , "E" , 91 );
   
   /*
    * POLYGON STATES
    */
   
   add ( 2 , BlankChar , 2 );
   add ( 2 , "-" , 3 );
   add ( 2 , Digit , 4 );
   
   add ( 3 , Digit , 4 );
   
   add ( 4 , Digit , 4 );
   add ( 4 , SeparatorChar , 5 );
   
   add ( 5 , SeparatorChar , 5 );
   add ( 5 , "-" , 6 );
   add ( 5 , Digit , 7 );
   
   add ( 6 , Digit , 7 );
   
   add ( 7 , Digit , 7 );
   add ( 7 , SeparatorChar , 8 );
   add ( 7 , ";" , 1 );
   
   add ( 8 , SeparatorChar , 8 );
   add ( 8 , "-" , 9 );
   add ( 8 , Digit , 10 );
   add ( 8 , ";" , 1 );
   
   add ( 9 , Digit , 10 );
   
   add ( 10 , Digit , 10 );
   add ( 10 , SeparatorChar , 11 );
   
   add ( 11 , SeparatorChar , 11 );
   add ( 11 , "-" , 12 );
   add ( 11 , Digit , 13 );
   
   add ( 12 , Digit , 13 );
   
   add ( 13 , SeparatorChar , 8 );
   add ( 13 , Digit , 13 );
   add ( 13 , ";" , 1 );
   
   /*
    * BOX STATES
    */
   
   add ( 14 , BlankChar , 14 );
   add ( 14 , Digit , 15 );
   
   add ( 15 , Digit , 15 );
   add ( 15 , SeparatorChar , 16 );

   add ( 16 , SeparatorChar , 16 );
   add ( 16 , Digit , 17 );
   
   add ( 17 , Digit , 17 );
   add ( 17 , SeparatorChar , 18 );
   
   add ( 18 , SeparatorChar , 18 );
   add ( 18 , "-" , 19 );
   add ( 18 , Digit , 20 );
   
   add ( 19 , Digit , 20 );
   
   add ( 20 , Digit , 20 );
   add ( 20 , SeparatorChar , 21 );
   
   add ( 21 , SeparatorChar , 21 );
   add ( 21 , "-" , 22 );
   add ( 21 , Digit , 23 );
   
   add ( 22 , Digit , 23 );
   
   add ( 23 , Digit , 23 );
   add ( 23 , SeparatorChar , 24 );
   add ( 23 , ";" , 1 );
   
   add ( 24 , SeparatorChar , 24 );
   add ( 24 , "-" , 25 );
   add ( 24 , Digit , 26 );
   add ( 24 , ";" , 1 );
   
   add ( 25 , Digit , 26 );
   
   add ( 26 , Digit , 26 );
   add ( 26 , SeparatorChar , 27 );
   
   add ( 27 , SeparatorChar , 27 );
   add ( 27 , "-" , 28 );
   add ( 27 , Digit , 29 );
   
   add ( 28 , Digit , 29 );
   
   add ( 29 , Digit , 29 );
   add ( 29 , SeparatorChar , 30 );
   add ( 29 , ";" , 1 );
   
   add ( 30 , SeparatorChar , 30 );
   add ( 30 , ";" , 1 );
   
   /*
    * ROUNDFLASH STATES
    */
   
   add ( 31 , BlankChar , 31 );
   add ( 31 , Digit , 32 );
   
   add ( 32 , Digit , 32 );
   add ( 32 , SeparatorChar , 33 );
   
   add ( 33 , SeparatorChar , 33 );
   add ( 33 , "-" , 34 );
   add ( 33 , Digit , 35 );
   
   add ( 34 , Digit , 35 );
   
   add ( 35 , Digit , 35 );
   add ( 35 , SeparatorChar , 36 );
   
   add ( 36 , SeparatorChar , 36 );
   add ( 36 , "-" , 37 );
   add ( 36 , Digit , 38 );
   
   add ( 37 , Digit , 38 );
   
   add ( 38 , Digit , 38 );
   add ( 38 , SeparatorChar , 39 );
   add ( 38 , ";" , 1 );
   
   add ( 39 , SeparatorChar , 39 );
   add ( 39 , ";" , 1 );
   
   /*
    * WIRE STATES
    */
   
   add ( 40 , BlankChar , 40 );
   add ( 40 , Digit , 41 );
   
   add ( 41 , Digit , 41 );
   add ( 41 , SeparatorChar , 42 );
   
   add ( 42 , SeparatorChar , 42 );
   add ( 42 , "-" , 43 );
   add ( 42 , Digit , 44 );
   
   add ( 43 , Digit , 44 );
   
   add ( 44 , Digit , 44 );
   add ( 44 , SeparatorChar , 45 );
   
   add ( 45 , SeparatorChar , 45 );
   add ( 45 , "-" , 46 );
   add ( 45 , Digit , 47 );
   
   add ( 46 , Digit , 47 );
   
   add ( 47 , Digit , 47 );
   add ( 47 , SeparatorChar , 48 );
   add ( 47 , ";" , 1 );
   
   add ( 48 , SeparatorChar , 48 );
   add ( 48 , "-" , 49 );
   add ( 48 , Digit , 50 );
   add ( 48 , ";" , 1 );
   
   add ( 49 , Digit , 50 );
   
   add ( 50 , Digit , 50 );
   add ( 50 , SeparatorChar , 51 );
   
   add ( 51 , SeparatorChar , 51 );
   add ( 51 , "-" , 52 );
   add ( 51 , Digit , 53 );
   
   add ( 52 , Digit , 53 );
   
   add ( 53 , SeparatorChar , 48 );
   add ( 53 , Digit , 53 );
   add ( 53 , ";" , 1 );
   
   /*
    * LAYER STATES
    */
   
   add ( 54 , BlankChar , 54 );
   add ( 54 , LayerNameChar , 55 );
   
   // Don't swap the order of this two lines, of the transition priorities are going to be broken
   // (the LayerNameChar set overwrites some BlankChar characters)
   add ( 55 , BlankChar , 56 );
   add ( 55 , LayerNameChar , 55 );
   add ( 55 , ";" , 1 );
   
   add ( 56 , BlankChar , 56 );
   add ( 56 , ";" , 1 );
   
   /*
    * DEFINITION COMMANDS (DELETE, START, END)
    */
   
   add ( 57 , BlankChar , 57 );
   add ( 57 , "S" , 58 );
   add ( 57 , "F" , 66 );
   add ( 57 , "D" , 67 );
   
   // Substates: Definition Start
   
   add ( 58 , SeparatorChar , 59 );
   add ( 58 , Digit , 60 );
   
   add ( 59 , SeparatorChar , 59 );
   add ( 59 , Digit , 60 );
   
   add ( 60 , Digit , 60 );
   add ( 60 , SeparatorChar , 61 );
   add ( 60 , ";" , 1 );
   
   add ( 61 , SeparatorChar , 61 );
   add ( 61 , Digit , 62 );
   add ( 61 , ";" , 1 );
   
   add ( 62 , Digit , 62 );
   add ( 62 , SeparatorChar , 63 );
   
   add ( 63 , SeparatorChar , 63 );
   add ( 63 , Digit , 64 );
   
   add ( 64 , Digit , 64 );
   add ( 64 , SeparatorChar , 65 );
   add ( 64 , ";" , 1 );
   
   add ( 65 , SeparatorChar , 65 );
   add ( 65 , ";" , 1 );
   
   // Substates: Definition Finish
   
   add ( 66 , SeparatorChar , 66 );
   add ( 66 , ";" , 1 );
   
   // Substates: Definition delete
   
   add ( 67 , BlankChar , 67 );
   add ( 67 , Digit , 68 );
   
   add ( 68 , Digit , 68 );
   add ( 68 , SeparatorChar , 69 );
   add ( 68 , ";" , 1 );
   
   add ( 69 , SeparatorChar , 69 );
   add ( 69 , ";" , 1 );
   
   /*
    * CALL COMMAND STATES
    */
   
   add ( 70 , BlankChar , 70 );
   add ( 70 , Digit , 71 );
   
   add ( 71 , Digit , 71 );
   add ( 71 , ";" , 1 );
   add ( 71 , BlankChar , 72 );
   add ( 71 , "T" , 73 );
   add ( 71 , "M" , 79 );
   add ( 71 , "R" , 82 );
   
   add ( 72 , BlankChar , 72 );
   add ( 72 , ";" , 1 );
   add ( 72 , "T" , 73 );
   add ( 72 , "M" , 79 );
   add ( 72 , "R" , 82 );
   
   add ( 73 , BlankChar , 73 );
   add ( 73 , "-" , 74 );
   add ( 73 , Digit , 75 );
   
   add ( 74 , Digit , 75 );
   
   add ( 75 , Digit , 75 );
   add ( 75 , SeparatorChar , 76 );
   
   add ( 76 , SeparatorChar , 76 );
   add ( 76 , "-" , 77 );
   add ( 76 , Digit , 78 );
   
   add ( 77 , Digit , 78 );
   
   add ( 78 , Digit , 78 );
   add ( 78 , BlankChar , 72 );
   add ( 78 , ";" , 1 );
   add ( 78 , "M" , 79 );
   add ( 78 , "R" , 82 );
   add ( 78 , "T" , 73 );
   
   add ( 79 , BlankChar , 79 );
   add ( 79 , "X" , 80 );
   add ( 79 , "Y" , 81 );
   
   add ( 80 , BlankChar , 72 );
   add ( 80 , ";" , 1 );
   add ( 80 , "T" , 73 );
   add ( 80 , "R" , 82 );
   add ( 80 , "M" , 79 );
   
   add ( 81 , BlankChar , 72 );
   add ( 81 , ";" , 1 );
   add ( 81 , "T" , 73 );
   add ( 81 , "R" , 82 );
   add ( 81 , "M" , 79 );
   
   add ( 82 , BlankChar , 82 );
   add ( 82 , "-" , 83 );
   add ( 82 , Digit , 84 );
   
   add ( 83 , Digit , 84 );
   
   add ( 84 , Digit , 84 );
   add ( 84 , SeparatorChar , 85 );
   
   add ( 85 , SeparatorChar , 85 );
   add ( 85 , "-" , 86 );
   add ( 85 , Digit , 87 );
   
   add ( 86 , Digit , 87 );
   
   add ( 87 , Digit , 87 );
   add ( 87 , BlankChar , 72 );
   add ( 87 , ";" , 1 );
   add ( 87 , "T" , 73 );
   add ( 87 , "M" , 79 );
   add ( 87 , "R" , 82 );
   
   /*
    * DELETE COMMAND STATES
    */
   
   add ( 88 , ExtentionChar , 88 );
   add ( 88 , ";" , 1 );
   
   /*
    * COMMENT STATES
    */
   
   add ( 89 , CommentChar , 89 );
   add ( 89 , ")" , 90 );
   
   add ( 90 , BlankChar , 90 );
   add ( 90 , ";" , 1 );
   
   /*
    * END COMMAND STATES
    */
   
   add ( 91 , SeparatorChar , 91 );
   add ( 91 , ";" , 92 );
   
   add ( 92 , SeparatorChar , 92 );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::CIFFSM::~CIFFSM ( void )
{
}

/* 
 * Member function to add a special group of transitions.
 */
void OpenCIF::CIFFSM::add ( const int& input_state , const OpenCIF::CIFFSM::Transition& input_chars , const int& output_state )
{
   std::string tmp;
   
   switch ( input_chars )
   {
      case Digit:
         for ( int i = '0'; i <= '9'; i++ )
         {
            tmp = (char)i;
            add ( input_state , tmp , output_state );
         }
         break;
         
      case UpperChar:
         for ( int i = 'A'; i <= 'Z'; i++ )
         {
            tmp = (char)i;
            add ( input_state , tmp , output_state );
         }
         break;
      case LowerChar:
         for ( int i = 'a'; i <= 'z'; i++ )
         {
            tmp = (char)i;
            add ( input_state , tmp , output_state );
         }
         break;
         
      case BlankChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( !( std::isdigit ( i ) ||
                    std::isupper ( i ) ||
                    i == '-' || 
                    i == '(' ||
                    i == ')' ||
                    i == ';' ) )
            {
               tmp = (char)i;
               add ( input_state , tmp , output_state );
            }
         }
         break;
         
      case UserChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( i != ';' )
            {
               tmp = (char)i;
               add ( input_state , tmp , output_state );
            }
         }
         break;
         
      case CommentChar:
         for ( int i = 0; i < 256; i++ )
         {
            tmp = (char)i;
            add ( input_state , tmp , output_state );
         }
         break;
         
      case SeparatorChar:
         add ( input_state , LowerChar , output_state );
         add ( input_state , BlankChar , output_state );
         break;
         
      case LayerNameChar:
         add ( input_state , Digit , output_state );
         add ( input_state , UpperChar , output_state );
         add ( input_state , "_" , output_state );
         break;
         
      case ExtentionChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( i != ';' )
            {
               tmp = (char)i;
               add ( input_state , tmp , output_state );
            }
         }
         break;
         
      default:
         std::cerr << "OpenCIF->CIFFSM->add: Logical error detected." << std::endl;
         std::cerr << "                      Adding a special group of input chars, detected an unknown group of values." << std::endl;
         std::cerr << "                      Such group will be skipped, but there can be errors validating files." << std::endl;
         break;
   }
   
   return;
}

/*
 * Member function to return the next state of the FSM based in an input char.
 * 
 * This member function takes the input char. If the current state is other but those
 * ones for the comment command, only passes to the member of the parent class.
 * 
 * If the current state if one of those ones for the comment command, there is needed
 * to take care of he parentheses that open and closes.
 * 
 * The CIF file format stablish that there should be a balanced amount of them in a
 * command.
 * 
 * Something like this:
 * 
 *      ( This is a valid comment );
 *      ((This is also a valid comment));
 *      (This a (valid) (comment) ((because is balanced))());
 * 
 *      (( This comment is invalid);
 *      (This other ()()()(())) is also invalid);
 * 
 * So, internally, the CIFFSM should have a control of the parentheses that
 * opens and those that close.
 */

int OpenCIF::CIFFSM::operator[] ( const char& input_char )
{
   int new_state = -1;
   
   // Ok. If I'm at state 1 AND the input char is a parentheses '(', then, increase
   // the parentheses counter by 1 and do the jump.
   
   // If the current state is 89 AND the input char is a parentheses '(', then,
   // increase the parentheses counter by 1, but don't perform the jump.
   
   // If the current state is 89 AND the input char is a parentheses ')' AND
   // the parentheses counter is more than 1, substract 1 from it but don't
   // perform the jump.
   
   // If the current state is 89 AND the input char is a parentheses ')' AND
   // the parentheses counter is equal to 1, substract 1 from it AND perform
   // the jump.
   
   if ( currentState () == 1 && input_char == '(' )
   {
      new_state = FiniteStateMachine::operator[] ( input_char );
      parentheses = 1;
   }
   else if ( currentState () == 89 )
   {
      if ( input_char == '(' )
      {
         parentheses++;
         new_state = currentState ();
      }
      else if ( input_char == ')' )
      {
         if ( parentheses > 1 )
         {
            parentheses--;
            new_state = currentState ();
         }
         else if ( parentheses == 1 )
         {
            parentheses = 0;
            new_state = FiniteStateMachine::operator[] ( input_char );
         }
         else
         {
            new_state = -1;
         }
      }
      else
      {
         new_state = FiniteStateMachine::operator[] ( input_char );
      }
   }
   else
   {
      new_state = FiniteStateMachine::operator[] ( input_char );
   }
    
   return ( new_state );
}

void OpenCIF::CIFFSM::add ( const int& input_state, const std::string& input_chars, const int& output_state )
{
   FiniteStateMachine::add ( input_state , input_chars , output_state );
   
   return;
}

// FILE: file.cc


/*
 * Default constructor. Nothing to do.
 */
OpenCIF::File::File ( void )
{
}

/*
 * Destructor. Delete the commands stored (if any).
 */
OpenCIF::File::~File ( void )
{
   for ( unsigned int i = 0; i < file_commands.size (); i++ )
   {
      delete file_commands[ i ];
      file_commands[ i ] = 0;
   }
}

/*
 * Member function to return the commands vector.
 */
std::vector< OpenCIF::Command* > OpenCIF::File::getCommands ( void ) const
{
   return ( file_commands );
}

/*
 * Member function to return the file path.
 */
std::string OpenCIF::File::getPath ( void ) const
{
   return ( file_path );
}

/*
 * Member function to set a vector of commands.
 */
void OpenCIF::File::setCommands ( const std::vector< OpenCIF::Command* >& new_commands )
{
   file_commands = new_commands;
   
   return;
}

/*
 * Member function to release the vector of commands.
 */
void OpenCIF::File::dropCommands ( void )
{
   std::vector< OpenCIF::Command* > temporal_vector;
   file_commands = temporal_vector;
   
   return;
}

/*
 * Member function to set the path to the file.
 */
void OpenCIF::File::setPath ( const std::string& new_path )
{
   file_path = new_path;
   
   return;
}

/*
 * Member function to return the messages generated during the load of the file.
 */
std::vector< std::string > OpenCIF::File::getMessages ( void )
{
   return ( file_messages );
}

/*
 * Member function to load the input file. There is returned a LoadStatus
 * value that indicates the result of the process.
 */
OpenCIF::File::LoadStatus OpenCIF::File::loadFile ( const LoadMethod& load_method )
{
   LoadStatus end_status;
   
   file_messages.clear ();
   
   end_status = openFile ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   end_status = validateSyntax ( load_method );
   cleanCommands ();
   
   if ( end_status != AllOk && load_method != ContinueOnError )
   {
      return ( end_status );
   }
   
   convertCommands ();
   
   return ( end_status );
}

/*
 * This member function try to open the input file.
 */
OpenCIF::File::LoadStatus OpenCIF::File::openFile ( void )
{
   if ( file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Warning: Input file already opened. Closing." ) );
      file_input.close ();
   }
   
   file_input.open ( file_path.c_str () );
   
   if ( !file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Error: Can't open input file." ) );
      
      return ( CantOpenInputFile );
   }
   
   return ( AllOk );
}

/*
 * This member function validates the contents of the input file using
 * a finite state machine.
 */
OpenCIF::File::LoadStatus OpenCIF::File::validateSyntax ( const LoadMethod& load_method )
{
   /*
    * The process of validation isn't that complex.
    * 
    * I need to create a CIFFSM class instance. Such instance will help me to validate
    * the file contents. The file is already opened. So, I'll read char by char and feed
    * them to the CIFFSM instance. The CIFFSM instance will start, by default, in state 1.
    * 
    * I'll feed the instance characters until I reach the end of file or the instance reports
    * an error (jump state equal to -1). After feeding the characters, if I finish feeding the
    * file and none error was reported, I will check the current state of the instance.
    * 
    * The instance should end in state 91 or 92. If the FSM is in such states, the file is 
    * correct and the format is supported.
    * 
    * If the FSM ends in any other state, the file is not neccessarally incorrect, but incomplete.
    * 
    * If there is a jump to a negative state, the file is invalid.
    */
   
   OpenCIF::CIFFSM* fsm;
   std::string command_buffer;
   int jump_state = 1; // By default, start in 1
   int previous_state; // Previous state.
   char input_char;
   char previous_char;
   bool errors_omited = false;
   
   fsm = new OpenCIF::CIFFSM ();
   
   file_raw_commands.clear ();
   
   // Iterate over the contents of the file, until the file end is
   // reached or the FSM reports a problem.
   
   while ( !file_input.eof () && jump_state != -1 )
   {
      previous_char = input_char;
      input_char = file_input.get ();
   
      if ( !file_input.eof () )
      {
         previous_state = jump_state;
         jump_state = fsm->operator[] ( input_char );
         
         if ( jump_state == 1 && previous_state != 1 ) // If I'm returning to the first state, the command
                                                       // is loaded. Just check the previous state. If the
                                                       // previous state is the state 1, then, do nothing,
                                                       // since those are characteres to skip.
         {
            std::string tmp;
            tmp = input_char;
            command_buffer += tmp;
            
            // I call the CleanCommand member function to remove unnecesary characters.
            file_raw_commands.push_back ( command_buffer );
            command_buffer = "";
         }
         else if ( jump_state != 1 && jump_state != -1 )
         {
            std::string tmp;
            tmp = input_char;
            command_buffer += tmp;
         }
         
         // Check if the current jump state is to an error. 
         // If so, and the load method indicates "ContinueOnError", reset the FSM
         // to state 1, reset the current jumps to 1, clean the command buffer and skip chars until a semicolon
         
         if ( jump_state == -1 && load_method == ContinueOnError )
         {
            fsm->reset ();
            jump_state = 1;
            errors_omited = true;
            command_buffer = "";
            
            file_input.putback ( input_char );
            file_raw_commands.push_back ( "(LibOpenCIF: Incorrect command here) ;" );
         }
      }
   }
   
   // File validated. What is the result?
   std::ostringstream oss;
   
   if ( jump_state == -1 )
   {
      std::string tmp;
      
      // There is an invalid input.
      file_messages.push_back ( std::string ( "File:validateSintax:Error: Error detected when validating contents of input file." ) );
      
      oss << previous_state;
      
      file_messages.push_back ( std::string ( "                           State: " ) + oss.str () );
      
      oss.str ( std::string ( "" ) );
      oss << (char)previous_char;
      
      tmp = tmp;
      
      file_messages.push_back ( std::string ( "                           Input char: \"" ) +
                                tmp +
                                std::string ( "\" (ASCII=" ) +
                                (
                                   ( oss.str ( std::string ( "" ) ) , oss << (int)previous_char ) ,
                                   oss.str ()
                                ) +
                                std::string ( ")" )
                              );
      
      file_messages.push_back ( std::string ( "                           Current command buffer: \"" ) + command_buffer + std::string ( "\"" ) );
      file_messages.push_back ( std::string ( "                           The loaded raw commands can be accessed to analize the error and locate the error." ) );
      
      return ( IncorrectInputFile );
   }
   
   if ( jump_state != 91 && jump_state != 92 )
   {
      file_messages.push_back ( std::string ( "File:validateSintax:Error: The file contents are incomplete (maybe a missing END command)." ) );
      
      return ( IncompleteInputFile );
   }
   
   // Everything Ok. Add last command (the END command)
   file_raw_commands.push_back ( cleanCommand ( command_buffer ) );
   
   return ( ( errors_omited) ? IncorrectInputFile : AllOk );
}

void OpenCIF::File::cleanCommands ( void )
{
   for ( unsigned long int i = 0; i < file_raw_commands.size (); i++ )
   {
      file_raw_commands[ i ] = cleanCommand ( file_raw_commands[ i ] );
   }
   
   return;
}

/*
 * This member function loads the contents of the input file and converts them
 * into Command instances.
 */
void OpenCIF::File::convertCommands ( void )
{
   /*
    * The raw commands are ready and validated. So, there is only left the process of
    * turning those strings into commands.
    */
   
   // First, delete and clear the current commands vector
   for ( unsigned int i = 0; i < file_commands.size (); i++ )
   {
      delete file_commands[ i ];
      file_commands[ i ] = 0;
   }
   
   file_commands.clear ();
   
   // Iterate over the raw commands. Check the first char of all. The first char will tell me exactly
   // wich command type is every one.
   
   for ( unsigned long int i = 0; i < file_raw_commands.size (); i++ )
   {
      std::string str_command;
      OpenCIF::Command* command;
      
      str_command = file_raw_commands[ i ];
      
      switch ( str_command[ 0 ] )
      {
         case 'B':
            command = new OpenCIF::BoxCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'P':
            command = new OpenCIF::PolygonCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'W':
            command = new OpenCIF::WireCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'R':
            command = new OpenCIF::RoundFlashCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case '(':
            command = new OpenCIF::CommentCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'C':
            command = new OpenCIF::CallCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'D':
            switch ( str_command[ 2 ] )
            {
               case 'D':
                  command = new OpenCIF::DefinitionDeleteCommand ( str_command );
                  file_commands.push_back ( command );
                  break;
                  
               case 'F':
                  command = new OpenCIF::DefinitionEndCommand ( str_command );
                  file_commands.push_back ( command );
                  break;
                  
               case 'S':
                  command = new OpenCIF::DefinitionStartCommand ( str_command );
                  file_commands.push_back ( command );
                  break;
            }
            break;
            
         case 'L':
            command = new OpenCIF::LayerCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'E':
            command = new OpenCIF::EndCommand ();
            file_commands.push_back ( command );
            break;
            
         default:
            command = new OpenCIF::UserExtensionCommand ( str_command );
            file_commands.push_back ( command );
            break;
      }
   }
   
   return;
}

/*
 * This member function returns the vector of the raw (string) commands of the file.
 */
std::vector< std::string > OpenCIF::File::getRawCommands ( void ) const
{
   return ( file_raw_commands );
}

/*
 * This member function takes as argument a command in string form. The command is "not clear". That means
 * that is in the same way it was readed from the file.
 * 
 * The process of cleaning is to delete anything that is not intented to exist and leave only that things that can make
 * the command easy to parse.
 * 
 * For example, from this: "P-100,10000thisisvalid-10000cuac,cuac,cuac,imaduck-20000yolo;"
 * To this:                "P -100 10000 -10000 -20000 ;"
 * 
 * So, such kind of string can be used as an input stream to read easily.
 * 
 * There are some commands that I can't clean, like the comment or user expansion commands. Those commands are just returned.
 * 
 * At least, I can know what kind of command I'm working with by it's first char.
 */
std::string OpenCIF::File::cleanCommand ( std::string command )
{
   std::string final_command;
   
   switch ( command[ 0 ] )
   {
      // All of these commands can be processed as the same, since they only need values.
      case 'P':
      case 'B':
      case 'W':
      case 'R':
         final_command = clearNumericCommand ( command );
         break;
         
      case 'L': // Layer command
         final_command = cleanLayerCommand ( command );
         break;
         
      case 'C': // Call command
         final_command = cleanCallCommand ( command );
         break;
         
      case 'D': // Definition {Start|End|Delete} command.
         final_command = cleanDefinitionCommand ( command );
         break;
         
      case 'E': // End command.
         final_command = "E ;";
         break;
         
      default:
         final_command = command.substr ( 0 , command.size () - 1 ) + " ;";
         break;
   }
   
   return ( final_command );
}

/*
 * This member function takes as argument a string that, maybe, is a CIF command.
 * 
 * The operation done is similar to the one performed when loading a CIF file, but
 * applied directly to a string. The idea is to validate a single string as a service
 * for the user.
 */
bool OpenCIF::File::isCommandValid ( std::string command )
{
   /*
    * The process of validation isn't that complex.
    * 
    * I need to create a CIFFSM class instance. Such instance will help me to validate
    * the command contents. I'll read char by char and feed them to the CIFFSM instance.
    * The CIFFSM instance will start, by default, in state 1.
    * 
    * I'll feed the instance characters until I reach the end of the command or the instance reports
    * an error (jump state equal to -1). After feeding the characters, if I finish feeding the
    * command and none error was reported, I will check the current state of the instance.
    * 
    * The instance should end in state 91 or 92. If the FSM is in such states, the command is 
    * correct and the format is supported.
    * 
    * If there is a jump to a negative state, the command is invalid.
    * 
    * Also, I'm considering an invalid a string like this one:
    * 
    * this.is.an.invalid.string
    * 
    * Such string, according to the FSM used, is valid, since all of those characters are considered
    * "Black characters", they are chars used to add spaces between commands.
    * 
    * So, what I'm considering a valid command? A string that *has* a valid command. If none valid
    * command is found, then, even if the FSM says no invalid char is found, I'm going to return
    * false, since a technically empty string doesn't count as a command.
    */
   
   OpenCIF::CIFFSM* fsm;
   
   int jump_state = 1; // By default, start in 1
   char input_char;
   bool cif_command_found = false; // Flag to prevent validating strings that are, technically speaking, empty.
   
   fsm = new OpenCIF::CIFFSM ();
   
   // Iterate over the contents of the string, until the string end is
   // reached or the FSM reports a problem.
   
   for ( unsigned int i = 0; i < command.size () && jump_state != -1; i++ )
   {
      input_char = command[ i ];
      
      jump_state = fsm->operator[] ( input_char );
      
      if ( jump_state > 1 )
      {
         cif_command_found = true;
      }
   }
   
   // String validated. What is the result?
   if ( jump_state == -1 )
   {      
      return ( false );
   }
   
   // If no command found, is considered invalid
   if ( !cif_command_found )
   {
      return ( false );
   }
   
   // Everything Ok. The string is a valid according to the CIF format.
   
   return ( true );
}

/*
 * This member function takes as argument a Definition command and returns it cleaned.
 * 
 * A definition command can be something like this:
 * 
 *      "DxxxxxSlol100im,totally,legal;"
 * 
 * So, the task of this member function is to turn it into like this:
 * 
 *      "D S 100 ;"
 * 
 * The process begins with the deletion of any non-digit and non-uppercase characters.
 * Such operation, if good, can leave a command like this:
 * 
 *      "DS100;"
 * 
 * To simplify the process of converting commands into instances, the commands must have
 * whitespaces to separate components (to use the strings as, for example, input streams).
 * 
 * So, the next process is to separate the components to turn the command into this:
 * 
 *      "D S 100 ;"
 */
std::string OpenCIF::File::cleanDefinitionCommand ( std::string command )
{
   std::string final_command;
   std::string tmp = " ";
            
   // There are only uppercase chars and digits
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   command[ 0 ] = ' ';
   for ( unsigned int i = 0; i < command.size (); i++ )
   {
      // If the current char is not a 'D', not a digit, not an 'S' and not an 'F'
      if ( !std::isdigit ( command[ i ] ) && !std::isupper ( command[ i ] ) )
      {
         command[ i ] = ' ';
      }
   }
   
   for ( unsigned int i = 1; i < command.size (); i++ )
   {
      if ( std::isdigit ( command[ i ] ) )
      {
         final_command += command[ i ];
      }
      else if ( command[ i ] != ' ' )
      {
         final_command += command[ i ];
         final_command += " ";
      }
      else if ( command[ i ] == ' ' && final_command[ final_command.size () - 1 ] != ' ' )
      {
         final_command += " ";
      }
   }
   
   ( final_command[ final_command.size () - 1 ] == ' ' )
      ? final_command += ";"
      : final_command += " ;";
   
   return ( final_command );
}

/*
 * This member function takes as argument a call command and returns it cleaned.
 * 
 * A call command can be something like this:
 * 
 *      "C1T20000 -20000R1000000 -59999MXlololololololololMY MXMXMXMYMXR100 100R100 100;"
 * 
 * So, the task of this member function is to turn it into like this:
 * 
 *      "C 1 T 20000 -20000 R 1000000 -59999 M X M Y M X M X M X M Y M X R 100 100 R 100 100;"
 * 
 * The process begins with the deletion of any non-digit, non-dash ('-') and non-uppercase characters.
 * Such operation, if good, can leave a command like this:
 * 
 *      "C 1 T 20000 -20000 R 1000000 -59999 MX MY MXMXMXMYMXR100 100R100 100;"
 * 
 * To simplify the process of converting commands into instances, the commands must have
 * whitespaces to separate components (to use the strings as, for example, input streams).
 * 
 * So, the next process is to separate the components to turn the command into this:
 * 
 *      "C 1 T 20000 -20000 R 1000000 -59999 M X M Y M X M X M X M Y M X R 100 100 R 100 100;"
 */
std::string OpenCIF::File::cleanCallCommand ( std::string command )
{
   std::string final_command;
   std::string tmp = " ";
            
   // There are only uppercase chars
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   command[ 0 ] = ' ';
   for ( unsigned int i = 0; i < command.size (); i++ )
   {
      if ( !std::isdigit ( command[ i ] ) && !std::isupper( command[ i ] ) && command[ i ] != '-' )
      {
         command[ i ] = ' ';
      }
   }
   
   for ( unsigned int i = 1; i < command.size (); i++ )
   {
      tmp = command[ i ];
      
      if ( std::isdigit ( command[ i ] ) )
      {
         final_command += tmp;
      }
      else if ( command[ i ] != ' ' )
      {
         if ( final_command[ final_command.size () - 1 ] != ' ' )
         {
            final_command += " ";
         }
         
         final_command += tmp;
         
         if ( std::isupper ( command[ i ] ) )
         {
            final_command += " ";
         }
      }
      else if ( final_command[ final_command.size () - 1 ] != ' ' )
      {
         final_command += " ";
      }
   }
   
   ( final_command[ final_command.size () - 1 ] == ' ' )
      ? final_command += ";"
      : final_command += " ;";
   
   return ( final_command );
}

/*
 * This member function takes as argument a Layer camand and removes any unnecesary character.
 */
std::string OpenCIF::File::cleanLayerCommand ( std::string command )
{
   std::string tmp = " ";
   std::string final_command;
            
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   command[ 0 ] = ' ';
   for ( unsigned int i = 0; i < command.size (); i++ )
   {
      if ( !std::isupper ( command[ i ] ) && command[ i ] != '_' && ! std::isdigit ( command[ i ] ) )
      {
         command[ i ] = ' ';
      }
   }
   
   std::istringstream iss ( command );
   
   while ( !iss.eof () )
   {
      iss >> tmp;
      
      if ( !iss.eof () )
      {
         final_command += tmp;
         tmp = " ";
         final_command += tmp;
      }
   }
   
   final_command += ";";
            
   return ( final_command );
}

/*
 * This member function takes as argument a numeric command (like a Polygon or Box command)
 * and cleans it.
 * 
 * A numeric command can be something like this:
 * 
 *      "W1000,muajajajajaja20000,,,this,is,valid20000twerking,so,hard,,,,,,xoxoxoxoxox-10000,-10000,-500 juar juar juarX-4000;"
 * 
 * So, the task of this member function is to turn it into like this:
 * 
 *      "W 1000 20000 20000 -10000 -10000 -500 -4000 ;"
 * 
 * The process begins with the deletion of any non-digit and non-dash ('-') characters.
 * Such operation, if good, can leave a command like this:
 * 
 *      "W1000              20000                20000                                 -10000 -10000 -500                -4000;"
 * 
 * To simplify the process of converting commands into instances, the commands must have
 * whitespaces to separate components (to use the strings as, for example, input streams).
 * 
 * So, the next process is to separate the components to turn the command into this:
 * 
 *      "W 1000 20000 20000 -10000 -10000 -500 -4000 ;"
 */
std::string OpenCIF::File::clearNumericCommand ( std::string command )
{
   std::string tmp = " ";
   std::string final_command;
            
   // There are only numbers and guides ("-")
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   for ( unsigned int i = 0; i < command.size (); i++ )
   {
      if ( !std::isdigit ( command[ i ] ) && command[ i ] != '-' )
      {
         command[ i ] = ' ';
      }
   }
   
   std::istringstream iss ( command );
   
   while ( !iss.eof () )
   {
      iss >> tmp;
      
      if ( !iss.eof () )
      {
         final_command += tmp;
         tmp = " ";
         final_command += tmp;
      }
   }
   
   final_command += ";";
   
   return ( final_command );
}