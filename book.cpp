#include "book.h"
#include <iostream>
#include <sstream>

Book::Book()
{
}

Book::Book(const string &title, const string &author, const string &isbn)
{
    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->isAvailable = true;
}

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

string Book::getISBN() const
{
    return isbn;
}

bool Book::getAvailability() const
{
    return isAvailable;
}

string Book::getBorrowerId() const
{
    return borrowerId;
}

void Book::setTitle(const string &title)
{
    this->title = title;
}

void Book::setAuthor(const string &author)
{
    this->author = author;
}

void Book::setISBN(const string &isbn)
{
    this->isbn = isbn;
}

void Book::setAvailability(bool available)
{
    this->isAvailable = available;
}

void Book::setBorrowerId(const string &id)
{
    this->borrowerId = id;
}

// checks out the book
void Book::checkOut(const string &borrowerId)
{
    this->borrowerId = borrowerId;
    this->isAvailable = false;
}

// returns the book, makes it available
void Book::returnBook()
{
    this->borrowerId.clear();
    this->isAvailable = true;
}

// prints the details of the book
string Book::toString() const
{
    
    // using stringstream to save multiple string to one variable
    std::stringstream ss;
    ss << "Titre: " << getTitle() << "\n"
    << "Auteur: " << getAuthor() << "\n"
    << "ISBN: " << getISBN() << "\n"
    << "Statu: " << getAvailability() << "\n";

    return ss.str();
}

string Book::toFileFormat() const
{
    return string();
}

void Book::fromFileFormat(const string &line)
{
}
