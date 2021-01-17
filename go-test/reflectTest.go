/*
 * @Author: your name
 * @Date: 2021-01-15 11:41:19
 * @LastEditTime: 2021-01-15 11:47:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /C-Study/go-test/reflectTest.go
 */
package main

import (
	"fmt"
	"reflect"
)

func main() {
	author := "draven"
	type1 := reflect.TypeOf(author)
	// a := reflect.String
	value1 := reflect.ValueOf(author)
	fmt.Println("TypeOf author:", type1)
	fmt.Println("ValueOf author:", value1)

	i := 1
	v := reflect.ValueOf(&i)
	v.Elem().SetInt(10)

	fmt.Println(i)

}
