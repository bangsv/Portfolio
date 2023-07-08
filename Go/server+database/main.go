package main

import (
	"database/sql" // Import database/sql package for database access functions
	"fmt"          // Import fmt package for formatted I/O functions
	"html/template"
	"log"      // Import log package for logging functions
	"net/http" // Import net/http package for web server functions
	"strconv"  // Import strconv package for string conversion functions

	// Import time package for time functions
	"github.com/gorilla/mux"
	_ "github.com/mattn/go-sqlite3" // Import go-sqlite3 library

	handle "test/functions/handle_func" // Import functions package for functions // HandleRegistr // HandlerPost // checkDatabasy
	out "test/functions/output"         // Import functions package for functions
	send "test/functions/send_files"    // Import functions package for functions // ServeImage // ServeCSS // ServeJS
)

func main() {

	router := mux.NewRouter()
	http.HandleFunc("/home", mainHandle) // Handle web server request

	router.HandleFunc("/{id:.+}", send.ServeFile) // Handle web server request

	port := ":9090" // Port to listen on

	http.HandleFunc("/login", handle.HandleLogin) // Handle web server request
	http.HandleFunc("/registration", handle.HandleRegistr)
	http.HandleFunc("/admin", checkDatabasy) // Handle web server request
	http.HandleFunc("/loading", handle.HandlerLoading)
	http.HandleFunc("/chat", handle.HandlerChat) // not work

	http.HandleFunc("/postlogin", handle.HandlerPostLogin) // За счет этого идет переадрисация на (postform) другую страницу после регистрации
	http.HandleFunc("/postregister", handle.HandlerPostRegister)

	http.Handle("/", router) // Handle web server request

	fmt.Println("Server is running on port 9090") // Print Server is running on port 9090
	go out.Ellipsis("Server is running")          // Print Server is running with ellipsis

	err := http.ListenAndServe(port, nil) // Start web server on port 9090 // If error return err

	if err != nil { // If error
		log.Fatal("Error starting server: ", err) // If error panic and stop program
		return
	}

}

func mainHandle(w http.ResponseWriter, r *http.Request) { // Handle web server request

	httpPars, err := template.ParseFiles("visit_site/index.html") // Parse registr.html file

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}

	httpPars.Execute(w, nil) // Execute registr.html file

}

func checkDatabasy(w http.ResponseWriter, r *http.Request) { // Check databasy
	database, err := sql.Open("sqlite3", "./databasy/databasy.db") // Open database file // If not exists create file databasy.db // If exists open file databasy.db

	if err != nil { // If error
		panic(err) // If error panic and stop program
	}

	statement, _ := database.Prepare("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)") // Prepare SQL Statement // If not exists create table people with id, firstname, lastname, age  // INTEGER PRIMARY KEY is auto incrementing integer // TEXT is string
	statement.Exec()                                                                                                            // Execute SQL Statement

	rows, _ := database.Query("SELECT id, username, password FROM users") // Prepare SQL Statement // Select from table users id, firstname, lastname, age

	var id int // Declare variables for id, firstname, lastname, age
	var firstname string
	var lastname string

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}
	w.Write([]byte("ID\t\tUserName\t\tPassword\n")) // Write id, firstname, lastname, age to web browser
	for rows.Next() {                               // Loop through rows
		rows.Scan(&id, &firstname, &lastname)                                        // Scan row and assign to variables
		w.Write([]byte(strconv.Itoa(id) + "\t\t" + firstname + "\t\t\t" + lastname)) // Write id, firstname, lastname, age to web browser
		w.Write([]byte("\n"))                                                        // Write new line to web browser
	}

}
