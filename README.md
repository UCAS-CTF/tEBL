
# Table of Contents

1.  [About](#orgd07063a)
2.  [References](#org12d3bae)



<a id="orgd07063a"></a>

# About

这是一个简单的解释器自举 (bootstrap) 的小教程.
本教程的目标在于用一个尽可能小, 同时尽可能简单的玩具项目 <sup><a id="fnr.what-i-mean-simple" class="footref" href="#fn.what-i-mean-simple" role="doc-backlink">1</a></sup>,
来介绍基础的一些计算机知识 <sup><a id="fnr.what-i-mean-basic-computer-knowledge" class="footref" href="#fn.what-i-mean-basic-computer-knowledge" role="doc-backlink">2</a></sup>.

最终会用 C 语言作为基础解释器, 实现一种 [LISP](https://en.wikipedia.org/wiki/Lisp_(programming_language)) 的方言 (主要借鉴了 LISP-1.5)
的解释器, 编译器 (看进度). 并在其之上实现一些简单的功能和程序.

大概的进度安排:

1.  简单的 C 回顾与链表的实现
2.  简单的链表读取 (从 `stdin` 到任意 `stream` 的输入读取) 与解析 (top-down parser)
3.  6 个 <sup><a id="fnr.6-base-fn" class="footref" href="#fn.6-base-fn" role="doc-backlink">3</a></sup> 基本函数 (`atom`, `car`, `cdr`, `cons`, `eq`, `cond`) 解释器的实现
4.  用 6 个基本函数实现的 "解释器"
5.  给解释器添加更多的功能 (不同类型的值? 对值的标记? 不同的计算顺序? )
6.  让解释器去生成简单的汇编 <sup><a id="fnr.llvm-ir-or-asm" class="footref" href="#fn.llvm-ir-or-asm" role="doc-backlink">4</a></sup>
7.  如何实现 JIT (Just In Time, 在读取时编译并运行的解释器)
8.  如何实现 GC (Garbage Collecting)
9.  &#x2026;

如何跟进?

-   `.md` 和 `.org`, 该阅读哪一种?
    
    `.org` 是我在撰写本教程中使用的标记语言 (markup language, [org-mode](https://orgmode.org)),
    使用它是出于我个人的喜好以及对我来说效率最高. 但是为了方便 Github 的渲染,
    以及非 org-mode 用户的使用, 我会在提交前导出一份 markdown 格式.
-   `day*` 真的是一天能够完成的量吗?
    
    虽然本项目确实是按照 `day*` 来划分的, 但并不意味着进度安排是一天就能完成的
    (或者是能够撑起一天的工作量). 毕竟我写的时候也不是一天就写完的,
    并且一些概念出于第一次接触或是我的表达能力的原因, 可能并不能快速理解.
    
    所以假如你无法在一天里面完成 `day*` 的内容, 或是你觉得 `day*` 的内容过少,
    完全可以根据自己的进度去调整.


<a id="org12d3bae"></a>

# References

可能有用的参考资料 (虽然我也没有全部读完就是了)

-   [From Linked List to the Old Yet Modern Computer [S1]​](https://li-yiyang.github.io/lisp/from-linked-list-to-the-old-yet-modern-computer/)
-   [From Linked List to the Old Yet Modern Computer [S2]​](https://li-yiyang.github.io/lisp/from-linked-list-to-the-old-yet-modern-computer-2/)
-   [mal (Make a Lisp)](https://github.com/kanaka/mal/)
-   [RECURSIVE FUNCTIONS OF SYMBOLIC EXPRESSIONS AND THEIR COMPUTATION BY MACHINE (Part I)](https://www-formal.stanford.edu/jmc/recursive.html)
-   [LISP1.5](https://github.com/informatimago/lisp-1-5/)
-   [History of Lisp](http://jmc.stanford.edu/articles/lisp/lisp.pdf)
-   Anatomy of LISP
-   LISP from Nothing
-   The Architecture of Symbolic Computers
-   [Programming languages resources](https://bernsteinbear.com/pl-resources/)


# Footnotes

<sup><a id="fn.1" href="#fnr.1">1</a></sup> 这里指的 "尽可能小" 指的是相对而言,
不做代码压缩优化之类的尽可能小, "尽可能简单" 指的也是相对的简单,
毕竟实现的功能少的代价就是可能会缺少部分的高层的抽象,
使得一些功能可能难以实现.

<sup><a id="fn.2" href="#fnr.2">2</a></sup> 这里的 "基础" 计算机知识,
指的也是相对而言的基础计算机知识. 你可能需要适当了解一些关于如何编译 C
语言程序以及如何运行它们的简单前置知识. 同时, 为了尽量保证 "基础",
我会尽量保留一些简单的伪代码, 流程图以及示意图, 理论上来说,
你可以使用任意的编程语言来实现 tEBL.

<sup><a id="fn.3" href="#fnr.3">3</a></sup> 实际上为了方便, 我觉得再添加一个 `setq` (全局的带副作用的赋值操作)
会更好. 但是只有 6 个基本函数其实也不是不能实现局部的值绑定, 只是有些过于麻烦了.

<sup><a id="fn.4" href="#fnr.4">4</a></sup> 这里我还没有想好要用 LLVM IR 还是直接生成汇编.
当然, 另外还有一种选择就是写一个虚拟机去对应到其指令集上,
好处就是可以把指令集设计得非常简单. 不过完全不用担心, 不论是 LLVM IR
还是直接生成汇编, 我们的编译器都是那种完全没有优化的编译器.
实现起来是非常轻松的那种最简单的编译器. 虽然我可以保证性能一定不好,
但是 tEBL 的目标是为了实现 "自举" 而非实现性能的优化, 所以也不是不行吧.
