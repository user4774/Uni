# Task 1 (Haskell): Convert a Markup Language to HTML

A charity has approached you to help them convert marked-up texts into HTML.
The texts are made of a sequence of headings and paragraphs.
Most paragraphs start with a chain of *narrators*, one narrating from the next, until they reach the final narrator, whose saying is to be highlighted.

The narrators are enclosed in a pattern "`/d ..... LD /d`", where `d` and `D` are numbers (`L` is the literal letter 'L').

The texts are in Arabic, but Latinised copies can be generated using the Python script `latinise.py`.

Below is a Latinised example where the markup is shown in bold:

> **E1** **/1** `musnadu aleašarati almubaššarīna bialjannati` **/1** **/30** `musnadu alḵulafā'i alrrāšidīna` **/30** **/7** `musnadu 'abī bakrin alṣṣiddīqi raḍiya alllahu eanhu` **/7**
> 
> **$1**  **1** **/2** **/140** ḥaddaṯanā **/94** `eabdu alllahi bnu numayrin` **L5128 /94** , qāla : 'aḵbaranā **/26** `'ismāeīlu yaenī abna 'abī ḵālidin` **L989 /26** , ean **/26** `qaysin` **L6508 /26** , qāla : **/27** qāma **/93** `'abū bakrin` **L4945 /93** , faḥamida alllaha wa'aṯnā ealayhi , ṯumma qāla : yā 'ayyuhā alnnāsu , 'innakum taqra'ūna haḏihi alāyata : **/4** `ya'ayyuhā allaḏīna āmanuwa ealaykum 'anfusakum la yaḍurrukum man ḍalla 'iḏā ahtadaytum` **swrt alma'dt āyt 105 /4** , wa'innā samienā rasūla alllahi ṣallā alllahu ealayhi wasallama , yaqūlu : **/20** " 'inna alnnāsa 'iḏā ra'awa almunkara falam yuggiyirwh , 'awšaka 'an yaeummahumu alllahu bieiqābihi " **/27 *** 

When this is convereted it would show like this (with the provided CSS style sheet and fonts):

![](example.png)

The meaning of some tags:

| Tag | Meaning        |  | Tag | Meaning        |  | Tag | Meaning        |
|-----|----------------|--|-----|----------------|--|-----|----------------|
| /1  | Heading 1      |  | /7  | Heading 2      |  | /30  | Heading 3     |
| /26 | Narrator       |  | /94 | First narrator |  | /93 | Last narrator  |

You are also given a file `input/narrators.csv` containing **reliability grades** and short **biographical information** on the narrators.
(Header: *ID,Name,Grade,Grade text,Generation,Total*.)

Your task is to use Haskell to create a converter that mimics the Python solution `convert.py` provided on the [template GitHub repository under the folder `T1`].


> Regarding the non-POSIX regex's, you have at least two options:
>
> 1. Find a library that supports them. You are permitted to use such libraries as long as they can be installed using  `stack install`  on Codio.
> 2. Design your own POSIX regex's. Use e.g. <https://regex101.com> to test and debug them. (I recommend testing them on a Latinised copy of the text to avoid any right-to-left issues.)
>	In particular, many of the "`.+?`" may be replaced with "`[^/]+`" or "`[^\s/]+`" -- try it!
