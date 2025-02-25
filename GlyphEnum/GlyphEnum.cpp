#include "GlyphEnum.h"

#include <format>
#include <opencv2/opencv.hpp>
#include <set>

namespace {

yh_glyph get_glyph(int offsetx, int offsety, cv::Mat& image) {
	offsetx = 1 + offsetx * 4;
	offsety = 1 + offsety * 8;

	yh_glyph res = 0;
	yh_glyph f = 1;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 7; ++j) {
			cv::Point tp(offsetx + i, offsety + j);

			uchar clr = image.at<uchar>(tp);

			if (clr < 128) {
				res |= f;
			}
			f <<= 1;
		}
	}
	return res;
}

cv::Mat gen_glyph(yh_glyph glyph) {
	cv::Mat mat(7 * 16, 4 * 16, CV_8UC1, cv::Scalar(255));

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (glyph & 1) {
				int x = i * 16;
				int y = j * 16;
				cv::rectangle(mat, cv::Rect(x, y, 16, 16), cv::Scalar(0), cv::FILLED);
			}
			glyph >>= 1;
		}
	}
	return mat;
}

}

void GlyphEnum::readBasic(const fs::path& filepath) {
	if (!fs::exists(filepath) || !fs::is_regular_file(filepath))
		return;

	cv::Mat im = cv::imread(filepath.string(), cv::ImreadModes::IMREAD_UNCHANGED);

	int nnnn = (yh_conso::COUNT_c - 1) * yh_csmod::COUNT_m;
	m_consonants.reserve(nnnn);
	for (int i = 0, n = nnnn; i < n; ++i) {
		int x = i % 16;
		int y = i / 16;

		yh_glyph glyph = get_glyph(x, y, im);

		yh_conso c = yh_conso(i / yh_csmod::COUNT_m + 1);
		yh_csmod m = yh_csmod(i % yh_csmod::COUNT_m);

		m_consonants.emplace_back(yhchar(c, m, yh_vowel::null_v, yh_vowel::null_v), glyph);
	}

	yh_glyph vowel[yh_vowel::COUNT_v] = {};
	yh_glyph vowel2[yh_vowel::COUNT_v] = {};

	m_vowels.reserve((yh_vowel::COUNT_v - 1) * yh_vowel::COUNT_v);
	for (int i = 1; i < yh_vowel::COUNT_v; ++i) {
		int x = i - 1;
		int y = 3;

		yh_glyph glyph = get_glyph(x, y, im);

		vowel[i] = glyph;
		m_vowels.emplace_back(yhchar(yh_conso::null_c, yh_csmod::null_m, yh_vowel(i), yh_vowel::null_v), glyph);
	}
	for (int i = 1; i < yh_vowel::COUNT_v; ++i) {
		int x = i - 1;
		int y = 4;

		yh_glyph glyph = get_glyph(x, y, im);

		vowel2[i] = glyph;
		m_vowels.emplace_back(yhchar(yh_conso::null_c, yh_csmod::null_m, yh_vowel(i), yh_vowel(i)), glyph);
	}

	for (int i = 1; i < yh_vowel::COUNT_v; ++i) {
		for (int j = 1; j < yh_vowel::COUNT_v; ++j) {
			if (i == j)
				continue;

			m_vowels.emplace_back(yhchar(yh_conso::null_c, yh_csmod::null_m, yh_vowel(i), yh_vowel(j)), vowel2[i] | vowel[j]);
		}
	}
}

void GlyphEnum::genTo(const fs::path& dir) {
	if (!fs::exists(dir)) {
		fs::create_directory(dir);
	}
	if (!fs::is_directory(dir))
		return;

	std::set<yhchar_bits> bucket;
	int off = 0xE000;

	for (auto& i : m_consonants) {
		auto im = gen_glyph(i.second);

		cv::imwrite((dir / std::format("{0:04X}.bmp", i.first.code + off)).string(), im);
	}

	for (auto& i : m_vowels) {
		auto im = gen_glyph(i.second);

		cv::imwrite((dir / std::format("{0:04X}.bmp", i.first.code + off)).string(), im);
	}

	for (auto& i : m_consonants) {
		for (auto& j : m_vowels) {
			auto im = gen_glyph(i.second | j.second);
			auto code = (i.first.code | j.first.code);

			if (bucket.contains(code)) {
				cout << std::format("{0:04X} {1:X} {2:X}", code, i.first.code, j.first.code) << endl;
				int a;
				cin >> a;
			}
			bucket.insert(code);

			cv::imwrite((dir / std::format("{0:04X}.bmp", code + off, i.first.code, j.first.code)).string(), im);
		}
	}
}
