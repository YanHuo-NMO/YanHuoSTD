#pragma once

#include <cstdint>

typedef int16_t yhchar_bits;
typedef int32_t yh_glyph;

enum yh_conso {
	null_c, X, P, T, K, H, M, N, R, S, COUNT_c
};

enum yh_csmod {
	null_m, minus, plus, prime, COUNT_m
};

enum yh_vowel {
	null_v, I, E, U, A, W, O, COUNT_v
};

struct yhchar {
	yhchar_bits code;

	yhchar();
	yhchar(yhchar_bits _code);
	yhchar(yh_conso _conso, yh_csmod _mod, yh_vowel _vowel, yh_vowel _vowel2);

	yh_conso GetConsonant() const;
	yh_csmod GetConsonantModifier() const;
	yh_vowel GetVowel() const;
	yh_vowel GetVowel2() const;

	bool operator < (const yhchar& _r) const {
		return code < _r.code;
	}
};

