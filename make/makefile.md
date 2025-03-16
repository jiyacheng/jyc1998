## 1，c语言运行

预处理->编译->汇编->链接->目标文件

 ![img](https://img-blog.csdnimg.cn/20190928133358474.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3oxOTExNzI1MTQ1,size_16,color_FFFFFF,t_70) 

gcc编译步骤（包括预处理preprocessor,编译compiler,汇编assemble,链接linker）

**预处理**：gcc -E hello.c -o hello.i      完成对代码的预处理

处理源文件中以“#”开头的预编译指令，包括：

– 处理所有条件预编译指令，如“#if”,“#ifdef”, “#endif”等

– 插入头文件到“#include”处，可以递归方式进行处理

– 删除所有的注释“//”和“/* */”

– 添加行号和文件名标识，以便编译时编译器产生调试用的行号信息

– 保留所有#pragma编译指令（编译器需要用）

• 经过预编译处理后，得到的是预处理文件（如，hello.i) ，

它还是一个可读的文本文件 ，但不包含任何宏定义



**编译**: gcc -S hello.i -o hello.s      gcc –S hello.c –o hello.s 将**源代码编译成汇编代码**
• 编译过程就是将预处理后得到的预处理文件（如 hello.i）

进行 **词法分析、语法分析、语义分析、优化**后，生成汇编代码文

• 经过编译后，得到的汇编代码文件（如 hello.s）还是可读的文 本文件，CPU无法理解和执行它

gcc命令实际上是具体程序（如ccp、cc1、as等）的包装命令，

用户通过gcc命令来使用具体的预处理程序ccp、编译程序cc1和汇编程序as等



**汇编**：gcc -c hello.s -o hello.o ,  gcc -c hello.c -o hello.o ,  as hello.s -o hello.o

(as是一个汇编程序）将**汇编代码**转换成**可重定位目标文件**（二进制）

• 汇编程序（汇编器）用来将汇编语言源程序转换为**机器指令序列** （机器语言程序）

• 汇编指令和机器指令一一对应，前者是后者的**符号表示**，它们都 属于**机器级指令**，

所构成的程序称为机器级代码

• 汇编结果是一个可重定位目标文件（如，hello.o），其中包含 的是

不可读的二进制代码，必须用相应的工具软件来查看其内容



**链接**：gcc hello.o -o hello   

将**目标代码**和所需要的**库**链成一个**完整的应用程序**。

gcc的结果输出是后缀名不相关的，只与输入参数有关

为了构造可执行文件，连接器必须完成两个主要任务：

**符号解析**（symbol resolution)，**重定位**(relocation)

 

目标文件有三种形式：

• 可重定位目标文件。包含二进制代码和数据，其形式可以在编译时与其他可重定位

目标文件合并起来，创建一个可执行目标文件。

• 可执行目标文件。包括二进制代码和数据，其形式可以被直接复制到内存并执行。

• 共享目标文件。一种特殊类型的可重定位目标文件，可以在加载或者运行

时被动态的加载进内存并链接。

## 2，Makefile

 功能：[makefile](https://so.csdn.net/so/search?q=makefile&spm=1001.2101.3001.7020)关系到了整个工程的编译规则。一个工程中的源文件不计数，其按***\**\*类型、功能、模块\*\**\***分别放在若干个目录中，makefile定义了一系列的规则来指定，哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作 。 makefile带来的好处就是——“自动化编译”，一旦写好，只需要一个make命令，整个工程完全自动编译，极大的提高了软件开发的效率。 









**语法：**

 ***\*反斜杠 \ \****是换行符的意思。 

   在定义好依赖关系后，后续的那一行定义了如何生成目标文件的***\**\*操作系统命令\*\**\**\*，<u>一定要以一个\**\**Tab\*\*键作为开头\*\**\**\*。</u>记住，\**make\**并不管命令是怎么工作的，他只管执行所定义的命令\****。make会比较targets文件和prerequisites文件的修改日期，如果prerequisites文件的日期要比targets文件的日期要新，或者target不存在的话，那么，make就会执行后续定义的命令。 

***\*1.5 \*\*让\*\*\*\*make\*\*\*\*自动推导\*\**\***

GNU的make很强大，它可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个[.o]文件后都写上类似的命令，因为，我们的make会自动识别，并自己推导命令。

  只要make看到一个[.o]文件，它就会自动的把[.c]文件加在依赖关系中，如果make找到一个whatever.o，那么whatever.c，就会是whatever.o的依赖文件。并且 cc -c whatever.c 也会被推导出来，于是，我们的makefile再也不用写得这么复杂。我们的是新的makefile又出炉了。

 “.PHONY”表示，clean是个伪目标文件。 

***\*1.7 \*\*清空目标文件的规则\*\**\***

   每个Makefile中都应该写一个清空目标文件（.o和执行文件）的规则，这不仅便于重编译，也很利于保持文件的清洁。这是一个“修养”（呵呵，还记得我的《编程修养》吗）。一般的风格都是：

​    clean:

​      rm edit $(objects)

更为稳健的做法是：

​    .PHONY : clean

​    clean :

​        -rm edit $(objects)

前面说过，.PHONY意思表示clean是一个“伪目标”，。而在rm命令前面加了一个小减号的意思就是，也许某些文件出现问题，但不要管，继续做后面的事。当然，clean的规则不要放在文件的开头，不然，这就会变成make的默认目标，相信谁也不愿意这样。不成文的规矩是——“clean从来都是放在文件的最后”。

## 3,Makefile综述

***\*3.1 Makefile\*\*里有什么？\*\**\***

Makefile里主要包含了***\**\*五个东西\*\**\**\**\*：显式规则、隐晦规则、变量定义、文件指示和注释。\*\**\***

\1. 显式规则。显式规则说明了，如何生成一个或多的的目标文件。这是由Makefile的书写者明显指出，要生成的文件，文件的依赖文件，生成的命令。

\2. 隐晦规则。由于我们的make有自动推导的功能，所以隐晦的规则可以让我们比较粗糙地简略地书写Makefile，这是由make所支持的。

\3. 变量的定义。在Makefile中我们要定义一系列的变量，变量一般都是字符串，这个有点你C语言中的宏，当Makefile被执行时，其中的变量都会被扩展到相应的引用位置上。

\4. 文件指示。其包括了三个部分，一个是在一个Makefile中引用另一个Makefile，就像C语言中的include一样；另一个是指根据某些情况指定Makefile中的有效部分，就像C语言中的预编译#if一样；还有就是定义一个多行的命令。有关这一部分的内容，我会在后续的部分中讲述。

\5. 注释。Makefile中只有行注释，和UNIX的Shell脚本一样，其注释是用“#”字符，这个就像C/C++中的“//”一样。如果你要在你的Makefile中使用“#”字符，可以用反斜框进行转义，如：“\#”。

最后，还值得一提的是，在Makefile中的命令，必须要以[Tab]键开始。



***\*3 Makefile\*\*书写规则\*\**\***

 规则包含两个部分，一个是***\**\*依赖关系\*\**\***，一个是***\**\*生成目标的方法\*\**\***。

***\**\*在\*\*Makefile\*\*中，规则的顺序是很重要的\*\**\***，因为，***\*Makefile\*\*中只应该有一个最终目标\*\**\***，其它的目标都是被这个目标所连带出来的，所以一定要让make知道你的最终目标是什么。一般来说，定义在Makefile中的目标可能会有很多，但是第一条规则中的目标将被确立为最终的目标。如果第一条规则中的目标有很多个，那么，第一个目标会成为最终的目标。make所完成的也就是这个目标。

好了，还是让我们来看一看如何书写规则。

**3.1 规则举例**

 foo.o: foo.c defs.h    # foo模块

​      cc -c -g foo.c

看到这个例子，各位应该不是很陌生了，前面也已说过，foo.o是我们的目标，foo.c和defs.h是目标所依赖的源文件，而只有一个命令“cc -c -g foo.c”（以Tab键开头）。这个规则告诉我们两件事：

\1.    文件的依赖关系，foo.o依赖于foo.c和defs.h的文件，如果foo.c和defs.h的文件日期要比foo.o文件日期要新，或是foo.o不存在，那么依赖关系发生。

\2.    如果生成（或更新）foo.o文件。也就是那个cc命令，其说明了，如何生成foo.o这个文件。（当然foo.c文件include了defs.h文件）

***\*3.2 \*\*规则的语法\*\**\***

   targets : prerequisites

​    command

​    ...

或是这样：

   targets : prerequisites ; command

​      command

​      ...

targets是文件名，以空格分开，可以使用通配符。一般来说，我们的目标基本上是一个文件，但也有可能是多个文件。

command是命令行，如果其不与“target:prerequisites”在一行，那么，必须以[Tab键]开头，如果和prerequisites在一行，那么可以用分号做为分隔。（见上）

prerequisites也就是目标所依赖的文件（或依赖目标）。如果其中的某个文件要比目标文件要新，那么，目标就被认为是“过时的”，被认为是需要重生成的。这个在前面已经讲过了。

如果命令太长，你可以使用反斜框（‘\’）作为换行符。make对一行上有多少个字符没有限制。规则告诉make两件事，文件的依赖关系和如何成成目标文件。

一般来说，make会以UNIX的标准Shell，也就是/bin/sh来执行命令。

***\*3.3 \*\*在规则中使用通配符\*\**\***

   如果我们想定义一系列比较类似的文件，我们很自然地就想起使用通配符。make支持三各通配符：“*”，“?”和“[...]”。这是和Unix的B-Shell是相同的。

***\*"~"\****

波浪号（“~”）字符在文件名中也有比较特殊的用途。如果是“~/test”，这就表示当前用户的$HOME目录下的test目录。而“~hchen/test”则表示用户hchen的宿主目录下的test目录。（这些都是Unix下的小知识了，make也支持）而在Windows或是MS-DOS下，用户没有宿主目录，那么波浪号所指的目录则根据环境变量“HOME”而定。

***\*"\*"\****
通配符代替了你一系列的文件，如“*.c”表示所以后缀为c的文件。一个需要我们注意的是，如果我们的文件名中有通配符，如：“*”，那么可以用转义字符“\”，如“\*”来表示真实的“*”字符，而不是任意长度的字符串。

好吧，还是先来看几个例子吧：

  clean:

​    rm -f *.o

上面这个例子我不不多说了，这是操作系统Shell所支持的通配符。这是在命令中的通配符。

  print: *.c

​    lpr -p $?

​    touch print

上面这个例子说明了通配符也可以在我们的规则中，目标print依赖于所有的[.c]文件。其中的“$?”是一个自动化变量，我会在后面给你讲述。

  objects = *.o

上面这个例子，表示了，通符同样可以用在变量中。并不是说[*.o]会展开，不！objects的值就是“*.o”。Makefile中的变量其实就是C/C++中的宏。如果你要让通配符在变量中展开，也就是让objects的值是所有[.o]的文件名的集合，那么，你可以这样：

  objects := $(wildcard *.o)

这种用法由关键字“wildcard”指出，关于Makefile的关键字，我们将在后面讨论。

## 4，脚本语言--Makefile基本使用

**过程:**

1，创建文本文档，取名：Makefile.

2，注释：#

.c   --->   .i



第一层：显示规则(注意显示规则是递归的)

Makefile文件内容：

![ ](C:\Users\纪亚成\AppData\Roaming\Typora\typora-user-images\1642516703459.png)



![1642517260497](C:\Users\纪亚成\AppData\Roaming\Typora\typora-user-images\1642517260497.png)

**语法：**

rm -rf hello.o

make后执行，./hello

第二层： 变量![1642517590447](C:\Users\纪亚成\AppData\Roaming\Typora\typora-user-images\1642517590447.png)

第三层：隐含规则（图中23行出错，%.o与%.c位置搞反了）

![1642517854692](C:\Users\纪亚成\AppData\Roaming\Typora\typora-user-images\1642517854692.png)

第四层： 通配符

![1642518827122](C:\Users\纪亚成\AppData\Roaming\Typora\typora-user-images\1642518827122.png)



vim代码模板，

IDE：代码模板----》配置vdscode



g++（linux)编译C++文件.

### 多个源文件生成可执行程序

------

如果多于一个的源码文件在 g++ 命令中指定，它们都将被编译并被链接成一个单一的可执行文件。下面是一个名为 speak.h 的头文件；它包含一个仅含有一个函数的类的定义：

```cpp
/* speak.h */
#include <iostream>
class Speak
{
    public:
        void sayHello(const char *);
};
```

 

下面列出的是文件 speak.cpp 的内容：包含 sayHello() 函数的函数体：

```css
/* speak.cpp */
#include "speak.h"
void Speak::sayHello(const char *str)
{
    std::cout << "Hello " << str << "\n";
}
```

 

文件 hellospeak.cpp 内是一个使用 Speak 类的程序：

```cpp
/* hellospeak.cpp */
#include "speak.h"
int main(int argc,char *argv[])
{
    Speak speak;
    speak.sayHello("world");
    return(0);
}
```

下面这条命令将上述两个源码文件编译链接成一个单一的可执行程序：

```avrasm
$ g++ hellospeak.cpp speak.cpp -o hellospeak
```

PS：这里说一下为什么在命令中没有提到“speak.h“该文件（原因是：在“speak.cpp“中包含有”#include”speak.h”“这句代码，它的意思是搜索系统头文件目录之前将先在当前目录中搜索文件“speak.h“。而”speak.h“正在该目录中，不用再在命令中指定了）。



 **选项  -c** 用来告诉编译器编译源代码但不要执行链接，输出结果为对象文件。 

 **选项  -o**指定可执行程序的文件名。 



### 源文件生成对象文件

------

选项 -c 用来告诉编译器编译源代码但不要执行链接，输出结果为对象文件。文件默认名与源码文件名相同，只是将其后缀变为 .o。例如，下面的命令将编译源码文件 hellospeak.cpp 并生成对象文件 hellospeak.o：

```r
$ g++ -c hellospeak.cpp
```

命令 g++ 也能识别 .o 文件并将其作为输入文件传递给链接器。下列命令将编译源码文件为对象文件并将其链接成单一的可执行程序：

g++−chellospeak.cppg++−chellospeak.cpp g++ -c speak.cpp 
$ g++ hellospeak.o speak.o -o hellospeak

选项 -o 不仅仅能用来命名可执行文件。它也用来命名编译器输出的其他文件。例如：除了中间的对象文件有不同的名字外，下列命令生将生成和上面完全相同的可执行文件：

```avrasm
$ g++ -c hellospeak.cpp -o hspk1.o 
$ g++ -c speak.cpp -o hspk2.o 
$ g++ hspk1.o hspk2.o -o hellospeak
```

### 编译预处理

------

选项 -E 使 g++ 将源代码用编译预处理器处理后不再执行其他动作。下面的命令预处理源码文件 helloworld.cpp 并将结果显示在标准输出中：

```ruby
$ g++ -E helloworld.cpp
```

本文前面所列出的 helloworld.cpp 的源代码，仅仅有六行，而且该程序除了显示一行文字外什么都不做，但是，预处理后的版本将超过 1200 行。这主要是因为头文件 iostream 被包含进来，而且它又包含了其他的头文件，除此之外，还有若干个处理输入和输出的类的定义。

预处理过的文件的 GCC 后缀为 .ii，它可以通过 -o 选项来生成，例如：

```avrasm
$ gcc -E helloworld.cpp -o helloworld.ii
```

### 生成汇编代码

------

选项 -S 指示编译器将程序编译成汇编语言，输出汇编语言代码而後结束。下面的命令将由 C++ 源码文件生成汇编语言文件 helloworld.s：

```ruby
$ g++ -S helloworld.cpp1
```

生成的汇编语言依赖于编译器的目标平台。



### 创建静态库

------

静态库是编译器生成的一系列对象文件的集合。链接一个程序时用库中的对象文件还是目录中的对象文件都是一样的。库中的成员包括普通函数，类定义，类的对象实例等等。静态库的另一个名字叫归档文件(archive)，管理这种归档文件的工具叫 ar 。

在下面的例子中，我们先创建两个对象模块，然后用其生成静态库。 
头文件 say.h 包含函数 sayHello() 的原型和类 Say 的定义：

```cpp
/* say.h */
#include <iostream>
void sayhello(void);
class Say {
    private:
        char *string;
    public:
        Say(char *str)
        {
            string = str;
        }
        void sayThis(const char *str)
        {
            std::cout << str << " from a static library\n";
        }
        void sayString(void);
};
```

下面是文件 say.cpp 是我们要加入到静态库中的两个对象文件之一的源码。它包含 Say 类中 sayString() 函数的定义体；类 Say 的一个实例 librarysay 的声明也包含在内：

```cpp
/* say.cpp */
#include "say.h"
void Say::sayString()
{
    std::cout << string << "\n";
}

Say librarysay("Library instance of Say");
```

源码文件 sayhello.cpp 是我们要加入到静态库中的第二个对象文件的源码。它包含函数 sayhello() 的定义：

```css
/* sayhello.cpp */
#include "say.h"
void sayhello()
{
    std::cout << "hello from a static library\n";
}
```

下面的命令序列将源码文件编译成对象文件，命令 ar 将其存进库中：

```avrasm
$ g++ -c sayhello.cpp
$ g++ -c say.cpp
$ ar -r libsay.a sayhello.o say.o
```

程序 ar 配合参数 -r 创建一个新库 libsay.a 并将命令行中列出的对象文件插入。采用这种方法，如果库不存在的话，参数 -r 将创建一个新的库，而如果库存在的话，将用新的模块替换原来的模块。 
下面是主程序 saymain.cpp，它调用库 libsay.a 中的代码：

```csharp
/* saymain.cpp */
#include "say.h"
int main(int argc,char *argv[])
{
    extern Say librarysay;
    Say localsay = Say("Local instance of Say");
    sayhello();
    librarysay.sayThis("howdy");
    librarysay.sayString();
    localsay.sayString();
    return(0);
}
```

该程序可以下面的命令来编译和链接：

```avrasm
$ g++ saymain.cpp libsay.a -o saymain
```

程序运行时，产生以下输出：

```delphi
hello from a static library
howdy from a static library
Library instance of Say
Local instance of Say
```

本文来自：http://wiki.ubuntu.org.cn/Compiling_Cpp

ps：如果一个文件夹下有多个cpp文件需要编译的话，除了采用makefile的方式之外，还可以使用

“`g++ *.cpp -o hello`”,“hello为编译生成的可执行文件的名字”，编译时要确保cpp文件和他们各自所引用的头文件在同一个目录下。

