// GlyphConvert.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
std::vector<std::string> files;

void symbols() {
	int cnt = 13;

	for (int i = 0; i < cnt; ++i) {
		fs::path s(std::to_string(i));
		fs::path p(s);
		s.replace_extension(".bmp");
		p.replace_extension(".svg");

		system(("potrace -s \"../basic_symbols_bmp\\" + s.string() + "\" -o \"../basic_symbols\\" + p.string() + "\"").c_str());
	}
}

int main() {
	symbols();
	return 0;

	std::cout << "Hello World!\n";

	files.reserve(2048);

	std::ifstream ifs("../1.txt");

	while (true) {
		std::string line;
		ifs >> line;

		if (line.length() > 0)
			files.push_back(line);

		// Check if end of file is reached
		if (ifs.eof()) {
			std::cout << "End of file reached. " << files.size() << std::endl;
			break;
		}
	}

	for (auto& s : files) {
		fs::path p(s);
		p.replace_extension(".svg");

		system(("potrace -s \"../basic_glyphs_bmp\\" + s + "\" -o \"../basic_glyphs\\" + p.string() + "\"").c_str());
	}
}

