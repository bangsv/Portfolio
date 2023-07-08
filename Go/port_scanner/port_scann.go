package main

import (
	"fmt"
	"net"
	"strconv"
	"strings"
	"time"
)

const MAX_SIZE_PORTS = 65535

func Str_in_array(str string) []int {

	var array []int
	strs := strings.Split(str, ",")
	for _, s := range strs {
		num, err := strconv.Atoi(s)
		if err == nil {
			array = append(array, num)
		}
	}
	return array
}

func Out_info_port(open_ports []int) {
	fmt.Println("Scanning finished")
	if len(open_ports) == 0 {
		fmt.Println("No open ports")
		return
	} else if len(open_ports) == 1 {
		fmt.Println("Open port: ", open_ports[0])
	} else {
		fmt.Println("\nOpen ports: ")
		for i := 0; i < len(open_ports); i++ {
			if i == len(open_ports)-1 {
				fmt.Print(open_ports[i])
				break
			}
			fmt.Print(open_ports[i], ", ")
		}
	}
}

func Check_str_size(str string) string {
	if len(str) == 0 {
		panic("Error: Empty string")
	}
	if str[len(str)-1] != ':' {
		str += ":"
		return str
	}
	return ""
}

func ScanPort(port int, str_1 string, ch chan int) {
	str := str_1 + strconv.Itoa(port)
	conn, err := net.Dial("tcp", str)
	if err != nil {
		ch <- 0
		return
	}
	ch <- port
	conn.Close()
}

// Ellipsis - function for animation
// Example: Scanning...
func Ellipsis(str string) {
	fmt.Print(str)
	for {
		fmt.Print(".")
		time.Sleep(1 * time.Second)
		fmt.Print(".")
		time.Sleep(1 * time.Second)
		fmt.Print(".")
		time.Sleep(1 * time.Second)
		fmt.Print(".")
		fmt.Print("\b\b\b   \b\b\b\b")
	}
}

func main() {

	var max_port int
	var min_port int
	var specific_port []int
	var open_ports []int

	var answer int

	ch := make(chan int)
	fmt.Println("Write a website or ip:\nExample: scanme.nmap.org or 45.33.32.156")
	var str_site string
	fmt.Print("Enter the site: ")
	fmt.Scan(&str_site)
	str_site = Check_str_size(str_site)
	fmt.Print("Choose how you want to scan:\n1. Scan all ports (1-65535)\n2. Scan port range(20-25)\n3. Scan specific port (20,80,443, etc.)\nСhoice: ")
	fmt.Scan(&answer)

	if answer == 1 {
		go Ellipsis("Scanning")
		for i := 1; i <= MAX_SIZE_PORTS; i++ {
			go ScanPort(i, str_site, ch)
		}

		for i := min_port; i <= MAX_SIZE_PORTS; i++ {
			check := <-ch
			if check != 0 {
				open_ports = append(open_ports, check)
			}
		}
		fmt.Println()
	} else if answer == 2 {

		fmt.Println("Input port range:")
		fmt.Print("Enter the begin port: ")
		fmt.Scan(&min_port)
		fmt.Print("Enter the end port: ")
		fmt.Scan(&max_port)

		go Ellipsis("Scanning")
		for i := min_port; i <= max_port+1; i++ {
			go ScanPort(i, str_site, ch)
		}

		for i := min_port; i <= max_port+1; i++ {
			check := <-ch
			if check != 0 {
				open_ports = append(open_ports, check)
			}
		}

		fmt.Println()
	} else if answer == 3 {
		fmt.Println("Input specific port:")
		var str_port string
		fmt.Print("Enter the port: ")
		fmt.Scan(&str_port)

		specific_port = Str_in_array(str_port)

		go Ellipsis("Scanning")

		for i := 0; i < len(specific_port); i++ {
			go ScanPort(specific_port[i], str_site, ch)
		}

		for i := 0; i <= len(ch); i++ {
			check := <-ch
			if check != 0 {
				open_ports = append(open_ports, check)
			}
		}
		fmt.Println()
	}
	Out_info_port(open_ports)
}
