/*
 * @Author: your name
 * @Date: 2021-01-13 14:26:42
 * @LastEditTime: 2021-01-15 15:22:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /C-Study/goParsetest.go
 */
package main

import (
	"errors"
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"
	"reflect"
	"strconv"
	"strings"
)

func Eval(exp ast.Expr, vars map[string]interface{}) interface{} {
	switch exp := exp.(type) {
	case *ast.BinaryExpr:
		return EvalBinaryExpr(exp, vars)
	case *ast.ParenExpr:
		return Eval(exp.X, vars)
	case *ast.CallExpr:
		EvalCallExpr(exp, vars)
	case *ast.UnaryExpr:
		return EvalUnaryExpr(exp, vars)

		// case *ast.

	case *ast.BasicLit:
		switch exp.Kind {
		case token.INT:
			value, _ := strconv.ParseInt(exp.Value, 10, 64)
			return value
		case token.FLOAT:
			f, _ := strconv.ParseFloat(exp.Value, 64)
			return f
		case token.STRING:
			return exp.Value
		case token.CHAR:
			return exp.Value
		default:
			value, _ := strconv.ParseInt(exp.Value, 64, 64)
			return value
		}

	case *ast.Ident:
		return vars[exp.Name]
	}
	return false
}
func EvalCallExpr(exp *ast.CallExpr, vars map[string]interface{}) bool {
	in := make([]interface{}, len(exp.Args))

	for k, param := range exp.Args {
		in[k] = Eval(param, vars)
	}

	var result []reflect.Value
	switch len(in) {
	case 1:
		result, _ = Call(vars, exp.Fun.(*ast.Ident).Name, in[0])
	case 2:
		result, _ = Call(vars, exp.Fun.(*ast.Ident).Name, in[0], in[1])
	case 3:
		result, _ = Call(vars, exp.Fun.(*ast.Ident).Name, in[0], in[1], in[2])
	case 4:
		result, _ = Call(vars, exp.Fun.(*ast.Ident).Name, in[0], in[1], in[2], in[3])
	}

	return result[0].Bool()
}
func EvalUnaryExpr(exp *ast.UnaryExpr, vars map[string]interface{}) bool {
	switch exp.Op {
	case token.NOT:
		return !(Eval(exp.X, vars).(bool))
	}
	return !(Eval(exp.X, vars).(bool))
}
func EvalBinaryExpr(exp *ast.BinaryExpr, vars map[string]interface{}) bool {

	switch exp.Op {
	case token.LAND:
		return Eval(exp.X, vars).(bool) && Eval(exp.Y, vars).(bool)
	case token.LOR:
		return Eval(exp.X, vars).(bool) || Eval(exp.Y, vars).(bool)
	case token.EQL:
		lf := Eval(exp.Y, vars)
		lfValue := reflect.ValueOf(&lf).Elem()
		switch lfValue.Kind() {
		case reflect.Int, reflect.Int8, reflect.Int16,
			reflect.Int32, reflect.Int64:
			return Eval(exp.X, vars).(int64) == lfValue.Int()
		case reflect.Float32, reflect.Float64:
			return Eval(exp.X, vars).(float64) == Eval(exp.Y, vars).(float64)
		case reflect.String:
			return Eval(exp.X, vars).(string) == Eval(exp.Y, vars).(string)
		}
	case token.NEQ:
		lf := Eval(exp.Y, vars)
		switch lf.(type) {
		case int64:
			return Eval(exp.X, vars).(int64) != Eval(exp.Y, vars).(int64)
		case float64:
			return Eval(exp.X, vars).(float64) != Eval(exp.Y, vars).(float64)
		case string:
			return Eval(exp.X, vars).(string) != Eval(exp.Y, vars).(string)
		}
	case token.LEQ:
		lf := Eval(exp.Y, vars)
		switch lf.(type) {
		case int64:
			return Eval(exp.X, vars).(int64) <= Eval(exp.Y, vars).(int64)
		case float64:
			return Eval(exp.X, vars).(float64) <= Eval(exp.Y, vars).(float64)
		case string:
			return Eval(exp.X, vars).(string) <= Eval(exp.Y, vars).(string)
		}
	case token.GEQ:
		lf := Eval(exp.Y, vars)
		switch lf.(type) {
		case int64:
			return Eval(exp.X, vars).(int64) >= Eval(exp.Y, vars).(int64)
		case float64:
			return Eval(exp.X, vars).(float64) >= Eval(exp.Y, vars).(float64)
		case string:
			return Eval(exp.X, vars).(string) >= Eval(exp.Y, vars).(string)
		}
	case token.LSS:
		lf := Eval(exp.Y, vars)
		switch lf.(type) {
		case int64:
			return Eval(exp.X, vars).(int64) < Eval(exp.Y, vars).(int64)
		case float64:
			return Eval(exp.X, vars).(float64) < Eval(exp.Y, vars).(float64)
		case string:
			return Eval(exp.X, vars).(string) < Eval(exp.Y, vars).(string)
		}
	case token.GTR:
		lf := Eval(exp.Y, vars)
		switch lf.(type) {
		case int64:
			return Eval(exp.X, vars).(int64) > Eval(exp.Y, vars).(int64)
		case float64:
			return Eval(exp.X, vars).(float64) > Eval(exp.Y, vars).(float64)
		case string:
			return Eval(exp.X, vars).(string) > Eval(exp.Y, vars).(string)
		}
	}
	return false
}

func Call(m map[string]interface{}, name string, params ...interface{}) (result []reflect.Value, err error) {

	f := reflect.ValueOf(m[name])
	if len(params) != f.Type().NumIn() {
		err = errors.New("The number of params is not adapted.")
		return
	}
	in := make([]reflect.Value, len(params))

	for k, param := range params {
		in[k] = reflect.ValueOf(param)
	}
	result = f.Call(in)
	return

}
func isList(lists []int64, item int64) bool {
	for _, value := range lists {
		if value == item {
			return true
		}
	}
	return false
}
func main() {
	// B站 规则引擎 实现 用栈实现 树的遍历，在进入退出时 用栈可以保存好新建对应的树

	orderRuleExp := "area > 0 and (driver_product_temp == 1 or driver_product_temp == 2 or driver_product_temp != 15) and isList(passList,2)"
	orderRuleExp = strings.Replace(orderRuleExp, " and ", " && ", -1)
	orderRuleExp = strings.Replace(orderRuleExp, " or ", " || ", -1)

	// fset := token.NewFileSet()
	exprAst, err := parser.ParseExpr(orderRuleExp)
	if err != nil {
		fmt.Println(err)
		return
	}
	varMap := map[string]interface{}{"area": int64(2), "driver_product_temp": int64(2), "isList": isList, "passList": []int64{int64(12), int64(32)}}
	// funcMap := map[string]interface{}{"isList": isList}
	fmt.Println(Eval(exprAst, varMap))

	// ast.Print(fset, exprAst)
}
