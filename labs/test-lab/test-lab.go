package main

import (
	"errors"
	"fmt"
	"os"
)

func getName() error{
	if len(os.Args) > 1{
		for i, val := range os.Args {
			if i == 0{
				continue
			}
			fmt.Printf("%s ", string(val))
		}
		fmt.Print("Welcome to the jungle\n")
	}else{
		return errors.New("no argument given")
	}
	return nil
}

func main() {
	err := getName()
	if err != nil{
	}
}
