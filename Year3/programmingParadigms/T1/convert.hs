{-# LANGUAGE OverloadedStrings, UnicodeSyntax #-}
import System.Environment
import ClassyPrelude (singleton)
import System.FilePath.Posix  (takeBaseName)
import Data.List
import Data.Char
import Data.Text as T (Text, pack, unpack, replace, concat)
import Text.Megaparsec
import Text.Megaparsec.Char
import Data.Void (Void)
import Data.List.Split
import System.Directory
import System.Exit
import Data.Typeable
import Data.Maybe
import Data.Either

{-
Program to replace markup text with html. Some functionality was written with the help of the official Megaparsec tutorial at: https://markkarpov.com/tutorial/megaparsec.html
-}

type Parser = Parsec Void Text  -- parser type to prevent having to type out Parsec Void Text all the time

exclusionList = ["^", "%", "&", "#", "?", "/140", "/141", "/142", "/143", "/2 ", "/20", "/27", "/3 ", "/8 ", "/18", "/15", "/45"]
exclusionList2 = ["^", "%", "&", "#", "?", "/140", "/141", "/142", "/143", "/2 ", "/20", "/27", "/3 ", "/8 ", "/18", "/15", "/45"]

removeTashkeel xs = [x | x <- xs, not (x `elem` ['ً'..'ْ'])]    -- function to remove tashkeel

headers = ["/1", "/7", "/30", "/80"]

{-function to detect h1 pattern
return: returns text wrapped in header tags while removing markup-}
h1 :: Parser Text
h1 = try $ do           -- try to backtrack and not fail completely if parser doesn't succeed
    _ <- (string "/1 ")   -- look for /1 in text
    _ <- many spaceChar   -- check for 0 or more spaces
    text <- manyTill (anySingleBut '\n') (lookAhead (string " /1"))   -- any character except newline and /1
    _ <- many spaceChar
    _ <- (string "/1 ")
    space   -- look for space character
    _ <- many (char ':')  -- zero or more of : character
    return (T.concat ["<h1>", (pack text), "</h1>"])  -- return text wrapped with <h1></h1>

{-function to detect h2 pattern
return: returns text wrapped in header tags while removing markup-}
h2 :: Parser Text
h2 = do 
    _ <- (string "/7 ") 
    _ <- many spaceChar
    text <- manyTill anySingle (lookAhead (string " /7"))   -- any character until  /7 without consuming  /7
    _ <- many spaceChar
    _ <- (string "/7 ")
    space
    _ <- many (char ':')
    return (T.concat ["<h2>", (pack text), "</h2>"])

{-function to detect h3 pattern
return: returns text wrapped in header tags while removing markup-}
h3 :: Parser Text
h3 = do 
    _ <- (string "/30")
    _ <- many spaceChar
    text <- manyTill anySingle (lookAhead (string "/30"))
    _ <- many spaceChar
    _ <- (string "/30")
    space
    _ <- many (char ':')
    return (T.concat ["<h3>", (pack text), "</h3>"])

{-function to detect h4 pattern
return: returns text wrapped in header tags while removing markup-}
h4 :: Parser Text
h4 = do 
    _ <- (string "/80")
    _ <- many spaceChar
    text <- manyTill anySingle (lookAhead (string " /80"))
    _ <- many spaceChar
    _ <- (string "/80")
    space
    _ <- many (char ':')
    return (T.concat ["<h4>", (pack text), "</h4>"])

{-function to detect p1 pattern
return: returns text wrapped in paragraph tags while removing markup-}
p1 :: Parser Text
p1 = do 
    at <- string "@"
    text <- (manyTill anySingle newline)
    return (T.concat ["<p>", at, (pack text), "</p>"])

{-function to remove tags in exclusionList2 pattern
return: returns empty string-}
exclusionListRemoval :: Parser Text
exclusionListRemoval = do 
              tag <- choice exclusionList2
              return ""

{-function to detect info1 pattern
return: returns text wrapped in span tags while removing markup-}
info1 :: Parser Text
info1 = try $ do
        _ <- (string "/13") <|> (string "/23")    -- parse /13 or /23
        text <- manyTill anySingle ((string "/13") <|> (string "/23"))  --parse until /13 or /23
        return (T.concat ["<span class=\"info1\" title=\"زيادة علم\">(&nbsp;", (pack text), "&nbsp;)</span>"])

{-function to detect info2 pattern
return: returns text wrapped in span tags while removing markup-}
info2 :: Parser Text
info2 = do
        tag <- (string "/10") <|> (string "/70") <|> (string "/72") <|> (string "/74") <|> (string "/75")
        text <- manyTill anySingle (string tag)
        return (T.concat ["<span class=\"info2\" title=\"زيادة علم\">(&nbsp;", (pack text), "&nbsp;)</span>"])

{-function to detect place pattern
return: returns text wrapped in span tags while removing markup-}
place :: Parser Text
place = do
        _ <- (string "/60")
        text <- manyTill anySingle (string "/60")
        return (T.concat ["<span class=\"place\" title=\"مكان\">", (pack text), "</span>"])

{-function to detect p2 pattern
return: returns text wrapped in span tags and adding <p> to the beginning while removing markup-}
p2 :: Parser Text
p2 = try $ do
    _ <- (char '$')
    paragraphNumber <- some numberChar    -- parse one or more numbers
    text <- (manyTill anySingle (lookAhead (Text.Megaparsec.oneOf ['ء'..'ٓ'])))    -- parse until character in range of ['ء'..'ٓ']
    haddathana <- manyTill (Text.Megaparsec.oneOf ['ء'..'ٓ']) (lookAhead (char ' '))    -- parse characters ['ء'..'ٓ'] until space
    return (T.concat ["<p><span class=\"number\">", (pack paragraphNumber), "</span>", "<span class=\"haddathana\">", pack haddathana, "</span>"])

{-function to detect p2End pattern
return: returns string to signify end of paragraph with </p>-}
p2End :: Parser Text
p2End = do
      _ <- char '*'
      return ".</p>"

{-function to detect author pattern
return: returns text wrapped in span tags while removing markup-}
author :: Parser Text
author = try $ do 
        _ <- string "/12"
        space1
        text <- manyTill anySingle (string "/12")
        return (T.concat ["<span class=\"author\" title=\"المصنِّف\">", (pack text), "</span>"])


specialList = ["/22", "/55", "/56", "/57", "/58", "/59", "/64", "/71", "/73"]   -- list of tags to look out for in special function

{-function to detect special pattern
return: returns text wrapped in span tags while removing markup-}
special :: Parser Text
special = try $ do
        tag <- choice specialList   -- parse one of tags in specialList
        space1  
        text <- manyTill anySingle (string tag)
        return (T.concat ["<span class=\"special\" title=\"عَلَم\">", pack text, "</span>"])

{-function to replace comma with ،
return: returns text form of ،-}
replaceComma :: Parser Text
replaceComma = do
              _ <- (char ',')
              return "،"

{-function to replace semicolon with ؛
return: returns text of ؛-}
replaceSemicolon :: Parser Text
replaceSemicolon = do
                _ <- (char ';')
                return "؛"

{-function to detect salah pattern
return: returns text of span wrapped condenced salah-}
replaceSalah :: Parser Text
replaceSalah = do
            _ <- (string "صلى الله عليه وسلم")
            return "<span class=\"salah\">ﷺ</span>"

{-function to detect quran mentions
return: returns text wrapped in span tags while removing markup-}
quranMention :: Parser Text
quranMention = do
        _ <- (string "/33") <|> (string "/65")
        text <- manyTill anySingle ((string "/33") <|> (string "/65"))
        return (T.concat ["<span class=\"quran\">", (pack text), "</span>"])

{-function to detect quran
return: returns text of quran wrapped in span tags and additional information while removing markup-}
quran :: Parser Text
quran = do
      _ <- (string "/4 ")
      first <- manyTill anySingle (lookAhead ("سورة"))
      stuff1 <- (string "سورة")
      second <- manyTill anySingle (lookAhead ("آية"))
      stuff2 <- (string "آية")
      third <- manyTill (numberChar <|> char '-' <|> spaceChar) (lookAhead (char '/'))
      _ <- (string "/4")
      return (T.concat ["<span class=\"quran\"><span class=\"leftmargin\">", (pack second), " ", (pack third), "</span>", (pack first), "</span>"])

{-function to detect quran without reference
return: returns text wrapped in span tags while removing markup-}
quranWithoutRef :: Parser Text
quranWithoutRef = do
                  _ <- (string "/4 ")
                  text <- manyTill (anySingle <|> spaceChar) (lookAhead ((string "/4")))
                  _ <- (string "/4") 
                  return (T.concat ["<span class=\"quran\">", (pack text), "</span>"])

{-function to detect narrator pattern
return: returns text wrapped in span tags with narrator information while removing markup-}
narrator :: Parser Text
narrator = try $ do
          tag <- (:) <$> char '/' <*> (some numberChar)   -- parse any /nr once
          if (tag) `elem` exclusionList then return "" else do  -- check if found tag is in exclusionList and return empty string if true
            text <- takeWhileP Nothing (\c -> c /= 'L')   -- take while character is not L
            _ <- char 'L'
            id <- (manyTill numberChar (lookAhead (char ' ')))
            _ <- manyTill spaceChar (lookAhead (char '/'))
            _ <- (string (pack tag))
            return (T.concat ["<span class=\"css_class_for_", (pack id), "_\" title=\"", (pack id), "\">", text, "</span>"])

inclusionList = ["/26", "/93", "/94"]

{-function to detect ungraded narrator pattern
return: returns text wrapped in span tags while removing markup-}
narratorUngraded :: Parser Text
narratorUngraded = try $ do
                  tag <- (:) <$> char '/' <*> (some numberChar)   -- parse any /nr once
                  if (tag) `elem` inclusionList then do   -- check if parsed tag is in inclusionList
                  text <- manyTill (anySingleBut 'L') (lookAhead (string (pack tag)))   -- if tag in inclusionList parse unless L until same tag is found again
                  _ <- (string (pack tag))
                  return (T.concat ["<span class=\"narrator_ungraded\" title=\"(راو)\">", (pack text), "</span>"])
                  else return ("")

{-function to find html tags denoting graded narrators and add narrator info taken from a csv file to the html
return: returns narrator text with added info in html tags-}
gradeNarrators :: [([Char], [[Char]])] -> Parser Text
gradeNarrators input = do
                _ <- (string "css_class_for_")
                id <- (manyTill numberChar (char '_'))
                let narrator = lookup id input    -- look for narrator in input data
                _ <- (string "\" title=\"")
                _ <- (manyTill numberChar (char '"')) 
                if narrator /= Nothing then do     -- if narrator is found in input
                    let name = (fromJust narrator)!!0   -- get narrator details and save to variables
                    let grade = (fromJust narrator)!!1
                    let gradeText = (fromJust narrator)!!2
                    let generation = (fromJust narrator)!!3
                    let total = (fromJust narrator)!!4
                    return (T.concat ["grade_color_", (pack grade), "\" title=\"", (pack name), "  -  ", (pack gradeText), "   (م", (pack grade), " - ط", (pack generation), " - ح", (pack total), ")\""])
                else do
                    return (T.concat ["not_in_db", " title=\"(", (pack id), "<\"(ليس في قاعدة البيانات "])  

{-function to detect poem verse 1 pattern
return: returns text wrapped in div tags while removing markup-}
poemVerse1 :: Parser Text
poemVerse1 = try $ do
            _ <- (string "/50")
            _ <- some spaceChar
            _ <- (string "/51")
            _ <- some spaceChar
            text <- manyTill (anySingle <|> spaceChar) (lookAhead (char '/'))
            _ <- (string "/51")
            _ <- some spaceChar
            _ <- (string "/50")
            _ <- many spaceChar
            _ <- many (char '،')
            _ <- many (char '.')
            return (T.concat ["<div class=\"poem_verse\">", (pack text), "</div>"])

{-function to detect poem verse 2 pattern
return: returns text wrapped in div tags while removing markup-}
poemVerse2 :: Parser Text
poemVerse2 = try $ do
            _ <- (string "/50")
            _ <- some spaceChar
            _ <- (string "/51")
            _ <- some spaceChar
            text1 <- manyTill (anySingle <|> spaceChar) (lookAhead (char '/'))
            _ <- (string "/51")
            _ <- some spaceChar
            _ <- (string "/51")
            text2 <- manyTill (anySingle <|> spaceChar) (lookAhead (char '/'))
            _ <- (string "/51")
            _ <- some spaceChar
            _ <- (string "/50")
            _ <- some spaceChar
            _ <- many (char '،')
            _ <- many (char '.')
            return (T.concat ["<div class=\"poem_verse\">", (pack text1), " ... ", (pack text2), "</div>"])

{-function to remove character E from text
return: returns empty text-}
eNumber :: Parser Text
eNumber = do
        _ <- (:) <$> char 'E' <*> (manyTill numberChar (lookAhead (char ' ')))
        return ""


{-function to detect haddathana pattern
return: returns text wrapped in span tags while removing markup-}
haddathana :: Parser Text
haddathana = try $ do
  _ <- lookAhead (string "@" <|> string"$")
  text <- lookAhead (manyTill anySingle (lookAhead (Text.Megaparsec.oneOf ['ء'..'ٓ'])))
  haddathana <- manyTill (Text.Megaparsec.oneOf ['ء'..'ٓ']) (lookAhead (char ' '))
  return $ (T.concat ["<span class=\"haddathana\">", pack haddathana, "</span>"])

{-function to detect page number pattern
return: returns text wrapped in span tags while removing markup-}
pageNumber :: Parser Text
pageNumber = try $ do
  _ <- char '@'
  space
  n <- some numberChar
  space
  _ <- char ':'
  space
  n2 <- some numberChar
  space
  _ <- char '@'
  return (T.concat ["<span class=\"pagenumber\">", (pack n), " / ", (pack n2), "</span>"])

{-function to parse text to remove markup and replace with html-}
parseText :: Parser [Text]
parseText = many $ 
            ((replaceSalah
            <|> replaceComma
            <|> replaceSemicolon
            <|> eNumber
            <|> h1
            <|> h2
            <|> h3
            <|> h4
            <|> p2End
            <|> p2
            <|> quran
            <|> quranWithoutRef
            <|> quranMention
            <|> special
            <|> place
            <|> poemVerse1
            <|> poemVerse2
            <|> narratorUngraded
            <|> narrator)  
            <|> (singleton <$> anySingle))    -- if none of the above parsers succeed or fit, parse single character

{-function to parse text to remove markup and replace with html. Separated to prevent parsing conflicts-}
parseSensitiveText :: Parser [Text]
parseSensitiveText = many $
  (pageNumber <|> haddathana <|> exclusionListRemoval <|> (singleton <$> anySingle))

{-function to parse text to remove markup and replace with html. Separated to prevent parsing conflicts-}
parseParagraph :: Parser [Text]
parseParagraph = many $ (p1 <|> (singleton <$> anySingle))

parseSensitiveText2 :: Parser [Text]
parseSensitiveText2 = many $ ((info1 <|> info2 <|> place <|> quran) <|> (singleton <$> anySingle))

{-function to concatenate parsed text back together from list-}
concatenateSensitiveText2 :: Parser Text
concatenateSensitiveText2 = T.concat <$> parseSensitiveText2

concatenateSensitiveText :: Parser Text
concatenateSensitiveText = T.concat <$> parseSensitiveText

{-function to parse and add narrator data to text-}
parseNarrators :: [([Char], [[Char]])] -> Parser [Text]
parseNarrators input = many $
  ((gradeNarrators input) <|> (singleton <$> anySingle))

concatenateText = T.concat <$> parseText

concatenateGradedText input = T.concat <$> (parseNarrators input)

concatenateParagraph = T.concat <$> parseParagraph

main = do
      file <- getArgs   -- get arguments provided by user
      if length file > 0 then   -- make sure user passed file name
            do
              boolFile <- doesFileExist ("input/" ++ file!!0)   -- make sure file exists
              if boolFile then
                    do
                    
                      template <- readFile "input/template.html"    -- get template information
                      contents <- readFile ("input/" ++ file!!0)    -- get text to convert from markup to html
                      narratorCSV <- readFile "input/narrators.csv"   -- get narrator information
                      
                      let narrators = map (\(x:xs) -> (x, xs)) (map (splitOn ",") (lines narratorCSV))    -- convert csv to a usable state
                      let initial = runParser (concatenateSensitiveText2) "file" (pack (removeTashkeel contents))   -- parse over text
                      
                      case initial of 
                        (Right initial) -> do   -- if parsing was successful
                          let result = runParser concatenateSensitiveText "file" initial    -- parse over text again
                          case result of
                            (Right result) -> do
                              let anotherResult = runParser concatenateText "file" result
                              case anotherResult of
                                (Right anotherResult) -> do
                                  let paragraphResult = runParser concatenateParagraph "file" anotherResult
                                  case paragraphResult of
                                    (Right paragraphResult) -> do
                                      let gradedResult = runParser (concatenateGradedText narrators) "file" paragraphResult   -- parse over text to add narrator grade details
                                      case gradedResult of
                                        (Right gradedResult) -> do
                                          let htmlTags = ["%%AUTHOR%%", "%%TITLE%%", "%%BODY%%"]    -- tags to replace with text or text information
                                          let changeTags (x:xs) = case x of { "%%TITLE%%" -> (replace x (pack (takeBaseName (file!!0))) (changeTags xs));
                                                                                        "%%AUTHOR%%" -> (replace x "" (changeTags xs));
                                                                                        "%%BODY%%" -> (replace x gradedResult (pack template)) }
                                          writeFile ("output/" ++ (takeBaseName (file!!0) ++ ".html")) (unpack (changeTags htmlTags))   -- write parsed text to new file in output folder
                                        Left err -> (putStrLn "Fail5")    -- show what parsing step parser failed at if parser fails
                                    Left err -> (putStrLn "Fail4")
                                Left err -> (putStrLn "Fail3")
                            Left err -> (putStrLn "Fail2")
                        Left err -> (putStrLn "Fail1")
              else
                exitWith (ExitFailure 1)
      else
        exitWith (ExitFailure 1)
