#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include "yhchar.h"

using namespace std;
namespace fs = filesystem;

class GlyphEnum {
public:
	GlyphEnum() = default;
	~GlyphEnum() = default;

	void readBasic(const fs::path& filepath);
	void genTo(const fs::path& dir);

private:
	vector<pair<yhchar, yh_glyph>> m_consonants;
	vector<pair<yhchar, yh_glyph>> m_vowels;
};
