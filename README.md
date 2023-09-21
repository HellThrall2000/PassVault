# Password Manager Application

This is a simple command-line password manager application written in C++. It allows you to securely store and manage your passwords for different apps and websites. The passwords are encrypted before being stored in a MySQL database. It is fully CRUD enabled.

## Features

### 1. Create a New Password Entry

```cpp
case 1:
{
    // Input app, emailid, and password
    cout << "Enter app/site name: ";
    cin >> app;
    cout << "Enter emailid used: ";
    cin >> emailid;
    cout << "Enter password to be saved: ";
    cin >> pass;

    // Encrypt the password
    pass = encryptor(pass, key);

    // Insert the entry into the database
    query = "INSERT INTO " + user + " VALUES ( '" + app + "', '" + emailid + "', '" + pass + "'); ";
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate) {
        if (mysql_affected_rows(conn)) {
            cout << "Password details added";
        }
    }
    else {
        cout << "Query failed: " << mysql_error(conn) << endl;
    }
}
break;
```

### 2. Search for a Password

```cpp
case 2:
{
    string name_search;
    string query2 = "";
    cout << "Enter app/site name: ";
    cin >> name_search;
    query2 = "SELECT * FROM " + user + " WHERE app = ('" + name_search + "'); ";
    const char* q1 = query2.c_str();
    qstate = mysql_query(conn, q1);

    if (!qstate) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            cout << "App/Website:" << row[0] << "\tE-mail ID:" << row[1] << "\tPassword:" << decryptor(row[2], key) << "\n";
        }
    }
    else {
        cout << "Query failed: " << mysql_error(conn) << endl;
    }
}
break;
```

### 3. Update a Password

```cpp
case 3:
{
    string name_search;
    string new_pass;
    string query2 = "";
    cout << "Enter app/site name: ";
    cin >> name_search;

    cout << "Enter new password";
    cin >> new_pass;

    query2 = "UPDATE " + user + " SET pass ='" + encryptor(new_pass, key) + "'  WHERE app = '" + name_search + "' ;";
    const char* q1 = query2.c_str();
    qstate = mysql_query(conn, q1);

    if (!qstate) {
        if (mysql_affected_rows(conn)) {
            cout << "Updated password";
        }
    }
    else {
        cout << "Query failed: " << mysql_error(conn) << endl;
    }
}
break;
```

### 4. Delete a Password Entry

```cpp
case 4:
{
    string name_search;
    string query2 = "";
    cout << "Enter app/website entry to be removed: ";
    cin >> name_search;
    query2 = "DELETE from " + user + " WHERE app ='" + name_search + "' ;";
    const char* q1 = query2.c_str();
    qstate = mysql_query(conn, q1);

    if (!qstate) {
        if (mysql_affected_rows(conn)) {
            cout << "Deleted password entry";
        }
    }
    else {
        cout << "Query failed: " << mysql_error(conn) << endl;
    }
}
break;
```

### 5. View All Stored Passwords

```cpp
case 5:
{
    string query = "SELECT * FROM " + user;
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            cout << "App/Website:" << row[0] << "\tE-mail ID:" << row[1] << "\tPassword:" << decryptor(row[2], key) << "\n";
        }
    }
    else {
        cout << "Query failed: " << mysql_error(conn) << endl;
    }
}
break;
```

### 6. Delete Account and All Passwords

```cpp
case 6:
{
    query = "DROP TABLE " + user + ";";
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate) {
        del();
        if (mysql_affected_rows(conn)) {
            exit;
        }
    }
    else {
        cout << "Query failed: " << mysql_error(conn) << endl;
    }
}
break;
```

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
