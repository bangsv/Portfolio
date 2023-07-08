package send_files

import (
	"io/ioutil"
	"mime"
	"net/http"
	"path/filepath"

	"github.com/gorilla/mux"
)

func ServeFile(w http.ResponseWriter, r *http.Request) { // Serve file from id variable
	vars := mux.Vars(r)              // Get variables from request
	id := vars["id"]                 // Get id from variables
	file, err := ioutil.ReadFile(id) // Read file from id variable
	if err != nil {
		http.Error(w, "404 not found", http.StatusNotFound) // If error return error
		return
	}
	contentType := mime.TypeByExtension(filepath.Ext(id)) // Get content type from id variable
	w.Header().Set("Content-Type", contentType)           // Set content type
	w.Write(file)                                         // Write file to response
}
