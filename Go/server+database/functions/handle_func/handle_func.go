package handlefunc

import (
	"database/sql"
	"net/http"
	"text/template"
)

// Доработай потом уже, чтобы сервак не крашился а выходил на mainPage
func HandleLogin(w http.ResponseWriter, r *http.Request) { // Handle web server request

	httpPars, err := template.ParseFiles("./log_for_sysytem/index.html") // Parse registr.html file

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}

	error := r.URL.Query().Get("error")
	if error == "true" {
		data := struct{ Error string }{"true"}
		httpPars.Execute(w, data)
	} else {
		httpPars.Execute(w, nil)
	}

}

func HandleRegistr(w http.ResponseWriter, r *http.Request) { // Handle web server request

	httpPars, err := template.ParseFiles("./reg_for_system/index.html") // Parse registr.html file

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}

	error := r.URL.Query().Get("error")
	if error == "true" {
		data := struct{ Error string }{"true"}
		httpPars.Execute(w, data)
	} else if error == "false" {
		data := struct{ Error string }{"false"}
		httpPars.Execute(w, data)
	} else {
		httpPars.Execute(w, nil)
	}

}

func HandlerPostLogin(w http.ResponseWriter, r *http.Request) { // Handle web server request

	r.ParseForm() // Parse form data

	name := r.FormValue("name") // Get form value

	password := r.FormValue("pass") // Get form value

	database, err := sql.Open("sqlite3", "./databasy/databasy.db") // Open database

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}
	defer database.Close() // Close database

	//check name in database
	var nameExist string
	err = database.QueryRow("SELECT username FROM users WHERE username = ? AND password = ?", name, password).Scan(&nameExist)
	if err != nil {
		if err == sql.ErrNoRows {
			http.Redirect(w, r, "/login?error=true", http.StatusSeeOther)
			return
		} else {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
	} else {
		http.Redirect(w, r, "/loading", http.StatusSeeOther)
		return
	}

}

func HandlerPostRegister(w http.ResponseWriter, r *http.Request) { // Handle web server request

	r.ParseForm() // Parse form data

	regname := r.FormValue("regname")            // Get form value
	regpassword := r.FormValue("regpass")        // Get form value
	checkregpassword := r.FormValue("reregpass") // Get form value

	if regpassword != checkregpassword { // If password not equal
		http.Redirect(w, r, "/registration?error=true", http.StatusSeeOther)
		return
	}

	database, err := sql.Open("sqlite3", "./databasy/databasy.db") // Open database

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}
	defer database.Close() // Close database

	//check name in database
	var nameExist string
	err = database.QueryRow("SELECT username FROM users WHERE username = ?", regname).Scan(&nameExist)
	if err != nil {
		if err == sql.ErrNoRows {
			_, err = database.Exec("INSERT INTO users (username, password) VALUES (?, ?)", regname, regpassword)
			if err != nil {
				http.Error(w, err.Error(), http.StatusInternalServerError)
				return
			}
			http.Redirect(w, r, "/loading", http.StatusSeeOther)
			return
		} else {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
	} else {
		http.Redirect(w, r, "/registration?error=false", http.StatusSeeOther)
		return
	}

}

func HandlerLoading(w http.ResponseWriter, r *http.Request) { // Handle web server request

	HtmlSend, err := template.ParseFiles("./loading_page/dist/index.html") // Parse registr.html file

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}

	HtmlSend.Execute(w, nil) // Execute registr.html file
	http.Redirect(w, r, "/chat", http.StatusSeeOther)
}

func HandlerChat(w http.ResponseWriter, r *http.Request) { // Handle web server request

	httpPars, err := template.ParseFiles("./chat_page/dist/index.html") // Parse registr.html file

	if err != nil { // If error
		http.Error(w, err.Error(), http.StatusInternalServerError) // If error return error
		return
	}

	httpPars.Execute(w, nil) // Execute registr.html file
}
