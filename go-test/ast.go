/*
 * @Author: your name
 * @Date: 2021-01-14 00:40:20
 * @LastEditTime: 2021-01-14 00:43:12
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /C-Study/go-test/ast.go
 */
package main

import "github.com/xiazemin/golang/ast/ast_graph/gen"

func main() {
	path := "/Users/didi/goLang/src/github.com/xiazemin/golang/ast/ast_graph/exp/main.go"
	dpath := "/Users/didi/goLang/src/github.com/xiazemin/golang/ast/ast_graph/"
	gen.GenSvg(path, dpath, "tree")
}
