# SysY-Compiler
- NWPU compiler homework , a simplified C language(SysY) Compiler 

- 包含了项目代码以及词法分析，语法分析，优化，MIPS代码生成的测试

- 所有设计和测试结果都保存在《实验报告》目录中

## 功能需求及实现

- `词法分析：` 读取源文件，通过词法分析模块 生成 token 序列，用 C++的 vector 容器存储。 

- `语法分析 ：` 对 SYsy 文法的 EBNF 表达式进行递归下降，在递归下降的同时建 立符号表，根据语义规则进行语法分析，同时生成中间代码的四元式形式。 

- `局部中间代码优化：` 基本块划分，代数恒等式的优化，删除冗余临时变量，删除公共子表达式，局部常量传播。 

- `代码生成：` 生成 mips 汇编，没有采用特殊的寄存器分配策略，使用 $t0-$t7,$s0-$s8 进行分配，如果使用到的中间变量多余全部可用的寄存器，则在栈中存取。 

- `错误处理：` 在其它模块中进行错误处理分析,在 error.cpp 中打印并提示错误信息

## 模块划分和调用情况
- `main.cpp` main 函数
- `lexial.cpp` 词法分析
- `grammer.cpp` main 语法分析，符号表，语义检查，中间代码生成
- `opt.cpp` 全局优化，局部优化
- `tomips.cpp` 生产MIPS代码，寄存器分配优化
- `error.cpp`  错误处理


<div align=center>
<image src="fig/1.png"  width="40%" height="50%">
</div>
  
  
<div align=center>
<image src="fig/2.png"  width="40%" height="50%">
</div>

## 运行时栈设计
<center>
  
| 运行时栈 | 
| ------ | 
| 参数 | 
| 返回地址 | 
| 保存的 fp 旧值 | 
| 被调用函数的运行时栈 临时变量和数据 | 
| .text | 
| .data | 
  
</center>
  
## 在Mars中的部分测试结果
  
<div align=center>
<image src="fig/3.png"  width="40%" height="50%">
</div>
