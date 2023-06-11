import re, csv, sys

# -
# Read narrators data and store as dictionary for use later on
# -


def load_narrators():
    NARRATOR = dict()
    with open("input/narrators.csv", encoding='utf8') as file_narrators:
        csv_narrators = csv.DictReader(file_narrators)
        for row in csv_narrators:
            NARRATOR[row['ID']] = row
    return NARRATOR

# -
# Load the marked-up text, and start processing the mark-up using regular expressions
# -


re_h1 = re.compile(r'/1\s+(.+?)\s*/1(\s*:)?')
re_h2 = re.compile(r'/7\s+(.+?)\s*/7(\s*:)?')
re_h3 = re.compile(r'/30\s+(.+?)\s*/30(\s*:)?')
re_h4 = re.compile(r'/80\s+(.+?)\s*/80(\s*:)?')
re_p1 = re.compile(r'@\s*(.+?)$', re.MULTILINE)
re_p2 = re.compile(r'\$(\d+)[ 0-9/]+\s*(.+)\*')
re_narrator = re.compile(r'(/\d+)\s*([^/]+?)\s*L(\d+)\s*\1\b')
re_author = re.compile(r'/12\s+(.+?)\s+/12\b')
re_narrator_ungraded = re.compile(r'/(26|93|94)\s*([^/L]+?)\s*/\1\b')
re_special = re.compile(r'/(22|55|56|57|58|59|64|71|73)\s+(.+?)\s+/\1\b')
re_info1 = re.compile(r'/(13|23)\s+(.+?)\s+/\1\b')
re_info2 = re.compile(r'/(10|70|72|74|75)\s+(.+?)\s+/\1\b')
re_place = re.compile(r'/60\s+(.+?)\s+/60\b')
re_quran = re.compile(r'/4 (.+?) سورة (.+?) آية ([ 0-9-]+) /4\b') # use [^/]+? instead?
re_quran_without_ref = re.compile(r'/4 (.+?) /4\b') # use [^/]+? instead?
re_quran_mention = re.compile(r'/(33|65) (.+?) /\1\b')
re_page_number = re.compile(r'@\s*(\d+)\s*:\s*(\d+)\s*@')
re_poem_verse1 = re.compile(r'/50\s+/51\s+([^/]+)\s+/51\s+/50\s*[\.،]?')
re_poem_verse2 = re.compile(r'/50\s+/51\s+([^/]+)\s+/51\s+/51\s+([^/]+)\s+/51\s+/50\s*[\.،]?', re.DOTALL)
re_haddathana = re.compile(r'([\$@][^\u0621-\u0653]+?)([\u0621-\u0653]+) ')

re_remove_E_d = re.compile(r'E\d+')

# For Unicode see e.g. https://unicode-table.com/en/blocks/arabic/
re_arabic_without_tashkeel = re.compile(r'[^ \u0621-\u064a]')  # ء-ي  --  "tashkeel" -> short vowels
re_remove_tashkeel = re.compile(r'[\u064b-\u0652]')  # َ ً ُ ٌ ِ ٍ ْ ّ

def convert_markup_to_html(filename: str, NARRATOR: dict, remove_tashkeel=True):
    with open(f"input/{filename}", encoding='utf8') as textfile:
        text = textfile.read()

    if remove_tashkeel is True:
        text = re_remove_tashkeel.sub('', text)  # for simplicity...
        text = text.replace('صلى الله عليه وسلم', '<span class="salah">ﷺ</span>')
    text = text.replace(',', '،')
    text = text.replace(';', '؛')
    text = re_page_number.sub(r'<span class="pagenumber">\1 / \2</span>', text)
    text = re_haddathana.sub(r'\1<span class="haddathana">\2</span> ', text)
    # Ignored markup
    text = re_remove_E_d.sub('', text)
    for markup in ["^", "%", "&", "#", "/140 ", "/141 ", "/142 ", "/143", '/2 ', '/20', '/27', '/3 ', '/8 ', '/18 ', '/15 ', '/45 ']:
        text = text.replace(markup, '')

    # --
    text = re_h1.sub(r'<h1>\1</h1>', text)
    text = re_h2.sub(r'<h2>\1</h2>', text)
    text = re_h3.sub(r'<h3>\1</h3>', text)
    text = re_h4.sub(r'<b>\1</b>', text)  # todo
    text = re_p2.sub(r'<p><span class="number">\1</span>\2.</p>', text)
    text = re_p1.sub(r'<p>\1</p>', text)
    text = re_quran.sub(r'<span class="quran"><span class="leftmargin">\2 \3</span>\1</span>', text)
    text = re_quran_without_ref.sub(r'<span class="quran">\1</span>', text)
    text = re_quran_mention.sub(r'<span class="quran">\2</span>', text)
    text = re_special.sub(r'<span class="special" title="عَلَم">\2</span>', text)
    # Bug? nested tags...
    text = re_info1.sub(r'<span class="info1" title="زيادة علم">(&nbsp;\2&nbsp;)</span>', text)
    text = re_info2.sub(r'<span class="info2" title="زيادة علم">‹&nbsp;\2&nbsp;›</span>', text)
    text = re_author.sub(r'<span class="author" title="المصنِّف">\1</span>', text)
    text = re_place.sub(r'<span class="place" title="مكان">\1</span>', text)
    text = re_poem_verse1.sub(r'<div class="poem_verse">\1</div>', text)
    text = re_poem_verse2.sub(r'<div class="poem_verse">\1 ... \2</div>', text)
    # 'css_class_for_..._' will be transformed into a CSS class later on
    text = re_narrator.sub(r'<span class="css_class_for_\3_" title="\3">\2</span>', text)
    text = re_narrator_ungraded.sub(r'<span class="narrator_ungraded" title="(راو)">\2</span>', text)

    # -- Add narrators information

    re_css_for_narrator = re.compile(r'css_class_for_(\d+)_')
    unique_narrators_IDs = set(re_css_for_narrator.findall(text))
    for ID in unique_narrators_IDs:
        try:
            narrator = NARRATOR[ID]
            name = narrator['Name']
            grade = narrator['Grade']
            grade_text = narrator['Grade text']
            generation = narrator['Generation']
            total = narrator['Total']
        except KeyError:
            print(f"\tMissing narrator from database: ID={ID}")
            text = text.replace(f'css_class_for_{ID}_', 'not_in_db')
            text = text.replace(f'title="{ID}">', f'title="({ID} ليس في قاعدة البيانات)">')
            continue
        text = text.replace(f'css_class_for_{ID}_', f'grade_color_{grade}')
        text = text.replace(f'title="{ID}"', f'title="{name}  -  {grade_text}   (م{grade} - ط{generation} - ح{total})"') # طبقة - مرتبة - عدد أحاديثه

    # ---------------------------------

    with open("input/template.html", encoding='utf8') as file_template:
        HTML_TEMPLATE = file_template.read()
    HTML_TEMPLATE = HTML_TEMPLATE.replace('%%TITLE%%', re_arabic_without_tashkeel.sub('', filename))
    HTML_TEMPLATE = HTML_TEMPLATE.replace('%%AUTHOR%%', '')
    text = HTML_TEMPLATE.replace('%%BODY%%', text)
    with open(f"output/{filename[:-4]}.html", 'w', encoding='utf8') as file_html:
        file_html.write(text)


if __name__ == "__main__":
    try:
        filename = sys.argv[1]
        filename = re.sub(r'.+/([^/]+.txt)', r'\1', filename) # keep the file name only -- no path
    except IndexError:
        print("Please provide a filename.")
    
    NARRATOR = load_narrators()
    print("Converting:", filename)
    convert_markup_to_html(filename, NARRATOR)
