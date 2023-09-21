# Password Manager Application

This is a simple command-line password manager application written in C++. It allows you to securely store and manage your passwords for different apps and websites. The passwords are encrypted before being stored in a MySQL database.

## Features

- Create a new password entry.
- Search for a password by app or website name.
- Update a password.
- Delete a password entry.
- View all stored passwords.
- Delete the entire account and all stored passwords.

## Prerequisites

Before you can run this application, you need to have the following:

- MySQL server installed and running.
- MySQL C++ Connector library installed.
- C++ development environment.

## Installation

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/yourusername/password-manager.git
   ```

2. Create a MySQL database and update the database configuration in `main.cpp`:

   ```cpp
   conn = mysql_real_connect(conn, "localhost", "username", "password", "your_database_name", 3306, NULL, 0);
   ```

3. Compile the application:

   ```bash
   g++ main.cpp -o password-manager -lmysqlcppconn
   ```

4. Run the application:

   ```bash
   ./password-manager
   ```

## Usage

Follow the on-screen menu to perform various actions, including adding, searching, updating, and deleting password entries.

**Note:** Ensure that you remember your secret username/password as it will be required to access your passwords.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This application uses the MySQL C++ Connector library.
- Encryption and decryption functions are provided by custom algorithms.
- ASCII art provided by `asciiart.h`.

Please feel free to customize and improve this password manager according to your needs.
