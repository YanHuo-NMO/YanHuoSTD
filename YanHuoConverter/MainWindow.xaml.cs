using System.IO;
using System.Windows;
using System.Windows.Media;

namespace YanHuoConverter;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window {

	private readonly FontFamily m_font;

	public MainWindow() {
		InitializeComponent();

#if DEBUG
		string fontpath = Path.Combine(Environment.CurrentDirectory, "../publish/YanHuoSTD.ttf");
#else
		string fontpath = Path.Combine(Environment.CurrentDirectory, "YanHuoSTD.ttf");
#endif
		m_font = new FontFamily(new Uri(fontpath), "./#YanHuo STD");
		if (m_font == null)
			throw new Exception();

		textBox1.FontSize = 18;
	}

	private void Button_Click(object sender, RoutedEventArgs e) {
		string str = textBox1.Text;

		string res = "";

		Yhchar yhchar = new();
		bool lastIsSpace = true;

		for (int i = 0, n = str.Length; i < n; i++) {
			lastIsSpace = i > 0 && str[i - 1] == ' ';
			char curch = str[i];
			char[] curs = [curch];

			switch (curch) {
			case 'I':
			case 'E':
			case 'U':
			case 'A':
			case 'W':
			case 'O':
				if (!Enum.TryParse(typeof(VowelEnum), curs, out var vob) || vob is not VowelEnum v)
					break;
				//if (yhchar.Empty()) {
					//yhchar.SetConsonant(ConsoEnum.X);
					//yhchar.SetModifier(ModifEnum.minus);
				//}
				if (yhchar.GetVowel() == 0) {
					yhchar.SetVowel1(v);
					continue;
				}
				if (yhchar.GetVowel2() == 0) {
					yhchar.SetVowel2(v);
					continue;
				}
				i--;
				break;

			case 'X':
			case 'P':
			case 'T':
			case 'K':
			case 'H':
			case 'M':
			case 'N':
			case 'R':
			case 'S':
				if (!Enum.TryParse(typeof(ConsoEnum), curs, out var cob) || cob is not ConsoEnum c)
					break;
				if (yhchar.GetConsonant() == 0) {
					yhchar.SetConsonant(c);
					continue;
				}
				i--;
				break;

			case '-':
				if (yhchar.GetConsonant() != 0) {
					yhchar.SetModifier(ModifEnum.minus);
				}
				continue;
			case '+':
				if (yhchar.GetConsonant() != 0) {
					yhchar.SetModifier(ModifEnum.plus);
				}
				continue;
			case '\'':
				if (yhchar.GetConsonant() != 0) {
					yhchar.SetModifier(ModifEnum.prime);
				}
				continue;

			case ' ':
				if (yhchar.Empty() && lastIsSpace) {
					res += ' ';
					continue;
				}
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (yhchar.Empty()) {
					res += curch;
					continue;
				}
				i--;
				break;

			default:
				if (yhchar.Empty())
					continue;
				break;
			}
			if (yhchar.Empty())
				continue;
			res += yhchar.ToChar();
			yhchar = new();
		}

		/// 如果还残余字的一部分，直接将残体加入结果。
		if (!yhchar.Empty()) {
			res += yhchar.ToChar();
			//yhchar = new();
		}

		textBox2.Clear();
		textBox2.FontFamily = m_font;
		textBox2.FontSize = 72;
		textBox2.Text = res;
	}
}
