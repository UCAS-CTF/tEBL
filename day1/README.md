
# Table of Contents

1.  [前置需求](#org70fe211)
2.  [Detour: 简单的 C 语言复习 (以及简单的 EBNF 介绍)](#orga8b84ba)



<a id="org70fe211"></a>

# 前置需求

你需要了解简单的 C 语言以及如何使用 `gcc`, `llvm` 或 `msvc`
等编译器编译并运行你的 C 语言程序.


<a id="orga8b84ba"></a>

# Detour: 简单的 C 语言复习 (以及简单的 EBNF 介绍)

让我们来回顾一下一个简单的 C 语言程序 `hello_world.c`:

    #include <stdio.h>
    
    int main (int argc, char **argv)
    {
      printf("Hello World\n");
      return 0;
    }

编译 <sup><a id="fnr.how-to-compile-c" class="footref" href="#fn.how-to-compile-c" role="doc-backlink">1</a></sup> 并运行 <sup><a id="fnr.how-to-run-program" class="footref" href="#fn.how-to-run-program" role="doc-backlink">2</a></sup>,
我们可以在标准输出 `stdout` <sup><a id="fnr.what-is-stdio" class="footref" href="#fn.what-is-stdio" role="doc-backlink">3</a></sup> 中得到如下的输出:

    Hello World

如果我们将其抽象地来表述:

    预处理
    预处理
    ...
    函数定义
    函数定义
    ...

当然, 这样的记号实在是过于含糊不清了,
我们需要给它一个 "清晰" <sup><a id="fnr.what-i-mean-clear-here" class="footref" href="#fn.what-i-mean-clear-here" role="doc-backlink">4</a></sup> 的定义.

-   定义 `预处理` 为:
    
        预处理 ::= "#include" "<" 头文件名称或者相对路径 ">"
                 | "#define"  宏名称   表达式
    
    这里我们用 `::=` 符号表示规则的定义. 用 `|` 符号表示或, 即一个
    `预处理` 对应的表达式可以是 `#include < 头文件名称或者相对路径 >`,
    也可以是 `#define  宏名称   表达式`.
-   定义 `函数定义` 为:
    
        函数定义 ::= 类型 函数名 函数参数 "{"
                       (表达式 ";")*
                     "}"
    
    这里用 `*` 表示零次或多次的重复. 用 `(` 和 `)` 表示将括号内的元素看作一个整体,
    即我们可以在函数定义的 `{}` block 内看到 `表达式;`, `表达式;表达式;` 这样的东西.

用类似的规则, 我们可以定义一个简单的 C 语言 <sup><a id="fnr.simple-c-ebnf" class="footref" href="#fn.simple-c-ebnf" role="doc-backlink">5</a></sup>
的描述来作为我们 C 语言的复习:

    类型     ::= "int"
               | "float"
               | "double"
    
    函数参数 ::= "(" ")"
               | "(" 类型 变量名 ")"
               | "("
                     类型 变量名
                     ("," 类型 变量名)+
                 ")"
    
    表达式   ::=
               | 变量名                # x, x_y, 等等
               | 字面值                # 1, 2, 2.3, 'x', 等等
               | "(" 表达式 ")"        # ( x + 2 )
               | 变量名 "=" 表达式     # x = 2; 赋值
               | 表达式 "+" 表达式     # x + b; 加法
               | ...

一个有意思的例子 (`gen_c_by_enbf.c`) 是,
我们可以利用上面的规则来生成一个 "语法正确" 的 C 语言程序:

    #define RAND(x) (rand() % (x))
    
    void gen_type () {
      switch (RAND(3)) {
      case 0:  printf("int");   break;
      case 1:  printf("float"); break;
      case 2:  printf("char");  break;
      default: break;
      }
    }
    
    // ... see more in gen_c_by_enbf.c

注: 虽然语法正确, 但是可能并不是那么的语义正确.
一个简单的例子 <sup><a id="fnr.random-seed-gen" class="footref" href="#fn.random-seed-gen" role="doc-backlink">6</a></sup>:

    gcc -o gen_c_by_ebnf gen_c_by_ebnf.c && ./gen_c_by_ebnf 11451

小节: 在本节中稍微回顾了一下简单的 C 语言,
同时写了一个根据 EBNF 规则描述的通过递归实现的 C 语言文本生成器.
这其实没啥鸟用, 唯一的用处就是让大家了解 EBNF
可以用来描述一些比较有规律的语言; 同时让大家复习一下简单的 C
语言程序的阅读 (阅读 `gen_c_by_ebnf.c`).


# Footnotes

<sup><a id="fn.1" href="#fnr.1">1</a></sup> 假如你并不会编译, 这里以 `gcc` 为例:
`gcc -o hello_world hello_world.c` (更多内容请参考手册)

<sup><a id="fn.2" href="#fnr.2">2</a></sup> `./hello_world` 这告诉你的 shell 运行
给定的路径上的可执行程序. 和通常直接输入 `ls`, `gcc`, `cd` 这样的命令不同,
对于后者, shell 会在 `PATH` (环境变量) 的路径下查找是否存在对应的可执行程序.

<sup><a id="fn.3" href="#fnr.3">3</a></sup> 这里的 `stdout` (标准输出, **st**​an​**d**​ard **out**​put)
和以后会接触到的 `stdin` (标准输入, **st**​an​**d**​ard **in**​put) 和
`stderr` (标准错误输出, **st**​an​**d**​ard **err**​or) 是一种 [stream](https://en.wikipedia.org/wiki/Stream_(computing)) (流).
大家可以将其想象成一种管道, 可以从一个管道 (`input-stream`) 中读取数据,
可以从一个管道 (`output-stream`) 中写入数据 (`stderr` 可以看作是一种
`output-stream`).

<sup><a id="fn.4" href="#fnr.4">4</a></sup> 这里的 "清晰" 定义其实借鉴了部分的 [EBNF](https://en.wikipedia.org/wiki/Extended_Backus–Naur_form) 语法,
只不过用中文作为非终结符 (noterminal) 的标记来更加容易接受吧&#x2026;

<sup><a id="fn.5" href="#fnr.5">5</a></sup> 这里的 "简单" C 语言指的是 C 语言的一个小小子集.
为了简单, 我们并不会实现全部的 C 语言. 如果你对完整的 C 语言的 EBNF 表述感兴趣,
你可以考虑参考 [The syntax of C in Backus-Naur Form](https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm) (Section A13 of
The C programming language, 2nd edition, by Brian W. Kernighan and
Dennis M. Ritchie,Prentice Hall, 1988.)

<sup><a id="fn.6" href="#fnr.6">6</a></sup> 这里我们通过设定一个 `11451`
作为随机数种子的方式来保证输出的一致性.
你也可以替换为自己的随机数种子或者不提供随机数种子,
即使用当前时间 `time(NULL)` 作为随机数种子来进行设置.
