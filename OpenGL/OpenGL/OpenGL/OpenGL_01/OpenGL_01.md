Open GL 入门
=============

### 一、定义
##### OpenGL
一般它被认为是一个API(Application Programming Interface, 应用程序编程接口)，包含了一系列可以操作图形、图像的函数。然而，OpenGL本身并不是一个API，它仅仅是一个由Khronos组织制定并维护的规范(Specification)。

实际的OpenGL库的开发者通常是显卡的生产商。

由于OpenGL的大多数实现都是由显卡厂商编写的，当产生一个bug时通常可以通过升级显卡驱动来解决。这些驱动会包括你的显卡能支持的最新版本的OpenGL，这也是为什么总是建议你偶尔更新一下显卡驱动。

##### GLFW
GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入，这正是我们需要的。
(下载链接: http://www.glfw.org/download.html)

##### CMake
CMake是一个工程文件生成工具。

### 二、实践

> 顶点数组对象:  Vertex  Array  Object,  VAO
>
> 顶点缓冲对象:  Vertex Buffer Object,   VBO
>
> 索引缓冲对象:  Element Buffer Object,  EBO  或者 Index Buffer Object,  IBO


#### 相关资料
>LearnOpenGL(中文)：https://learnopengl-cn.github.io

>LearnOpenGL(英文)：https://learnopengl.com/

#### 参考资料
>配置编译环境: https://blog.csdn.net/u012733215/article/details/44751111
