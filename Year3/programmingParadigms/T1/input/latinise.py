import re, sys

def latinise(filename: str):
    shadda = re.compile(r'(.)ّ')
    long_a = re.compile(r'aa(?!a|u|i)')
    long_u = re.compile(r'uw(?!a|u|i)')
    long_i = re.compile(r'iy(?!a|u|i)')

    with open(filename, encoding='utf8') as mu:
        text = mu.read()

    with open('Latinised '+filename, 'w', encoding='utf8') as mu:
        SUBSTITUTIONS_LIST = {
            'ء':"'",
            'ئ':"'",
            'أ':"'",
            'إ':"'",
            'ا':'a',
            'ى':'a',
            'آ':'ā',
            'ب':'b',
            'ت':'t',
            'ة':'t',
            'ث':'ṯ',
            'ج':'j',
            'ح':'ḥ',
            'خ':'ḵ',
            'د':'d',
            'ذ':'ḏ',
            'ر':'r',
            'ز':'z',
            'س':'s',
            'ش':'š',
            'ص':'ṣ',
            'ض':'ḍ',
            'ط':'ṭ',
            'ظ':'ẓ',
            'ع':'e',
            'غ':'g',
            'ف':'f',
            'ق':'q',
            'ك':'k',
            'ل':'l',
            'م':'m',
            'ن':'n',
            'ه':'h',
            'و':'w',
            'ي':'y',
            'َ':'a',
            'ُ':'u',
            'ِ':'i',
            'ً':'an',
            'ٌ':'un',
            'ٍ':'in',
            'ْ':'', # sukoon
            '؟':'?',
            '،':',',
            '؛':';'
        }
        text = shadda.sub(r'\1\1', text)
        text = text.replace('ًا','ً')  # to avoid عرفًا becoming "eurfana"
        for letter in SUBSTITUTIONS_LIST:
            text = text.replace(letter, SUBSTITUTIONS_LIST[letter])
        text = long_a.sub('ā', text)
        text = long_u.sub('ū', text)
        text = long_i.sub('ī', text)
        mu.write(text)

if __name__ == '__main__':
    try:
        filename = sys.argv[1]
    except IndexError:
        print("Please provide a filename.")

    latinise(filename)