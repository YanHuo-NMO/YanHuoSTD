// GlyphEnum.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "GlyphEnum.h"

int main() {
	GlyphEnum enumer;
	enumer.readBasic("../basic.bmp");
	enumer.genTo("../basic_glyphs_bmp");
}
