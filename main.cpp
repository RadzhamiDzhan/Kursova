#include <iostream>
#include <vector>
#include <string>

// Клас, що описує книгу
class Book {
public:
  std::string title;
  std::string author;
  std::string topic;
  bool isAvailable;

  Book(std::string t, std::string a, std::string tp, bool avail = true)
      : title(t), author(a), topic(tp), isAvailable(avail) {}

  void display() const {
      std::cout << "Title: " << title << ", Author: " << author
                << ", Topic: " << topic << ", Available: " << (isAvailable ? "Yes" : "No") << std::endl;
  }
};

// Клас, що описує читача
class Reader {
public:
  std::string name;
  std::vector<Book*> borrowedBooks;

  Reader(std::string n) : name(n) {}

  bool borrowBook(Book* book) {
      if (borrowedBooks.size() >= 10) {
          std::cout << "You cannot borrow more than 10 books." << std::endl;
          return false;
      }
      if (!book->isAvailable) {
          std::cout << "This book is currently unavailable." << std::endl;
          return false;
      }
      book->isAvailable = false;
      borrowedBooks.push_back(book);
      std::cout << "Book borrowed successfully." << std::endl;
      return true;
  }

  void returnBook(Book* book) {
      for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
          if (*it == book) {
              book->isAvailable = true;
              borrowedBooks.erase(it);
              std::cout << "Book returned successfully." << std::endl;
              return;
          }
      }
      std::cout << "This book was not borrowed by you." << std::endl;
  }

  void displayBorrowedBooks() const {
      std::cout << "Borrowed books:" << std::endl;
      for (const auto& book : borrowedBooks) {
          book->display();
      }
  }
};

// Клас, що описує бібліотеку
class Library {
public:
  std::vector<Book> books;
  std::vector<Reader> readers;

  void addBook(const Book& book) {
      books.push_back(book);
  }

  void addReader(const Reader& reader) {
      readers.push_back(reader);
  }

  Book* searchByTitle(const std::string& title) {
      for (auto& book : books) {
          if (book.title == title) {
              return &book;
          }
      }
      return nullptr;
  }

  Book* searchByAuthor(const std::string& author) {
      for (auto& book : books) {
          if (book.author == author) {
              return &book;
          }
      }
      return nullptr;
  }

  Book* searchByTopic(const std::string& topic) {
      for (auto& book : books) {
          if (book.topic == topic) {
              return &book;
          }
      }
      return nullptr;
  }
};

// Основний інтерфейс користувача
int main() {
  Library library;

  // Додаємо книги
  library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "Fiction"));
  library.addBook(Book("1984", "George Orwell", "Dystopian"));
  library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "Fiction"));
  library.addBook(Book("A Brief History of Time", "Stephen Hawking", "Science"));
  library.addBook(Book("The Art of Computer Programming", "Donald Knuth", "Computer Science"));
  library.addBook(Book("Clean Code", "Robert C. Martin", "Software Engineering"));
  library.addBook(Book("The Pragmatic Programmer", "Andrew Hunt", "David Thomas", "Software Engineering"));
  library.addBook(Book("Introduction to Algorithms", "Thomas H. Cormen", "Computer Science"));
  library.addBook(Book("Design Patterns", "Erich Gamma", "Software Engineering"));
  library.addBook(Book("The Catcher in the Rye", "J.D. Salinger", "Fiction"));
  library.addBook(Book("The Lord of the Rings", "J.R.R. Tolkien", "Fantasy"));
  library.addBook(Book("Pride and Prejudice", "Jane Austen", "Romance"));
  library.addBook(Book("War and Peace", "Leo Tolstoy", "Historical Fiction"));
  library.addBook(Book("The Brothers Karamazov", "Fyodor Dostoevsky", "Philosophy"));
  library.addBook(Book("One Hundred Years of Solitude", "Gabriel Garcia Marquez", "Magic Realism"));

  // Додаємо читачів
  Reader reader1("Alice");
  Reader reader2("Bob");
  library.addReader(reader1);
  library.addReader(reader2);

  int choice;
  std::string searchQuery;

  while (true) {
      std::cout << "\nLibrary System Menu:\n";
      std::cout << "1. Search by title\n";
      std::cout << "2. Search by author\n";
      std::cout << "3. Search by topic\n";
      std::cout << "4. Borrow book\n";
      std::cout << "5. Return book\n";
      std::cout << "6. Display borrowed books\n";
      std::cout << "7. Exit\n";
      std::cout << "Enter your choice: ";
      std::cin >> choice;

      if (choice == 7) break;
      switch (choice) {
          case 1:
              std::cout << "Enter the title: ";
              std::cin.ignore();
              std::getline(std::cin, searchQuery);
              if (Book* book = library.searchByTitle(searchQuery)) {
                  book->display();
              } else {
                  std::cout << "Book not found." << std::endl;
              }
              break;
          case 2:
              std::cout << "Enter the author: ";
              std::cin.ignore();
              std::getline(std::cin, searchQuery);
              if (Book* book = library.searchByAuthor(searchQuery)) {
                  book->display();
              } else {
                  std::cout << "Book not found." << std::endl;
              }
              break;
          case 3:
              std::cout << "Enter the topic: ";
              std::cin.ignore();
              std::getline(std::cin, searchQuery);
              if (Book* book = library.searchByTopic(searchQuery)) {
                  book->display();
              } else {
                  std::cout << "Book not found." << std::endl;
              }
              break;
          case 4:
              std::cout << "Enter your name: ";
              std::cin.ignore();
              std::getline(std::cin, searchQuery);
              for (Reader& reader : library.readers) {
                  if (reader.name == searchQuery) {
                      std::cout << "Enter the title of the book to borrow: ";
                      std::getline(std::cin, searchQuery);
                      if (Book* book = library.searchByTitle(searchQuery)) {
                          reader.borrowBook(book);
                      } else {
                          std::cout << "Book not found." << std::endl;
                      }
                      break;
                  }
              }
              break;
          case 5:
              std::cout << "Enter your name: ";
              std::cin.ignore();
              std::getline(std::cin, searchQuery);
              for (Reader& reader : library.readers) {
                  if (reader.name == searchQuery) {
                      std::cout << "Enter the title of the book to return: ";
                      std::getline(std::cin, searchQuery);
                      if (Book* book = library.searchByTitle(searchQuery)) {
                          reader.returnBook(book);
                      } else {
                          std::cout << "Book not found." << std::endl;
                      }
                      break;
                  }
              }
              break;
          case 6:
              std::cout << "Enter your name: ";
              std::cin.ignore();
              std::getline(std::cin, searchQuery);
              for (const Reader& reader : library.readers) {
                  if (reader.name == searchQuery) {
                      reader.displayBorrowedBooks();
                      break;
                  }
              }
              break;
          default:
              std::cout << "Invalid choice. Please try again." << std::endl;
      }
  }

  return 0;
}