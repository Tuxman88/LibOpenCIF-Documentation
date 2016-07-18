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

# ifndef LIBOPENCIF_H_
# define LIBOPENCIF_H_

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <vector>

// To search over the contents of the original files, search for the word "FILE:"

// FILE: opencif.h

namespace OpenCIF
{
   const std::string LibraryVersion = "1.0.3";
   const std::string LibraryName = "LibOpenCIF";
   const std::string LibraryAuthor = "Moises Chavez-Martinez";
   const std::string LibrarySupport = "moises.chavez.martinez@gmail.com";
   const std::string LibraryCIFVersion = "2.0";
}

// FILE: command.h


namespace OpenCIF { class Command; }
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::Command* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Command* command );

// General namespace for all the library contents.
namespace OpenCIF
{     
   /*
    * Main class. Base for a lot of classes. Gives the powers needed
    * to store all the commands from the CIF file into a single list
    * using pointers to the base class (this class).
    * 
    * To detect the type of the classes once the list is filled, the
    * class contains a member function to return the type of every
    * instance (every class changes the value of such value, so, once
    * created, every instance has a different type).
    */
   
   class Command
   {
      public:
         // Enumeration for this class and child classes.
         enum CommandType
         {
            PlainCommand = 0 ,
            Primitive ,
            Control ,
            RawContent ,
            PathBased ,
            PositionBased ,
            DefinitionStart ,
            DefinitionDelete ,
            Call ,
            DefinitionEnd ,
            Comment ,
            UserExtension , 
            Polygon ,
            Wire ,
            Box ,
            RoundFlash ,
            Layer ,
            End
         };
         
      public:
         explicit Command ( void ); // Main constructor.
         virtual ~Command ( void ); // Destructor
         virtual CommandType type ( void ); // Returns the type of the instance. In this case, should return "PlainCommand"
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , Command* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , Command* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      protected:
         CommandType command_type;
         virtual unsigned long int toULInt ( const std::string& value );
         virtual long int toLInt ( const std::string& value );
   };
}

// FILE: primitivecommand.h


namespace OpenCIF
{
   class PrimitiveCommand : public OpenCIF::Command
   {
      public:
         explicit PrimitiveCommand ( void );
         virtual ~PrimitiveCommand ( void );
   };
}

// FILE: point.h


namespace OpenCIF { class Point; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Point& point );
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Point& point );

namespace OpenCIF
{
   class Point
   {
      public:
         explicit Point ( void );
         explicit Point ( const long int& new_x , const long int& new_y );
         virtual ~Point ( void );
         void setX ( const long int& new_x );
         void setY ( const long int& new_y );
         void set ( const long int& new_x , const long int& new_y );
         long int getX ( void ) const;
         long int getY ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , Point& point );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , const Point& point );
         
      private:
         long int point_x;
         long int point_y;
   };
}

// FILE: pathbasedcommand.h

namespace OpenCIF
{
   class PathBasedCommand : public OpenCIF::PrimitiveCommand
   {
      public:
         explicit PathBasedCommand ( void );
         virtual ~PathBasedCommand ( void );
         void setPoints ( const std::vector< OpenCIF::Point >& new_points );
         std::vector< OpenCIF::Point > getPoints ( void ) const;
         
      protected:
         std::vector< OpenCIF::Point > command_points;
   };
}

// FILE: polygoncommand.h

namespace OpenCIF { class PolygonCommand; }
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::PolygonCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::PolygonCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::PolygonCommand* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::PolygonCommand* command );

namespace OpenCIF
{
   class PolygonCommand : public OpenCIF::PathBasedCommand
   {
      public:
         explicit PolygonCommand ( void );
         explicit PolygonCommand ( const std::string& str_command );
         virtual ~PolygonCommand ( void );
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , PolygonCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , PolygonCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , PolygonCommand* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , PolygonCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
   };
}

// FILE: wirecommand.h

namespace OpenCIF { class WireCommand; }
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::WireCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::WireCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::WireCommand* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::WireCommand* command );

namespace OpenCIF
{
   class WireCommand : public OpenCIF::PathBasedCommand
   {
      public:
         explicit WireCommand ( void );
         explicit WireCommand ( const std::string& str_command );
         virtual ~WireCommand ( void );
         void setWidth ( const unsigned long int& new_width );
         unsigned long int getWidth ( void ) const;
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , WireCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , WireCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , WireCommand* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , WireCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         unsigned long int wire_width;
   };
}

// FILE: positionbasedcommand.h

namespace OpenCIF
{
   class PositionBasedCommand : public OpenCIF::PrimitiveCommand
   {
      public:
         explicit PositionBasedCommand ( void );
         virtual ~PositionBasedCommand ( void );
         void setPosition ( const OpenCIF::Point& new_position );
         OpenCIF::Point getPosition ( void ) const;
         
      protected:
         OpenCIF::Point command_position;
   };
}

// FILE: size.h


namespace OpenCIF { class Size; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Size& command );
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Size& command );

namespace OpenCIF
{
   class Size
   {
      public:
         explicit Size ( void );
         explicit Size ( const unsigned long int& new_width , const unsigned long int& new_height );
         virtual ~Size ( void );
         unsigned long int getWidth ( void ) const;
         unsigned long int getHeight ( void ) const;
         void setWidth ( const unsigned long int& new_width );
         void setHeight ( const unsigned long int& new_height );
         void set ( const unsigned long int& new_width , const unsigned long int& new_height );
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , Size& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , const Size& command );
         
      private:
         unsigned long int size_width;
         unsigned long int size_height;
   };
}

// FILE: boxcommand.h


namespace OpenCIF { class BoxCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand* command );

namespace OpenCIF
{
   class BoxCommand : public OpenCIF::PositionBasedCommand
   {
      public:
         explicit BoxCommand ( void );
         explicit BoxCommand ( const std::string& str_command );
         virtual ~BoxCommand ( void );
         void setRotation ( const OpenCIF::Point& new_rotation );
         void setSize ( const OpenCIF::Size& new_size );
         OpenCIF::Size getSize ( void ) const;
         OpenCIF::Point getRotation ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , BoxCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , BoxCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , BoxCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , BoxCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      protected:
         OpenCIF::Size box_size;
         OpenCIF::Point box_rotation;
   };
}

// FILE: roundflashcommand.h

namespace OpenCIF { class RoundFlashCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::RoundFlashCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::RoundFlashCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::RoundFlashCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::RoundFlashCommand* command );

namespace OpenCIF
{
   class RoundFlashCommand : public OpenCIF::PositionBasedCommand
   {
      public:
         explicit RoundFlashCommand ( void );
         explicit RoundFlashCommand ( const std::string& str_command );
         virtual ~RoundFlashCommand ( void );
         void setDiameter ( const unsigned long int& new_diameter );
         unsigned long int getDiameter ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , RoundFlashCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , RoundFlashCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , RoundFlashCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , RoundFlashCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         unsigned long int round_diameter;
   };
}

// FILE: controlcommand.h

namespace OpenCIF
{
   /*
    * This class has the objective to work as a base for the control
    * commands (DefinitionStart, DefinitionDelete, DefinitionEnd and Call).
    */
   class ControlCommand : public OpenCIF::Command
   {
      public:
         explicit ControlCommand ( void ); // Default constructor
         virtual ~ControlCommand ( void ); // Destructor
         void setID ( const unsigned long int& new_id );
         unsigned long int getID ( void ) const;
         
      protected:
         unsigned long int command_id; // Unsigned long int since the value lenght is unexpected (but must be non-negative)
   };
}

// FILE: fraction.h

namespace OpenCIF { class Fraction; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Fraction& command );
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Fraction& command );

namespace OpenCIF
{
   class Fraction
   {
      public:
         explicit Fraction ( void );
         explicit Fraction ( const unsigned long int& new_enumerator , const unsigned long int& new_denominator );
         virtual ~Fraction ( void );
         
         void set ( const unsigned long int& new_numerator , const unsigned long int& new_denominator );
         
         void setNumerator ( const unsigned long int& new_numerator );
         unsigned long int getNumerator ( void ) const;
         
         void setDenominator ( const unsigned long int& new_denominator );
         unsigned long int getDenominator ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , Fraction& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , const Fraction& command );
         
      private:
         unsigned long int fraction_numerator;
         unsigned long int fraction_denominator;
   };
}

// FILE: definitionstartcommand.h


namespace OpenCIF { class DefinitionStartCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionStartCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionStartCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionStartCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionStartCommand* command );

namespace OpenCIF
{
   class DefinitionStartCommand : public OpenCIF::ControlCommand
   {
      public:
         explicit DefinitionStartCommand ( void );
         explicit DefinitionStartCommand ( const std::string& str_command );
         virtual ~DefinitionStartCommand ( void );
         
         void setAB ( const OpenCIF::Fraction& new_ab );
         OpenCIF::Fraction getAB ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionStartCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionStartCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionStartCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionStartCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         OpenCIF::Fraction command_ab;
   };
}

// FILE: definitiondeletecommand.h


namespace OpenCIF { class DefinitionDeleteCommand; };
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand* command );

namespace OpenCIF
{
   class DefinitionDeleteCommand : public OpenCIF::ControlCommand
   {
      public:
         explicit DefinitionDeleteCommand ( void );
         explicit DefinitionDeleteCommand ( const std::string& str_command );
         virtual ~DefinitionDeleteCommand ( void );
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionDeleteCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionDeleteCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionDeleteCommand* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionDeleteCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
   };
}

// FILE: transformation.h


namespace OpenCIF { class Transformation; }
std::ostream& operator << ( std::ostream& output_stream , const OpenCIF::Transformation& transformation );
std::istream& operator >> ( std::istream& input_stream , OpenCIF::Transformation& transformation );

namespace OpenCIF
{
   class Transformation
   {
      public:
         enum TransformationType
         {
            Displacement = 0 ,
            Rotation ,
            HorizontalMirroring ,
            VerticalMirroring
         };
      
      public:
         explicit Transformation ( void );
         virtual ~Transformation ( void );
         
         void setType ( const TransformationType& new_type );
         TransformationType getType ( void ) const;
         
         void setRotation ( const OpenCIF::Point& new_rotation );
         OpenCIF::Point getRotation ( void ) const;
         
         void setDisplacement ( const OpenCIF::Point& new_displacement );
         OpenCIF::Point getDisplacement ( void ) const;
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , const Transformation& transformation );
         friend std::istream& (::operator>>) ( std::istream& input_stream , Transformation& transformation );
         
      private:
         TransformationType transformation_type;
         OpenCIF::Point transformation_point;
   };
}

// FILE: callcommand.h


// Forward declarations
namespace OpenCIF { class CallCommand; }
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CallCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::CallCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CallCommand* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::CallCommand* command );

namespace OpenCIF
{
   class CallCommand : public OpenCIF::ControlCommand
   {
      public:
         explicit CallCommand ( void );
         explicit CallCommand ( const std::string& str_command );
         virtual ~CallCommand ( void );
         
         void setTransformations ( const std::vector< OpenCIF::Transformation >& new_transformations );
         void addTransformation ( const OpenCIF::Transformation& new_transformation );
         std::vector< OpenCIF::Transformation >& getTransformations ( void );
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , CallCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , CallCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , CallCommand* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , CallCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         std::vector< OpenCIF::Transformation > call_transformations;
   };
}

// FILE: definitionendcommand.h


namespace OpenCIF { class DefinitionEndCommand; }
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionEndCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionEndCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionEndCommand* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionEndCommand* command );

namespace OpenCIF
{
   class DefinitionEndCommand : public OpenCIF::ControlCommand
   {
      public:
         explicit DefinitionEndCommand ( void );
         explicit DefinitionEndCommand ( const std::string& str_command );
         virtual ~DefinitionEndCommand ( void );
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionEndCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionEndCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionEndCommand* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionEndCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         // Turn these member functions into private, since this command doesn't need an ID
         void setID ( const unsigned long int& new_id );
         unsigned long int getID ( void ) const;
   };
}

// FILE: endcommand.h


namespace OpenCIF { class EndCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::EndCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::EndCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::EndCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::EndCommand* command );

namespace OpenCIF
{
   class EndCommand : public ControlCommand
   {
      public:
         explicit EndCommand ( void );
         virtual ~EndCommand ( void );
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , EndCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , EndCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , EndCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , EndCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         void setID ( const unsigned long int& new_id );
         unsigned long int getID ( void ) const;
   };
}

// FILE: rawcontentcommand.h


namespace OpenCIF
{
   class RawContentCommand : public OpenCIF::Command
   {
      public:
         explicit RawContentCommand ( void );
         virtual ~RawContentCommand ( void );
         void setContent ( const std::string& new_contents );
         std::string getContent ( void ) const;
         
      protected:
         std::string command_content;
   };
}

// FILE: userextentioncommand.h


namespace OpenCIF { class UserExtensionCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::UserExtensionCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::UserExtensionCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::UserExtensionCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::UserExtensionCommand* command );

namespace OpenCIF
{
   class UserExtensionCommand : public OpenCIF::RawContentCommand
   {
      public:
         explicit UserExtensionCommand ( void );
         explicit UserExtensionCommand ( const std::string& str_command );
         virtual ~UserExtensionCommand ( void );
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , UserExtensionCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , UserExtensionCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , UserExtensionCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , UserExtensionCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
   };
}

// FILE: commentcommand.h


namespace OpenCIF { class CommentCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::CommentCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CommentCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::CommentCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CommentCommand* command );

namespace OpenCIF
{
   class CommentCommand : public OpenCIF::RawContentCommand
   {
      public:
         explicit CommentCommand ( void );
         explicit CommentCommand ( const std::string& str_command );
         virtual ~CommentCommand ( void );
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , CommentCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , CommentCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , CommentCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , CommentCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
   };
}

// FILE: layercommand.h


namespace OpenCIF { class LayerCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::LayerCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::LayerCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::LayerCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::LayerCommand* command );

namespace OpenCIF
{
   class LayerCommand : public OpenCIF::Command
   {
      public:
         explicit LayerCommand ( void );
         explicit LayerCommand ( const std::string& str_command );
         virtual ~LayerCommand ( void );
         
         void setName ( const std::string& new_name );
         std::string getName ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , LayerCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , LayerCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , LayerCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , LayerCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         std::string layer_name;
   };
}

// FILE: state.h


namespace OpenCIF
{
   class State
   {
      public:
         explicit State ( void );
         virtual ~State ( void );
         
         void addOptions ( const std::string& new_options , const int& exit_state );
         int operator[] ( const char& input_char );
         void reset ( void );
         
      protected:
         int state_options[ 256 ];
   };
}

// FILE: finitestatemachine.h


namespace OpenCIF
{
   class FiniteStateMachine
   {
      public:
         explicit FiniteStateMachine ( const int& state_amount );
         virtual ~FiniteStateMachine ( void );
         
         void reset ( void );
         void add ( const int& input_state , const std::string& input_chars , const int& output_state );
         int operator[] ( const char& input_char );
         int currentState ( void ) const;
         
      protected:
         int fsm_current_state;
         std::vector< OpenCIF::State > fsm_states;
   };
}

// FILE: ciffsm.h


namespace OpenCIF
{
   class CIFFSM : public OpenCIF::FiniteStateMachine
   {
      private:
         enum Transition
         {
            Digit = 0 ,
            UpperChar ,
            LowerChar ,
            BlankChar ,
            UserChar ,
            CommentChar ,
            SeparatorChar ,
            LayerNameChar ,
            ExtentionChar
         };
      
      public:
         explicit CIFFSM ( void );
         virtual ~CIFFSM ( void );
         
         int operator[] ( const char& input_char );
         
      private:
         // This member function is being hidden.
         void add ( const int& input_state , const std::string& input_chars , const int& output_state );
         // This other member function is beign defined.
         void add ( const int& input_state , const Transition& input_chars , const int& output_state );
         
      private:
         int parentheses;
   };
}

// FILE: file.h


namespace OpenCIF
{
   class File
   {
      public:
         enum LoadStatus
         {
            AllOk = 0 ,
            CantOpenInputFile ,
            IncompleteInputFile ,
            IncorrectInputFile
         };
         
         enum LoadMethod
         {
            StopOnError = 0 ,
            ContinueOnError
         };
      
      public:
         explicit File ( void );
         virtual ~File ( void );
         void setPath ( const std::string& new_path );
         std::string getPath ( void ) const;
         
         void setCommands ( const std::vector< OpenCIF::Command* >& new_commands );
         std::vector< OpenCIF::Command* > getCommands ( void ) const;
         
         LoadStatus loadFile ( const LoadMethod& load_method = StopOnError ); // Whole process of loading a CIF file, from opening the file
                                                                              // to converting the commands into instances.
         LoadStatus openFile ( void );
         LoadStatus validateSyntax ( const LoadMethod& load_method = StopOnError );
         void cleanCommands ( void );
         void convertCommands ( void );
         
         std::vector< std::string > getMessages ( void );
         
         std::vector < std::string > getRawCommands ( void ) const;
         
      private:
         std::string cleanCommand ( std::string command );
         std::string clearNumericCommand ( std::string command );
         std::string cleanLayerCommand ( std::string command );
         std::string cleanCallCommand ( std::string command );
         std::string cleanDefinitionCommand ( std::string command );
         
      private:
         std::string file_path;
         std::ifstream file_input;
         std::vector< OpenCIF::Command* > file_commands;
         std::vector< std::string > file_raw_commands;
         std::vector< std::string > file_messages;
   };
}

# endif
