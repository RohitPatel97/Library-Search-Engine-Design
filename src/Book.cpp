#include <cmath>                                                      // abs(), pow()
#include <compare>                                                    // weak_ordering
#include <iomanip>                                                    // quoted()
#include <iostream>
#include <string>
#include <type_traits>                                                // is_floating_point_v, common_type_t
#include <utility>                                                    // move()

#include "Book.hpp"



/*******************************************************************************
**  Implementation of non-member private types, objects, and functions
*******************************************************************************/
namespace    // unnamed, anonymous namespace
{
  // Avoid direct equality comparisons on floating point numbers. Two values are equal if they are "close enough", which is
  // represented by Epsilon.  Usually, this is a pretty small number, but since we are dealing with money (only two, maybe three
  // decimal places) we can be a bit more tolerant.  Two floating point values are considered equal if they are within EPSILON of
  // each other.
  template< typename T,  typename U >   requires std::is_floating_point_v<std::common_type_t<T, U> >
  constexpr bool floating_point_is_equal( T const lhs,  U const rhs,  double const EPSILON = 1e-4 ) noexcept
  {
    return std::abs( lhs - rhs ) <= EPSILON;
  }

  bool read_comma( std::istream & stream )
  {
    char delimiter = '\0';

    if( stream >> std::ws >> delimiter  &&  delimiter == ',' ) return true;

    stream.setstate( std::ios::failbit );
    return false;
  }
}    // unnamed, anonymous namespace







/*******************************************************************************
**  Constructors, assignments, and destructor
*******************************************************************************/

// Default and Conversion Constructor
Book::Book( std::string title, std::string author, std::string isbn, double price )
  : _isbn( std::move( isbn ) ),
    _title( std::move( title ) ),
    _author( std::move( author ) ),
    _price( price )
{}




// Copy constructor
Book::Book( Book const & other )
    = default;




// Move constructor
Book::Book( Book && other ) noexcept
    = default;




// Copy Assignment Operator
Book & Book::operator=( Book const & rhs ) &
    = default;




// Move Assignment Operator
Book & Book::operator=( Book && rhs ) & noexcept
    = default;



// Destructor
Book::~Book() noexcept
    = default;








/*******************************************************************************
**  Accessors
*******************************************************************************/

// isbn() const
std::string const & Book::isbn() const &
{
  return _isbn;
}




// title() const
std::string const & Book::title() const &
{
  return _title;
}




// author() const
std::string const & Book::author() const &
{
  return _author;
}



// price() const
double Book::price() const &
{
  return _price;
}




// isbn()
std::string Book::isbn() &&
{
  return std::move( _isbn );
}




// title()
std::string Book::title() &&
{
  return std::move( _title );
}




// author()
std::string Book::author() &&
{
  return std::move( _author );
}








/*******************************************************************************
**  Modifiers
*******************************************************************************/

// isbn()
Book & Book::isbn( std::string newIsbn ) &
{
  _isbn = std::move( newIsbn );
  return *this;
}




// title()
Book & Book::title( std::string newTitle ) &
{
  _title = std::move( newTitle );
  return *this;
}




// author()
Book & Book::author( std::string newAuthor ) &
{
  _author = std::move( newAuthor );
  return *this;
}




// price()
Book & Book::price( double newPrice ) &
{
  _price = newPrice;
  return *this;
}








/*******************************************************************************
**  Relational Operators
*******************************************************************************/

// operator<=>
std::weak_ordering Book::operator<=>( const Book & rhs ) const noexcept
{
  // Design decision:  A very simple and convenient defaulted 3-way comparison operator
  //                         auto operator<=>( const Book & ) const = default;
  //                   in the class definition (header file) would get very close to what is needed and would allow both the <=> and
  //                   the == operators defined here to be skipped.  The physical ordering of the attributes in the class definition
  //                   would have to be changed (easy enough in this case) but the default directly compares floating point types
  //                   (price) for equality, and that should be avoided, in general. For example, if x and y are of type double,
  //                   then x < y is okay but x == y is not.  So these (operator<=> and operator==) explicit definitions are
  //                   provided.
  //
  //                   Also, many ordering (sorting) algorithms, like those used in std::map and std::set, require at least a weak
  //                   ordering of elements. operator<=> provides only a partial ordering when comparing floating point numbers.
  //
  // Weak order:       Objects that compare equal but are not substitutable (identical).  For example, since _price can be within
  //                   EPSILON, Book("Title", "Author", "ISBN", 9.99999) and Book("Title", "Author", "ISBN", 10.00001) are equal but
  //                   they are not identical.  If you ignore case when comparing strings, as another example, Book("Title") and
  //                   Book("title") are equal but they are not identical.
  //
  // See std::weak_ordering    at https://en.cppreference.com/w/cpp/utility/compare/weak_ordering and
  //     std::partial_ordering at https://en.cppreference.com/w/cpp/utility/compare/partial_ordering
  //     The Three-Way Comparison Operator at  http://modernescpp.com/index.php/c-20-the-three-way-comparison-operator
  //     Spaceship (Three way comparison) Operator Demystified https://youtu.be/S9ShnAFmiWM
  //
  //
  // Books are equal if all attributes are equal (or within Epsilon for floating point numbers, like price). Books are ordered
  // (sorted) by ISBN, author, title, then price.

  if( auto result = _isbn <=> rhs._isbn; result != 0 ) { return result; }
  if( auto result = _author <=> rhs._author; result != 0 ) { return result; }
  if( auto result = _title <=> rhs._title; result != 0 ) { return result; }
  if( floating_point_is_equal( _price, rhs._price ) ) { return std::weak_ordering::equivalent; }

  return _price < rhs._price ? std::weak_ordering::less : std::weak_ordering::greater;
}




// operator==
bool Book::operator==( const Book & rhs ) const noexcept
{
  // All attributes must be equal for the two books to be equal to the other.  This can be done in any order, so put the quickest
  // and then the most likely to be different first.

  return _isbn == rhs._isbn
      && _title == rhs._title
      && _author == rhs._author
      && floating_point_is_equal( _price, rhs._price );
}








/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/

// operator>>
std::istream & operator>>( std::istream & stream, Book & book )
{
  Book workingItem;

  if( stream >> std::ws >> std::quoted( workingItem._isbn )
      && read_comma( stream )
      && stream >> std::ws >> std::quoted( workingItem._title )
      && read_comma( stream )
      && stream >> std::ws >> std::quoted( workingItem._author )
      && read_comma( stream )
      && stream >> std::ws >> workingItem._price )
  {
    book = std::move( workingItem );
  }

  return stream;
}




// operator<<
std::ostream & operator<<( std::ostream & stream, const Book & book )
{
  const std::string delimiter = ", ";

  return stream << std::quoted( book.isbn() ) << delimiter
                << std::quoted( book.title() ) << delimiter
                << std::quoted( book.author() ) << delimiter
                << book.price();
}
