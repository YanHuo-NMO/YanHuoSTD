namespace YanHuoConverter {
	internal enum ConsoEnum : uint {
		null_c, X, P, T, K, H, M, N, R, S, COUNT
	};

	internal enum ModifEnum : uint {
		null_m, minus, plus, prime, COUNT
	};

	internal enum VowelEnum : uint {
		null_v, I, E, U, A, W, O, COUNT
	};

	internal struct Yhchar {
		private uint code;

		public readonly ushort Code {
			get {
				return (ushort)code;
			}
		}

		public Yhchar() {
			code = 0;
		}
		public Yhchar(uint _code) {
			code = _code;
		}
		public Yhchar(uint _conso, uint _mod) {
			code = ((_mod & 0x3) << 6) | ((_conso & 0xf) << 8);
		}
		public Yhchar(uint _conso, uint _mod, uint _vowel, uint _vowel2) {
			code = (_vowel & 0x7) | ((_vowel2 & 0x7) << 3) | ((_mod & 0x3) << 6) | ((_conso & 0xf) << 8);
		}

		public readonly bool Empty() {
			return code == 0;
		}
		public readonly char ToChar() {
			return (char)(Code + 0xE000);
		}


		public void SetConsonant(ConsoEnum conso) {
			code |= ((uint)conso & 0xf) << 8;
		}
		public void SetModifier(ModifEnum modif) {
			code |= ((uint)modif & 0x3) << 6;
		}
		public void SetVowel1(VowelEnum vowel1) {
			code |= (uint)vowel1 & 0x7;
		}
		public void SetVowel2(VowelEnum vowel2) {
			code |= ((uint)vowel2 & 0x7) << 3;
		}

		public readonly uint GetConsonant() {
			return (code >> 8) & 0xf;
		}
		public readonly uint GetConsonantModifier() {
			return (code >> 6) & 0x3;
		}
		public readonly uint GetVowel() {
			return code & 0x7;
		}
		public readonly uint GetVowel2() {
			return (code >> 3) & 0x7;
		}
	}
}
