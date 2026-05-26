#pragma once
#include <algorithm>
#include <cstddef>
#include <forward_list>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "Book.hpp"









/***********************************************************************************************************************************
**  Insert operations
***********************************************************************************************************************************/
struct insert_at_back_of_vector
{
  // Function takes a constant Book as a parameter, inserts that book at the back of a vector, and returns nothing.
  void operator()( const Book & book )
  {
    my_vector.push_back( book );
  }

  std::vector<Book> & my_vector;
};



struct insert_at_back_of_dll
{
  // Function takes a constant Book as a parameter, inserts that book at the back of a doubly linked list, and returns nothing.
  void operator()( const Book & book )
  {
    my_dll.push_back( book );
  }

  std::list<Book> & my_dll;  // doubly linked list
};



struct insert_at_back_of_sll
{
  // Function takes a constant Book as a parameter, inserts that book at the back of a singly linked list, and returns nothing.
  void operator()( const Book & book )
  {
    auto position = my_sll.before_begin();
    for( auto current = my_sll.begin(); current != my_sll.end(); ++current ) position = current;

    my_sll.insert_after( position, book );
  }

  std::forward_list<Book> & my_sll;  // singly linked list
};



struct insert_at_front_of_vector
{
  // Function takes a constant Book as a parameter, inserts that book at the front of a vector, and returns nothing.
  void operator()( const Book & book )
  {
    my_vector.insert( my_vector.begin(), book );
  }

  std::vector<Book> & my_vector;
};



struct insert_at_front_of_dll
{
  // Function takes a constant Book as a parameter, inserts that book at the front of a doubly linked list, and returns nothing.
  void operator()( const Book & book )
  {
    my_dll.push_front( book );
  }

  std::list<Book> & my_dll;  // doubly linked list
};



struct insert_at_front_of_sll
{
  // Function takes a constant Book as a parameter, inserts that book at the front of a singly linked list, and returns nothing.
  void operator()( const Book & book )
  {
    my_sll.push_front( book );
  }

  std::forward_list<Book> & my_sll;  // doubly linked list
};



struct insert_into_bst
{
  // Function takes a constant Book as a parameter, inserts that book indexed by the book's ISBN into a binary search tree, and
  // returns nothing.
  void operator()( const Book & book )
  {
    my_bst.emplace( book.isbn(), book );
  }

  std::map<std::string, Book> & my_bst;    // binary search tree
};



struct insert_into_hash_table
{
  // Function takes a constant Book as a parameter, inserts that book indexed by the book's ISBN into a hash table, and returns
  // nothing.
  void operator()( const Book & book )
  {
    my_hash_table.emplace( book.isbn(), book );
  }

  std::unordered_map<std::string, Book> & my_hash_table;
};









/***********************************************************************************************************************************
**  Remove operations
***********************************************************************************************************************************/
struct remove_from_back_of_vector
{
  // Function takes no parameters, removes the book at the back of a vector, and returns nothing.
  void operator()( const auto & )
  {
    if( !my_vector.empty() ) my_vector.pop_back();
  }

  std::vector<Book> & my_vector;
};



struct remove_from_back_of_dll
{
  // Function takes no parameters, removes the book at the back of a doubly linked list, and returns nothing.
  void operator()( const auto & )
  {
    if( !my_dll.empty() ) my_dll.pop_back();
  }

  std::list<Book> & my_dll;  // doubly linked list
};



struct remove_from_back_of_sll
{
  // Function takes no parameters, removes the book at the back of a singly linked list, and returns nothing.
  void operator()( const auto & )
  {
    if( my_sll.empty() ) return;

    auto predecessor = my_sll.before_begin();
    for( auto current = my_sll.begin(); current != my_sll.end(); ++current )
    {
      auto next = current;
      ++next;
      if( next == my_sll.end() ) break;

      ++predecessor;
    }

    my_sll.erase_after( predecessor );
  }

  std::forward_list<Book> & my_sll;  // singly linked list
};



struct remove_from_front_of_vector
{
  // Function takes no parameters, removes the book at the front of a vector, and returns nothing.
  void operator()( const auto & )
  {
    if( !my_vector.empty() ) my_vector.erase( my_vector.begin() );
  }

  std::vector<Book> & my_vector;
};



struct remove_from_front_of_dll
{
  // Function takes no parameters, removes the book at the front of a doubly linked list, and returns nothing.
  void operator()( const auto & )
  {
    if( !my_dll.empty() ) my_dll.pop_front();
  }

  std::list<Book> & my_dll;
};



struct remove_from_front_of_sll
{
  // Function takes no parameters, removes the book at the front of a singly linked list, and returns nothing.
  void operator()( const auto & )
  {
    if( !my_sll.empty() ) my_sll.pop_front();
  }

  std::forward_list<Book> & my_sll;
};



struct remove_from_bst
{
  // Function takes a constant Book as a parameter, finds and removes from the binary search tree the book with a matching ISBN, and
  // returns nothing.
  void operator()( const Book & book )
  {
    my_bst.erase( book.isbn() );
  }

  std::map<std::string, Book> & my_bst;    // binary search tree
};



struct remove_from_hash_table
{
  // Function takes a constant Book as a parameter, finds and removes from the hash table the book with a matching ISBN, and returns
  // nothing.
  void operator()( const Book & book )
  {
    my_hash_table.erase( book.isbn() );
  }

  std::unordered_map<std::string, Book> & my_hash_table;
};









/***********************************************************************************************************************************
**  Search operations
***********************************************************************************************************************************/
struct search_within_vector
{
  // Function takes no parameters, searches a vector for a book with an ISBN matching the target ISBN, and returns a pointer to that
  // found book if such a book is found, nullptr otherwise.
  Book * operator()( const auto & )
  {
    auto match = std::find_if( my_vector.begin(), my_vector.end(), [&]( const Book & book )
    {
      return book.isbn() == target_isbn;
    } );

    return match == my_vector.end() ? nullptr : &*match;
  }

  std::vector<Book> & my_vector;
  const std::string   target_isbn;
};



struct search_within_dll
{
  // Function takes no parameters, searches a doubly linked list for a book with an ISBN matching the target ISBN, and returns a
  // pointer to that found book if such a book is found, nullptr otherwise.
  Book * operator()( const auto & )
  {
    auto match = std::find_if( my_dll.begin(), my_dll.end(), [&]( const Book & book )
    {
      return book.isbn() == target_isbn;
    } );

    return match == my_dll.end() ? nullptr : &*match;
  }

  std::list<Book>   & my_dll;
  const std::string   target_isbn;
};



struct search_within_sll
{
  // Function takes no parameters, searches a singly linked list for a book with an ISBN matching the target ISBN, and returns a
  // pointer to that found book if such a book is found, nullptr otherwise.
  Book * operator()( const auto & )
  {
    auto match = std::find_if( my_sll.begin(), my_sll.end(), [&]( const Book & book )
    {
      return book.isbn() == target_isbn;
    } );

    return match == my_sll.end() ? nullptr : &*match;
  }

  std::forward_list<Book> & my_sll;
  const std::string         target_isbn;
};



struct search_within_bst
{
  // Function takes no parameters, searches a binary search tree for a book with an ISBN matching the target ISBN, and returns a
  // pointer to that found book if such a book is found, nullptr otherwise.
  Book * operator()( const auto & )
  {
    auto match = my_bst.find( target_isbn );
    return match == my_bst.end() ? nullptr : &match->second;
  }

  std::map<std::string, Book> & my_bst;
  const std::string             target_isbn;
};



struct search_within_hash_table
{
  // Function takes no parameters, searches a hash table for a book with an ISBN matching the target ISBN, and returns a pointer to
  // that found book if such a book is found, nullptr otherwise.
  Book * operator()( const auto & )
  {
    auto match = my_hash_table.find( target_isbn );
    return match == my_hash_table.end() ? nullptr : &match->second;
  }

  std::unordered_map<std::string, Book> & my_hash_table;
  const std::string                       target_isbn;
};
