#include <fstream>
#include <iostream>
#include <filesystem>
// TIME INCLUDES
#include <iostream>
#include <chrono>
#include <iomanip>
#include "filemanager.h"

using namespace std;

// Constructor
FileManager::FileManager(const string& booksFile, const string& usersFile, const string& logsFile)
    : booksFileName(booksFile), usersFileName(usersFile), logFileName(logsFile) {}

// Save all library data
bool FileManager::saveLibraryData(Library& library) {
    return saveBooksToFile(library) && saveUsersToFile(library);
}

// Load all library data
bool FileManager::loadLibraryData(Library& library) {
    bool booksLoaded = loadBooksFromFile(library);
    bool usersLoaded = loadUsersFromFile(library);
    return booksLoaded || usersLoaded; // Return true if at least one file was loaded
}

// Save books to file
bool FileManager::saveBooksToFile(Library& library) {
    ofstream file(booksFileName);
    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << booksFileName << " en écriture.\n";
        return false;
    }
    
    auto books = library.getAllBooks();
    for (Book* book : books) {
        file << book->toFileFormat() << "\n";
    }
    
    file.close();
    return true;
}

// Save users to file
bool FileManager::saveUsersToFile(Library& library) {
    ofstream file(usersFileName);
    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << usersFileName << " en écriture.\n";
        return false;
    }
    
    auto users = library.getAllUsers();
    for (User* user : users) {
        file << user->toFileFormat() << "\n";
    }
    
    file.close();
    return true;
}

// Load books from file
bool FileManager::loadBooksFromFile(Library& library) {
    ifstream file(booksFileName);
    if (!file.is_open()) {
        cout << "Aucun fichier de livres existant trouvé. Démarrage avec une bibliothèque vide.\n";
        return false;
    }
    
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty()) {
            Book book;
            book.fromFileFormat(line);
            library.addBook(book);
            count++;
        }
    }
    
    file.close();
    cout << "Chargé " << count << " livre(s) depuis le fichier.\n";
    return true;
}

// Load users from file
bool FileManager::loadUsersFromFile(Library& library) {
    ifstream file(usersFileName);
    if (!file.is_open()) {
        cout << "Aucun fichier d'utilisateurs existant trouvé. Démarrage sans utilisateurs enregistrés.\n";
        return false;
    }
    
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty()) {
            User user;
            user.fromFileFormat(line);
            library.addUser(user);
            count++;
        }
    }
    
    file.close();
    cout << "Chargé " << count << " utilisateur(s) depuis le fichier.\n";
    return true;
}

// Check if file exists
bool FileManager::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void FileManager::writeLogs(string action, User user) {
    stringstream ss;
    ss = readFile(logFileName);
    ofstream file(logFileName);
    // put old content
    file << ss.str();
    // put new content
    file << getCurrentTime() << " - [" << action << "] " << user.toFileFormat() << "\n";
    file.close();
}

void FileManager::writeLogs(string action, Book &book)
{
    stringstream ss;
    ss = readFile(logFileName);
    ofstream file(logFileName);
    // put old content
    file << ss.str();
    // put new content
    file << getCurrentTime() << " - [" << action << "] " << book.toFileFormat() << "\n";
    file.close();
}

void FileManager::writeLogs(string action)
{
    stringstream ss;
    ss = readFile(logFileName);
    ofstream file(logFileName);
    // put old content
    file << ss.str();
    // put new content
    file << getCurrentTime() << " - [" << action << "] " << "\n";
    file.close();
}

// reads the file, that way the information of the file stays safe
stringstream FileManager::readFile(string fileName) {
    ifstream file(fileName);

    string line;
    stringstream ss;
    while (getline(file, line)) {
        ss << line << '\n';
    }

    file.close();

    return ss;
}

// get the time right now
_Put_time<char> FileManager::getCurrentTime() {

    auto now = chrono::system_clock::now();

    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm* localTime = localtime(&currentTime);

    return put_time(localTime, "%Y-%m-%d %H:%M:%S");
}

// Create backup
void FileManager::createBackup() {
    if (fileExists(booksFileName)) {
        filesystem::copy_file(booksFileName, booksFileName + ".backup");
    }
    
    if (fileExists(usersFileName)) {
        filesystem::copy_file(usersFileName, usersFileName + ".backup");
    }
    
    cout << "Fichiers de sauvegarde créés.\n";
}