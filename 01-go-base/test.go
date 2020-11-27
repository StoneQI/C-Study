package main

import "fmt"

type Intapp interface {
	add()
}
type set struct {
	a int
}

func (c *set) add() {
	c.a++
}
func Intadd(data Intapp) {
	data.add()
}

func main() {

	a := &set{a: 1}
	fmt.Println(a)
	Intadd(a)
	fmt.Println(a)
	// http.HandleFunc("/", func(w http.ResponseWriter,

	// http.ListenAndServe(":8080", nil)
}
