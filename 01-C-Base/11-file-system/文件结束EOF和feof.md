
stdio.h中有如下定义:
```c
#define EOF (-1)
#define _IOEOF          0x0010
#define feof(_stream)     ((_stream)->_flag & _IOEOF) 
```

### 判断文本文件是否结束： 
```c
char ch;
while(ch = fget(fp)) != EOF)
{
    putchar(ch)
}
```
一般地，用EOF判断文本文件是否结束。文本文件存放的内容一般是asii码（0-255），而EOF是-1。

### 判断二进制文件是否结束： 
```c
char ch;
ch = fgetc(fp);
while(feof(fp))
{
    putchar(ch);
    ch = fgetc(fp);
}
```
对于二进制文件，文件存放的内容可能包含-1(即：FF)，故不可用EOF来判断文件是否结束。
一般使用feof()，当然用feof()也可以用来判断文本文件是否结束。

### feof()和数据库中的eof()有所区别 
在读到最后一个字符后，stream->flag仍然没有被置为_IOEOF，feof() > 0；
在数据库中读到最后一条记录后eof()==false；

用如下方法读取会多出一个ffffffff
```c
char ch;
while(feof(fp))
{
    ch = fgetc(fp);
    printf("%x/n", ch);
}
```
原因是在读到最后一个字符后，stream->flag仍然没有被置为_IOEOF，feof() > 0；再次用fgetc()读取的，
stream->flag才会被置为_IOEOF，feof()==0，fgetc()返回-1(即ffffffff) 

老谭的经典的c程序设计中的一道题：复制一个文件file1的内容到另一个文件file2。
老谭的程序：
```c
char ch;
while(feof(in))
{
    ch = fgetc(in);
    fputc(ch，out);
}
```
程序运行后，我们会发现file1和file2内容不一致。
正确的方法：
```c
char ch;
ch = fgetc(in);
while(feof(in))
{
    ch = fgetc(in);
    fputc(ch，out);
}
```
--------------------- 
作者：ludonghai715 
来源：CSDN 
原文：https://blog.csdn.net/ludonghai715/article/details/6535911 
版权声明：本文为博主原创文章，转载请附上博文链接！










头文件：`#include <stdio.h>`

`feof()`函数用来检测当前文件流上的文件结束标识，判断是否读到了文件结尾，其原型为：
    `int feof(FILE * stream);`

【参数】stream为文件流指针。

【返回值】检测到文件结束标识返回1，否则返回0。

文件结束标识一般由上次的读写操作来设置，当然也可以手动设置。

当文件内部的位置指针指向文件结束时，并不会立即设置FILE结构中的文件结束标识，只有再执行一次读文件操作，才会设置结束标志，此后调用feof()才会返回为真。

文件结束标识可以由 clearerr()、rewind()、fseek()、fsetpos() 和 freopen() 函数清除；如果这时位置指针未被重置，那么将在下次 I/O 操作时进行设置。

更多信息请参考：[C语言FILE结构体](http://c.biancheng.net/cpp/html/2416.html)

注意，feof()与EOF不同：feof()是函数，用来检测文件的结束；EOF是 End Of File 的缩写，是C语言中标准库中定义的宏，定义为：#define  EOF  (-1)。

EOF的值为-1，是 int 类型数据，在32位系统中，可以表示为0xFFFFFFFF；EOF 不是一个字符，也不是文件中实际存在的内容。EOF不但能表示读文件到了结尾这一状态，它还能表示 I/O 操作中的读、写错误（可以用 ferror() 来检测）以及其它一些关联操作的错误状态。

fgetc() 或getc() 等函数返回EOF并不一定表示文件结束，当读取文件出错时也会返回EOF，仅凭返回 -1 就认为文件结束是错误的；正因为如此，我们需要feof()来判断文件是否结束，当然用feof()来判断文件结束时也需要判断读取操作是否出错，这时可以用ferror()来判断，当其为真时表示有错误发生。在实际的程序中，应该每执行一次文件操作，就用用ferror()函数检测是否出错。

例如，有一个文件指针fp，文件中有字符串“hello world”：
```c
int c=0;
while( !feof(fp) )
{
    int c=fgetc(fp);
    printf("%c: %x \n", c, c);
}
```
上面的代码除了输出 hello 外，还会输出一个结束字符EOF（EOF是fgetc函数的返回值，并不是文件中存在EOF）。其原因就是当内部位置指针指向结尾时，还要执行一次读操作，文件结束标识才会被设置。

对上面代码进行更改：
```c
int c; 
c=fgetc(fp);     
while( !feof(fp) ) 
{    
    printf("%c: %x \n", c, c); 
    c=fgetc(fp); 
}  
```
上面的代码只输出“hello”不输出文件结束符EOF。当文件内部位置指针指向结束位置时，先执行一次读操作，设置文件结束标识，while循环立即结束。

【实例】读取一个文件直到结束，然后回到开头重新读取。
```c
#include<iostream.h>
#include<stdio.h>
void main(void)
{
    FILE* stream;
    long l;
    float fp;
    char s[81];
    char c;
    stream = fopen("fscanf.txt","w+");
    if(stream == NULL)  /*打开文件失败*/
    {
        printf("the file is opeaned error!\n");
    }
    else
    {
        fprintf(stream,"%s %ld %f %c","a_string",6500,3.1415,'x');
        fseek(stream,0L,SEEK_SET);  /*定位读写指针*/
        fscanf(stream,"%s",s);
        printf("%ld\n",ftell(stream));
        fscanf(stream,"%ld",&l);
        printf("%ld\n",ftell(stream));
        fscanf(stream,"%f",&fp);
        printf("%ld\n",ftell(stream));
        fscanf(stream," %c",&c);
        printf("%ld\n",ftell(stream));
        fgetc(stream);  /*使指针到结尾*/
        if(!ferror(stream))
        {
            if(feof(stream))  /*如果不是结束*/
            {
                printf("We have reached end-of-file\n");
                rewind(stream);
                fscanf(stream,"%s",s);
                printf("%s\n",s);
            }
        }
       
        fclose(stream);
    }
}
```
运行结果：
8
13
22
24
We have reached end-of-file
a_string

程序先创建一个文件，写入4个类型的数据，然 后把读/写指针定位到文件开头逐个读取并输出当前指针的位置， 如果到了文件结尾则提示已经到达文件结尾，重新定位文件到开头并读取一个字符串。