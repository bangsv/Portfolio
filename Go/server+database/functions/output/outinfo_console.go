package output

import (
	"fmt"
	"time"
)

func Ellipsis(str string) { // Print str with ellipsis
	fmt.Print(str) // Print str
	for {          // Loop forever
		fmt.Print(".")              // Print ellipsis
		time.Sleep(1 * time.Second) // Sleep for 1 second
		fmt.Print(".")
		time.Sleep(1 * time.Second)
		fmt.Print(".")
		time.Sleep(1 * time.Second)
		fmt.Print(".")
		fmt.Print("\b\b\b   \b\b\b\b")
	}
}
