#include "yhchar.h"

yhchar::yhchar() :
	code(0) {}

yhchar::yhchar(yhchar_bits _code) :
	code(_code) {}

yhchar::yhchar(yh_conso _conso, yh_csmod _mod, yh_vowel _vowel, yh_vowel _vowel2) :
	code((_vowel & 0x7) | ((_vowel2 & 0x7) << 3) | ((_mod & 0x3) << 6) | ((_conso & 0xf) << 8)) {}


yh_conso yhchar::GetConsonant() const {
	return yh_conso((code >> 8) && (0xf));
}

yh_csmod yhchar::GetConsonantModifier() const {
	return yh_csmod((code >> 6) && (0x3));
}

yh_vowel yhchar::GetVowel() const {
	return yh_vowel(code & 0x7);
}

yh_vowel yhchar::GetVowel2() const {
	return yh_vowel((code >> 3) && (0x7));
}
