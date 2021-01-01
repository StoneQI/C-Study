package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"net/http"
	"sync"
)

func Run(searchTerm string) {
	// 获取需要搜索的数据源列表

	feeds := []string{"111", "222", "3333", "4444"}
	results := make(chan string)
	// 构造一个 waitGroup，以便处理所有的数据源
	var waitGroup sync.WaitGroup
	// 设置需要等待处理
	// 每个数据源的 goroutine 的数量
	waitGroup.Add(len(feeds))
	// 为每个数据源启动一个 goroutine 来查找结果
	for _, feed := range feeds {
		// 获取一个匹配器用于查找
		// 启动一个 goroutine 来执行搜索
		go func(feed string) {
			fmt.Printf(feed)
			waitGroup.Done()
		}(feed)
	}
	// 启动一个 goroutine 来监控是否所有的工作都做完了
	go func() {
		// 等候所有任务完成
		waitGroup.Wait()
		// 用关闭通道的方式，通知 Display 函数
		// 可以退出程序了
		close(results)
	}()
	// 启动函数，显示返回的结果，并且
	// 在最后一个结果显示完后返回
	Display(results)
}

func Display(results chan string) {
	for result := range results {
		fmt.Printf("%s:\n%s\n\n", result)
	}
}

func TestQC() {

	requestBody := `{
		"text": "Hello World"
	}
	`
	var jsonStr = []byte(requestBody)
	url := "https://im-dichat.xiaojukeji.com/api/hooks/incoming/58f05799-3454-4167-9a12-79f17da3a6e1"
	req, err := http.NewRequest("POST", url, bytes.NewBuffer(jsonStr))
	req.Header.Set("Content-Type", "application/json")
	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()
	fmt.Println("response Status:", resp.Status)
	fmt.Println("response Headers:", resp.Header)
	body, _ := ioutil.ReadAll(resp.Body)
	fmt.Println("response Body:", string(body))
}

func main() {
	TestQC()
	// Run("11")
}
