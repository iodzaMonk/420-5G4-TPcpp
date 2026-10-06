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
    // stringstream to easily format the one line cleanly
    std::stringstream ss;
    ss << getTitle() << "|" << getAuthor() << "|" << getISBN() << 
    "|" << getAvailability() << "|" << getBorrowerId();
    return ss.str();
}

void Book::fromFileFormat(const string &line)
{
    // clear all the values first before repopulating them back
    this->title.clear();
    this->author.clear();
    this->isbn.clear();
    this->borrowerId.clear();

    // counter to track which field to populate
    int counter = 0;
    for (char c : line) {
        if (c == '|') {
            counter++;
        } else {
            switch (counter)
            {
            case 0:
                setTitle(getTitle() + c);
                break;
            
            case 1:
                setAuthor(getAuthor() + c);
                break;

            case 2:
                setISBN(getISBN() + c);
                break;

            case 3:
                if (c == '0') {
                    setAvailability(false);
                } else {
                    setAvailability(true);
                }
                break;

            case 4:
                setBorrowerId(getBorrowerId() + c);
                break;
            default:
                break;
            }
        }
    }
}