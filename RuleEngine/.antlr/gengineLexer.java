// Generated from /Users/ziqi/Desktop/C-Study/RuleEngine/gengine.g4 by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class gengineLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, NIL=6, RULE=7, AND=8, OR=9, CONC=10, 
		IF=11, ELSE=12, RETURN=13, TRUE=14, FALSE=15, NULL_LITERAL=16, SALIENCE=17, 
		BEGIN=18, END=19, SIMPLENAME=20, INT=21, PLUS=22, MINUS=23, DIV=24, MUL=25, 
		EQUALS=26, GT=27, LT=28, GTE=29, LTE=30, NOTEQUALS=31, NOT=32, ASSIGN=33, 
		SET=34, PLUSEQUAL=35, MINUSEQUAL=36, MULTIEQUAL=37, DIVEQUAL=38, LSQARE=39, 
		RSQARE=40, SEMICOLON=41, LR_BRACE=42, RR_BRACE=43, LR_BRACKET=44, RR_BRACKET=45, 
		DOT=46, DQUOTA_STRING=47, DOTTEDNAME=48, REAL_LITERAL=49, SL_COMMENT=50, 
		WS=51;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "DEC_DIGIT", "A", "B", "C", "D", 
			"E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", 
			"S", "T", "U", "V", "W", "X", "Y", "Z", "EXPONENT_NUM_PART", "NIL", "RULE", 
			"AND", "OR", "CONC", "IF", "ELSE", "RETURN", "TRUE", "FALSE", "NULL_LITERAL", 
			"SALIENCE", "BEGIN", "END", "SIMPLENAME", "INT", "PLUS", "MINUS", "DIV", 
			"MUL", "EQUALS", "GT", "LT", "GTE", "LTE", "NOTEQUALS", "NOT", "ASSIGN", 
			"SET", "PLUSEQUAL", "MINUSEQUAL", "MULTIEQUAL", "DIVEQUAL", "LSQARE", 
			"RSQARE", "SEMICOLON", "LR_BRACE", "RR_BRACE", "LR_BRACKET", "RR_BRACKET", 
			"DOT", "DQUOTA_STRING", "DOTTEDNAME", "REAL_LITERAL", "SL_COMMENT", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "','", "'@name'", "'@id'", "'@desc'", "'@sal'", null, null, "'&&'", 
			"'||'", null, null, null, null, null, null, null, null, null, null, null, 
			null, "'+'", "'-'", "'/'", "'*'", "'=='", "'>'", "'<'", "'>='", "'<='", 
			"'!='", "'!'", "':='", "'='", "'+='", "'-='", "'*='", "'/='", "'['", 
			"']'", "';'", "'{'", "'}'", "'('", "')'", "'.'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, "NIL", "RULE", "AND", "OR", "CONC", 
			"IF", "ELSE", "RETURN", "TRUE", "FALSE", "NULL_LITERAL", "SALIENCE", 
			"BEGIN", "END", "SIMPLENAME", "INT", "PLUS", "MINUS", "DIV", "MUL", "EQUALS", 
			"GT", "LT", "GTE", "LTE", "NOTEQUALS", "NOT", "ASSIGN", "SET", "PLUSEQUAL", 
			"MINUSEQUAL", "MULTIEQUAL", "DIVEQUAL", "LSQARE", "RSQARE", "SEMICOLON", 
			"LR_BRACE", "RR_BRACE", "LR_BRACKET", "RR_BRACKET", "DOT", "DQUOTA_STRING", 
			"DOTTEDNAME", "REAL_LITERAL", "SL_COMMENT", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public gengineLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "gengine.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\65\u01da\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t"+
		" \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t"+
		"+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64"+
		"\t\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t"+
		"=\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\4F\tF\4G\tG\4H\tH\4"+
		"I\tI\4J\tJ\4K\tK\4L\tL\4M\tM\4N\tN\4O\tO\4P\tP\3\2\3\2\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3"+
		"\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\f\3\f\3\r\3\r\3\16\3\16\3\17"+
		"\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\3\24\3\24\3\25\3\25\3\26"+
		"\3\26\3\27\3\27\3\30\3\30\3\31\3\31\3\32\3\32\3\33\3\33\3\34\3\34\3\35"+
		"\3\35\3\36\3\36\3\37\3\37\3 \3 \3!\3!\3\"\3\"\5\"\u00f1\n\"\3\"\6\"\u00f4"+
		"\n\"\r\"\16\"\u00f5\3#\3#\3#\3#\3$\3$\3$\3$\3$\3%\3%\3%\3&\3&\3&\3\'\3"+
		"\'\3\'\3\'\3\'\3(\3(\3(\3)\3)\3)\3)\3)\3*\3*\3*\3*\3*\3*\3*\3+\3+\3+\3"+
		"+\3+\3,\3,\3,\3,\3,\3,\3-\3-\3-\3-\3-\3.\3.\3.\3.\3.\3.\3.\3.\3.\3/\3"+
		"/\3/\3/\3/\3/\3\60\3\60\3\60\3\60\3\61\6\61\u013f\n\61\r\61\16\61\u0140"+
		"\3\61\7\61\u0144\n\61\f\61\16\61\u0147\13\61\3\62\6\62\u014a\n\62\r\62"+
		"\16\62\u014b\3\63\3\63\3\64\3\64\3\65\3\65\3\66\3\66\3\67\3\67\3\67\3"+
		"8\38\39\39\3:\3:\3:\3;\3;\3;\3<\3<\3<\3=\3=\3>\3>\3>\3?\3?\3@\3@\3@\3"+
		"A\3A\3A\3B\3B\3B\3C\3C\3C\3D\3D\3E\3E\3F\3F\3G\3G\3H\3H\3I\3I\3J\3J\3"+
		"K\3K\3L\3L\3L\3L\3L\3L\7L\u018f\nL\fL\16L\u0192\13L\3L\3L\3M\3M\3M\3M"+
		"\3N\6N\u019b\nN\rN\16N\u019c\5N\u019f\nN\3N\3N\6N\u01a3\nN\rN\16N\u01a4"+
		"\3N\6N\u01a8\nN\rN\16N\u01a9\3N\3N\3N\3N\6N\u01b0\nN\rN\16N\u01b1\5N\u01b4"+
		"\nN\3N\3N\6N\u01b8\nN\rN\16N\u01b9\3N\3N\3N\6N\u01bf\nN\rN\16N\u01c0\3"+
		"N\3N\5N\u01c5\nN\3O\3O\3O\3O\7O\u01cb\nO\fO\16O\u01ce\13O\3O\3O\3O\3O"+
		"\3P\6P\u01d5\nP\rP\16P\u01d6\3P\3P\3\u01cc\2Q\3\3\5\4\7\5\t\6\13\7\r\2"+
		"\17\2\21\2\23\2\25\2\27\2\31\2\33\2\35\2\37\2!\2#\2%\2\'\2)\2+\2-\2/\2"+
		"\61\2\63\2\65\2\67\29\2;\2=\2?\2A\2C\2E\bG\tI\nK\13M\fO\rQ\16S\17U\20"+
		"W\21Y\22[\23]\24_\25a\26c\27e\30g\31i\32k\33m\34o\35q\36s\37u w!y\"{#"+
		"}$\177%\u0081&\u0083\'\u0085(\u0087)\u0089*\u008b+\u008d,\u008f-\u0091"+
		".\u0093/\u0095\60\u0097\61\u0099\62\u009b\63\u009d\64\u009f\65\3\2!\3"+
		"\2\62;\4\2CCcc\4\2DDdd\4\2EEee\4\2FFff\4\2GGgg\4\2HHhh\4\2IIii\4\2JJj"+
		"j\4\2KKkk\4\2LLll\4\2MMmm\4\2NNnn\4\2OOoo\4\2PPpp\4\2QQqq\4\2RRrr\4\2"+
		"SSss\4\2TTtt\4\2UUuu\4\2VVvv\4\2WWww\4\2XXxx\4\2YYyy\4\2ZZzz\4\2[[{{\4"+
		"\2\\\\||\5\2C\\aac|\6\2\62;C\\aac|\4\2$$^^\5\2\13\f\17\17\"\"\2\u01d2"+
		"\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2E\3\2\2"+
		"\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2"+
		"S\3\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3"+
		"\2\2\2\2a\3\2\2\2\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2"+
		"\2\2m\3\2\2\2\2o\3\2\2\2\2q\3\2\2\2\2s\3\2\2\2\2u\3\2\2\2\2w\3\2\2\2\2"+
		"y\3\2\2\2\2{\3\2\2\2\2}\3\2\2\2\2\177\3\2\2\2\2\u0081\3\2\2\2\2\u0083"+
		"\3\2\2\2\2\u0085\3\2\2\2\2\u0087\3\2\2\2\2\u0089\3\2\2\2\2\u008b\3\2\2"+
		"\2\2\u008d\3\2\2\2\2\u008f\3\2\2\2\2\u0091\3\2\2\2\2\u0093\3\2\2\2\2\u0095"+
		"\3\2\2\2\2\u0097\3\2\2\2\2\u0099\3\2\2\2\2\u009b\3\2\2\2\2\u009d\3\2\2"+
		"\2\2\u009f\3\2\2\2\3\u00a1\3\2\2\2\5\u00a3\3\2\2\2\7\u00a9\3\2\2\2\t\u00ad"+
		"\3\2\2\2\13\u00b3\3\2\2\2\r\u00b8\3\2\2\2\17\u00ba\3\2\2\2\21\u00bc\3"+
		"\2\2\2\23\u00be\3\2\2\2\25\u00c0\3\2\2\2\27\u00c2\3\2\2\2\31\u00c4\3\2"+
		"\2\2\33\u00c6\3\2\2\2\35\u00c8\3\2\2\2\37\u00ca\3\2\2\2!\u00cc\3\2\2\2"+
		"#\u00ce\3\2\2\2%\u00d0\3\2\2\2\'\u00d2\3\2\2\2)\u00d4\3\2\2\2+\u00d6\3"+
		"\2\2\2-\u00d8\3\2\2\2/\u00da\3\2\2\2\61\u00dc\3\2\2\2\63\u00de\3\2\2\2"+
		"\65\u00e0\3\2\2\2\67\u00e2\3\2\2\29\u00e4\3\2\2\2;\u00e6\3\2\2\2=\u00e8"+
		"\3\2\2\2?\u00ea\3\2\2\2A\u00ec\3\2\2\2C\u00ee\3\2\2\2E\u00f7\3\2\2\2G"+
		"\u00fb\3\2\2\2I\u0100\3\2\2\2K\u0103\3\2\2\2M\u0106\3\2\2\2O\u010b\3\2"+
		"\2\2Q\u010e\3\2\2\2S\u0113\3\2\2\2U\u011a\3\2\2\2W\u011f\3\2\2\2Y\u0125"+
		"\3\2\2\2[\u012a\3\2\2\2]\u0133\3\2\2\2_\u0139\3\2\2\2a\u013e\3\2\2\2c"+
		"\u0149\3\2\2\2e\u014d\3\2\2\2g\u014f\3\2\2\2i\u0151\3\2\2\2k\u0153\3\2"+
		"\2\2m\u0155\3\2\2\2o\u0158\3\2\2\2q\u015a\3\2\2\2s\u015c\3\2\2\2u\u015f"+
		"\3\2\2\2w\u0162\3\2\2\2y\u0165\3\2\2\2{\u0167\3\2\2\2}\u016a\3\2\2\2\177"+
		"\u016c\3\2\2\2\u0081\u016f\3\2\2\2\u0083\u0172\3\2\2\2\u0085\u0175\3\2"+
		"\2\2\u0087\u0178\3\2\2\2\u0089\u017a\3\2\2\2\u008b\u017c\3\2\2\2\u008d"+
		"\u017e\3\2\2\2\u008f\u0180\3\2\2\2\u0091\u0182\3\2\2\2\u0093\u0184\3\2"+
		"\2\2\u0095\u0186\3\2\2\2\u0097\u0188\3\2\2\2\u0099\u0195\3\2\2\2\u009b"+
		"\u01c4\3\2\2\2\u009d\u01c6\3\2\2\2\u009f\u01d4\3\2\2\2\u00a1\u00a2\7."+
		"\2\2\u00a2\4\3\2\2\2\u00a3\u00a4\7B\2\2\u00a4\u00a5\7p\2\2\u00a5\u00a6"+
		"\7c\2\2\u00a6\u00a7\7o\2\2\u00a7\u00a8\7g\2\2\u00a8\6\3\2\2\2\u00a9\u00aa"+
		"\7B\2\2\u00aa\u00ab\7k\2\2\u00ab\u00ac\7f\2\2\u00ac\b\3\2\2\2\u00ad\u00ae"+
		"\7B\2\2\u00ae\u00af\7f\2\2\u00af\u00b0\7g\2\2\u00b0\u00b1\7u\2\2\u00b1"+
		"\u00b2\7e\2\2\u00b2\n\3\2\2\2\u00b3\u00b4\7B\2\2\u00b4\u00b5\7u\2\2\u00b5"+
		"\u00b6\7c\2\2\u00b6\u00b7\7n\2\2\u00b7\f\3\2\2\2\u00b8\u00b9\t\2\2\2\u00b9"+
		"\16\3\2\2\2\u00ba\u00bb\t\3\2\2\u00bb\20\3\2\2\2\u00bc\u00bd\t\4\2\2\u00bd"+
		"\22\3\2\2\2\u00be\u00bf\t\5\2\2\u00bf\24\3\2\2\2\u00c0\u00c1\t\6\2\2\u00c1"+
		"\26\3\2\2\2\u00c2\u00c3\t\7\2\2\u00c3\30\3\2\2\2\u00c4\u00c5\t\b\2\2\u00c5"+
		"\32\3\2\2\2\u00c6\u00c7\t\t\2\2\u00c7\34\3\2\2\2\u00c8\u00c9\t\n\2\2\u00c9"+
		"\36\3\2\2\2\u00ca\u00cb\t\13\2\2\u00cb \3\2\2\2\u00cc\u00cd\t\f\2\2\u00cd"+
		"\"\3\2\2\2\u00ce\u00cf\t\r\2\2\u00cf$\3\2\2\2\u00d0\u00d1\t\16\2\2\u00d1"+
		"&\3\2\2\2\u00d2\u00d3\t\17\2\2\u00d3(\3\2\2\2\u00d4\u00d5\t\20\2\2\u00d5"+
		"*\3\2\2\2\u00d6\u00d7\t\21\2\2\u00d7,\3\2\2\2\u00d8\u00d9\t\22\2\2\u00d9"+
		".\3\2\2\2\u00da\u00db\t\23\2\2\u00db\60\3\2\2\2\u00dc\u00dd\t\24\2\2\u00dd"+
		"\62\3\2\2\2\u00de\u00df\t\25\2\2\u00df\64\3\2\2\2\u00e0\u00e1\t\26\2\2"+
		"\u00e1\66\3\2\2\2\u00e2\u00e3\t\27\2\2\u00e38\3\2\2\2\u00e4\u00e5\t\30"+
		"\2\2\u00e5:\3\2\2\2\u00e6\u00e7\t\31\2\2\u00e7<\3\2\2\2\u00e8\u00e9\t"+
		"\32\2\2\u00e9>\3\2\2\2\u00ea\u00eb\t\33\2\2\u00eb@\3\2\2\2\u00ec\u00ed"+
		"\t\34\2\2\u00edB\3\2\2\2\u00ee\u00f0\t\7\2\2\u00ef\u00f1\7/\2\2\u00f0"+
		"\u00ef\3\2\2\2\u00f0\u00f1\3\2\2\2\u00f1\u00f3\3\2\2\2\u00f2\u00f4\5\r"+
		"\7\2\u00f3\u00f2\3\2\2\2\u00f4\u00f5\3\2\2\2\u00f5\u00f3\3\2\2\2\u00f5"+
		"\u00f6\3\2\2\2\u00f6D\3\2\2\2\u00f7\u00f8\5)\25\2\u00f8\u00f9\5\37\20"+
		"\2\u00f9\u00fa\5%\23\2\u00faF\3\2\2\2\u00fb\u00fc\5\61\31\2\u00fc\u00fd"+
		"\5\67\34\2\u00fd\u00fe\5%\23\2\u00fe\u00ff\5\27\f\2\u00ffH\3\2\2\2\u0100"+
		"\u0101\7(\2\2\u0101\u0102\7(\2\2\u0102J\3\2\2\2\u0103\u0104\7~\2\2\u0104"+
		"\u0105\7~\2\2\u0105L\3\2\2\2\u0106\u0107\5\23\n\2\u0107\u0108\5+\26\2"+
		"\u0108\u0109\5)\25\2\u0109\u010a\5\23\n\2\u010aN\3\2\2\2\u010b\u010c\5"+
		"\37\20\2\u010c\u010d\5\31\r\2\u010dP\3\2\2\2\u010e\u010f\5\27\f\2\u010f"+
		"\u0110\5%\23\2\u0110\u0111\5\63\32\2\u0111\u0112\5\27\f\2\u0112R\3\2\2"+
		"\2\u0113\u0114\5\61\31\2\u0114\u0115\5\27\f\2\u0115\u0116\5\65\33\2\u0116"+
		"\u0117\5\67\34\2\u0117\u0118\5\61\31\2\u0118\u0119\5)\25\2\u0119T\3\2"+
		"\2\2\u011a\u011b\5\65\33\2\u011b\u011c\5\61\31\2\u011c\u011d\5\67\34\2"+
		"\u011d\u011e\5\27\f\2\u011eV\3\2\2\2\u011f\u0120\5\31\r\2\u0120\u0121"+
		"\5\17\b\2\u0121\u0122\5%\23\2\u0122\u0123\5\63\32\2\u0123\u0124\5\27\f"+
		"\2\u0124X\3\2\2\2\u0125\u0126\5)\25\2\u0126\u0127\5\67\34\2\u0127\u0128"+
		"\5%\23\2\u0128\u0129\5%\23\2\u0129Z\3\2\2\2\u012a\u012b\5\63\32\2\u012b"+
		"\u012c\5\17\b\2\u012c\u012d\5%\23\2\u012d\u012e\5\37\20\2\u012e\u012f"+
		"\5\27\f\2\u012f\u0130\5)\25\2\u0130\u0131\5\23\n\2\u0131\u0132\5\27\f"+
		"\2\u0132\\\3\2\2\2\u0133\u0134\5\21\t\2\u0134\u0135\5\27\f\2\u0135\u0136"+
		"\5\33\16\2\u0136\u0137\5\37\20\2\u0137\u0138\5)\25\2\u0138^\3\2\2\2\u0139"+
		"\u013a\5\27\f\2\u013a\u013b\5)\25\2\u013b\u013c\5\25\13\2\u013c`\3\2\2"+
		"\2\u013d\u013f\t\35\2\2\u013e\u013d\3\2\2\2\u013f\u0140\3\2\2\2\u0140"+
		"\u013e\3\2\2\2\u0140\u0141\3\2\2\2\u0141\u0145\3\2\2\2\u0142\u0144\t\36"+
		"\2\2\u0143\u0142\3\2\2\2\u0144\u0147\3\2\2\2\u0145\u0143\3\2\2\2\u0145"+
		"\u0146\3\2\2\2\u0146b\3\2\2\2\u0147\u0145\3\2\2\2\u0148\u014a\4\62;\2"+
		"\u0149\u0148\3\2\2\2\u014a\u014b\3\2\2\2\u014b\u0149\3\2\2\2\u014b\u014c"+
		"\3\2\2\2\u014cd\3\2\2\2\u014d\u014e\7-\2\2\u014ef\3\2\2\2\u014f\u0150"+
		"\7/\2\2\u0150h\3\2\2\2\u0151\u0152\7\61\2\2\u0152j\3\2\2\2\u0153\u0154"+
		"\7,\2\2\u0154l\3\2\2\2\u0155\u0156\7?\2\2\u0156\u0157\7?\2\2\u0157n\3"+
		"\2\2\2\u0158\u0159\7@\2\2\u0159p\3\2\2\2\u015a\u015b\7>\2\2\u015br\3\2"+
		"\2\2\u015c\u015d\7@\2\2\u015d\u015e\7?\2\2\u015et\3\2\2\2\u015f\u0160"+
		"\7>\2\2\u0160\u0161\7?\2\2\u0161v\3\2\2\2\u0162\u0163\7#\2\2\u0163\u0164"+
		"\7?\2\2\u0164x\3\2\2\2\u0165\u0166\7#\2\2\u0166z\3\2\2\2\u0167\u0168\7"+
		"<\2\2\u0168\u0169\7?\2\2\u0169|\3\2\2\2\u016a\u016b\7?\2\2\u016b~\3\2"+
		"\2\2\u016c\u016d\7-\2\2\u016d\u016e\7?\2\2\u016e\u0080\3\2\2\2\u016f\u0170"+
		"\7/\2\2\u0170\u0171\7?\2\2\u0171\u0082\3\2\2\2\u0172\u0173\7,\2\2\u0173"+
		"\u0174\7?\2\2\u0174\u0084\3\2\2\2\u0175\u0176\7\61\2\2\u0176\u0177\7?"+
		"\2\2\u0177\u0086\3\2\2\2\u0178\u0179\7]\2\2\u0179\u0088\3\2\2\2\u017a"+
		"\u017b\7_\2\2\u017b\u008a\3\2\2\2\u017c\u017d\7=\2\2\u017d\u008c\3\2\2"+
		"\2\u017e\u017f\7}\2\2\u017f\u008e\3\2\2\2\u0180\u0181\7\177\2\2\u0181"+
		"\u0090\3\2\2\2\u0182\u0183\7*\2\2\u0183\u0092\3\2\2\2\u0184\u0185\7+\2"+
		"\2\u0185\u0094\3\2\2\2\u0186\u0187\7\60\2\2\u0187\u0096\3\2\2\2\u0188"+
		"\u0190\7$\2\2\u0189\u018a\7^\2\2\u018a\u018f\13\2\2\2\u018b\u018c\7$\2"+
		"\2\u018c\u018f\7$\2\2\u018d\u018f\n\37\2\2\u018e\u0189\3\2\2\2\u018e\u018b"+
		"\3\2\2\2\u018e\u018d\3\2\2\2\u018f\u0192\3\2\2\2\u0190\u018e\3\2\2\2\u0190"+
		"\u0191\3\2\2\2\u0191\u0193\3\2\2\2\u0192\u0190\3\2\2\2\u0193\u0194\7$"+
		"\2\2\u0194\u0098\3\2\2\2\u0195\u0196\5a\61\2\u0196\u0197\5\u0095K\2\u0197"+
		"\u0198\5a\61\2\u0198\u009a\3\2\2\2\u0199\u019b\5\r\7\2\u019a\u0199\3\2"+
		"\2\2\u019b\u019c\3\2\2\2\u019c\u019a\3\2\2\2\u019c\u019d\3\2\2\2\u019d"+
		"\u019f\3\2\2\2\u019e\u019a\3\2\2\2\u019e\u019f\3\2\2\2\u019f\u01a0\3\2"+
		"\2\2\u01a0\u01a2\7\60\2\2\u01a1\u01a3\5\r\7\2\u01a2\u01a1\3\2\2\2\u01a3"+
		"\u01a4\3\2\2\2\u01a4\u01a2\3\2\2\2\u01a4\u01a5\3\2\2\2\u01a5\u01c5\3\2"+
		"\2\2\u01a6\u01a8\5\r\7\2\u01a7\u01a6\3\2\2\2\u01a8\u01a9\3\2\2\2\u01a9"+
		"\u01a7\3\2\2\2\u01a9\u01aa\3\2\2\2\u01aa\u01ab\3\2\2\2\u01ab\u01ac\7\60"+
		"\2\2\u01ac\u01ad\5C\"\2\u01ad\u01c5\3\2\2\2\u01ae\u01b0\5\r\7\2\u01af"+
		"\u01ae\3\2\2\2\u01b0\u01b1\3\2\2\2\u01b1\u01af\3\2\2\2\u01b1\u01b2\3\2"+
		"\2\2\u01b2\u01b4\3\2\2\2\u01b3\u01af\3\2\2\2\u01b3\u01b4\3\2\2\2\u01b4"+
		"\u01b5\3\2\2\2\u01b5\u01b7\7\60\2\2\u01b6\u01b8\5\r\7\2\u01b7\u01b6\3"+
		"\2\2\2\u01b8\u01b9\3\2\2\2\u01b9\u01b7\3\2\2\2\u01b9\u01ba\3\2\2\2\u01ba"+
		"\u01bb\3\2\2\2\u01bb\u01bc\5C\"\2\u01bc\u01c5\3\2\2\2\u01bd\u01bf\5\r"+
		"\7\2\u01be\u01bd\3\2\2\2\u01bf\u01c0\3\2\2\2\u01c0\u01be\3\2\2\2\u01c0"+
		"\u01c1\3\2\2\2\u01c1\u01c2\3\2\2\2\u01c2\u01c3\5C\"\2\u01c3\u01c5\3\2"+
		"\2\2\u01c4\u019e\3\2\2\2\u01c4\u01a7\3\2\2\2\u01c4\u01b3\3\2\2\2\u01c4"+
		"\u01be\3\2\2\2\u01c5\u009c\3\2\2\2\u01c6\u01c7\7\61\2\2\u01c7\u01c8\7"+
		"\61\2\2\u01c8\u01cc\3\2\2\2\u01c9\u01cb\13\2\2\2\u01ca\u01c9\3\2\2\2\u01cb"+
		"\u01ce\3\2\2\2\u01cc\u01cd\3\2\2\2\u01cc\u01ca\3\2\2\2\u01cd\u01cf\3\2"+
		"\2\2\u01ce\u01cc\3\2\2\2\u01cf\u01d0\7\f\2\2\u01d0\u01d1\3\2\2\2\u01d1"+
		"\u01d2\bO\2\2\u01d2\u009e\3\2\2\2\u01d3\u01d5\t \2\2\u01d4\u01d3\3\2\2"+
		"\2\u01d5\u01d6\3\2\2\2\u01d6\u01d4\3\2\2\2\u01d6\u01d7\3\2\2\2\u01d7\u01d8"+
		"\3\2\2\2\u01d8\u01d9\bP\2\2\u01d9\u00a0\3\2\2\2\26\2\u00f0\u00f5\u0140"+
		"\u0143\u0145\u014b\u018e\u0190\u019c\u019e\u01a4\u01a9\u01b1\u01b3\u01b9"+
		"\u01c0\u01c4\u01cc\u01d6\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}