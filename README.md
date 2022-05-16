# ANSI-Escape-Code

[ANSI escape code - Wikipedia](https://en.wikipedia.org/wiki/ANSI_escape_code)

## 使用举例

直接将对象打印至终端

### 打印颜色

```C++
std::cout << foreground("red");			// 设置字体颜色为红色
std::cout << background("black");       // 设置背景颜色为黑色
std::cout << "Hello, world!\n";			// 打印出黑底红字
std::cout << style("reset");			// 重置以清除所有效果

std::cout << foreground("green");		// 设置字体颜色为绿色
std::cout << style("underline");		// 设置下划线
std::cout << "Hello, world!\n";			// 打印时带有下滑线
std::cout << style("reset");			// 重置以清除所有效果
```

### 移动光标

```C++
std::cout << cursor("up",2);			// 向上移动2个单位
std::cout << cursor("right");			// 向右移动1个单位
std::cout << "***";						// ell 被 *** 覆盖
std::cout << cursor(5,1,true);			// 向右移动5个单位，向下移动1个单位
```

### 删除字符

```C++
std::cout << erase("line","before")		// 删除Hello, wor
std::cout << "Hello, world!\n";			// 用新的Hello, world!覆盖原来的ld!
```

### 使用decorated函数

达到与上面相同的效果

```C++
std::cout << decorated("Hello, World!\n", {foreground("red"), background("black")});
std::cout << decorated("Hello, World!\n", {style("underline")});
std::cout << decorated("***", {cursor("up",2),cursor("right")}, {cursor(5,1,true)});
std::cout << decorated("Hello, World!\n", {erase("line","before")});
```



## 定义

### decorated

```C++
string decorated(string, {decorator...})					// 在字符串首添加修饰，尾部默认为style("reset")
string decorated(string, {decorator...}, {decorator...})	// 在字符串首尾分别添加修饰
```

### decorators

#### foreground

```C++
foreground(int r, int g, int b) // 24 bit color
    r: 0<=int<=255
	g: 0<=int<=255
	b: 0<=int<=255
foreground(int color)	// 8 bit color
    color: 0<=int<=255
foreground(std::string color)
    color: 	"black","red", "green", "yellow", "blue", "magenta", "cyan", "white", 
			"lightblack", "lightred", "lightgreen", ...
```

#### background

同foreground

#### style

```C++
style(std::string type)	
    type: "reset", "bright", "dim", "italic", "underline", "blink", "reverse", "hidden", "crossed", ...
```

#### cursor

```C++
cursor(int x,int y)			// 设置光标的绝对坐标（相对于屏幕左上角，x正方向向右，y正方向向下）
cursor(int x,int y,true)	// 以当前位置为起点
cursor(std::string direction, int n)			// 向给定方向移动n个单位
    direction: 	"up", "down", "left", "right" 	// 向上，下，左，右移动n个字符
				"previous", "next" 				// 移动到前n行行首，后n行行首
   				"pageup", "pagedown"			// 上一页，下一页
	n: int 
```

#### erase

```C++
erase(std::string target, std::string type)
    target: "line", "screen"	// 清除范围
    type:	"after"  			// 清除当前位置后的所有字符
        	"before" 			// 清除当前位置前的所有字符
        	"all"				// 清除范围内的所有字符
```

