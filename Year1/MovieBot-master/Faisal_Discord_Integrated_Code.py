import asyncio
from asyncio import TimeoutError

import discord
import requests
from discord import *
from discord.ext import commands
from YoutubeAPI import *
from movies import *
from search_keyword_lists import *
import random
import sqlite3

"""
To improve readability, larger lists including keywords have been stored in a separate document which is
imported here.
Other team members' files are also imported here to gain access to their functions.
General references:
https://discordpy.readthedocs.io/en/latest/api.html
https://discordpy.readthedocs.io/en/async/faq.html#where-can-i-use-await    
"""

bot = commands.Bot(command_prefix="", description="Movie bot for your entertainment!")


@bot.event
async def on_ready(): #this event function is called when the bot is run and ready to operate
    db = sqlite3.connect("bot.db")
    c = db.cursor()
    # Creates Watchlist table with primary key UserWatchlistID, a watchlist attribute that stores watchlists, and User_name attribute that stores username
    c.execute("CREATE TABLE IF NOT EXISTS Watchlist (UserWatchlistID INTEGER PRIMARY KEY AUTOINCREMENT, Watchlist TEXT, Username TEXT)")
    db.commit() # Saves changes to DB

    print("Bot is ready!")  # indicator on the console that the bot is up and running
    await bot.change_presence(activity=discord.Game(name=" with James' waifu"))  # customises bot 'playing game' status on discord


awaiting_answer = False
asked_name = ""


@bot.event
async def on_message(message):
    message.content = message.content.lower()  # inclusion of all indices of a user input, whether upper case or lower case, so case sensitivity is not a constraint
    if message.author == bot.user:  # this ensures the bot doesn't respond to itself nor misinterprets its responses as user inputs by halting the function if the message processed was sent by itself
        return
    # lists (tuples) of various responses & emojis relevant to specified user inputs to enhance bot personality
    hiResponses = ["Hello", "Hey", "Hi", "Yo"]
    hruResponses = ["I'm fine, thank you", "Not too bad", "Doing just fine", "I'm alright", "We gucci out here"]
    niceResponses = ["Good to know", "That's lovely", "Nice one", "Great", "Cheers", "Cool"]
    byeResponses = ["See ya", "See you", "See you in a bit", "Ttyl", "Don't forget your popcorn"]
    thanksResponses = ["My pleasure", "You're welcome", "No worries", "No need to thank me", "It's all gucci"]
    popcornResponses = ["You talkin' to me", "Who, me", "That's me", "What's up"]
    badResponses = ["Excuse me", "That's not very nice", "I dare you to say that again", "Take that back", "Not cool", "Sorry for that"]
    okResponses = ["Okay", "Alright then", "Glad you approve"]
    yesResponses = ["Speak up then, I ain't got all the time in the world", "Ask away", "What's up?"]
    misunderstoodResponses = ["I didn't quite get that", "I didn't understand that", "That is beyond the grasp of my understanding", "That didn't make sense to me", "I'm sorry, I didn't catch that"]
    goodEmojis = ["😊", "☺", "😉", "😄", "😃", "🙂", "😝"]
    badEmojis = ["😡", "🤬", "😠", "😑", "👿"]
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]

    global asked_name
    if awaiting_answer and asked_name == message.author:
        return
    if message.author == bot.user:
        return
    if message.content.startswith("."):
        return
    if "cinema" in message.content.lower() or "cinemas" in message.content.lower() or "theatre" in message.content.lower():
        return await cinema_finder(message)
    if "hi" or "hey" or "hello" or "how are you" or "you're" or "you are" or "hows" or "how's" or "good" or "fine" or "im" or "i'm" or "bad" or "bad" or "nice" or "cool" or "great" or "popcorn" or "yes" or "yeah" or "yup" or "ye" or "yeh" or "no" or "nah" or "nope" or "nope" or "bye" or "goodbye" or "goodnight" or "see ya" or "cya" or "bad" or "shit" or "shut up" or "fuck" or "ok" or "okay" or "alright" or "thanks" or "thank you" or "cheers" or "delete" or "deletewatchlist" or "create" or "createwatchlist" or "view" or "viewwatchlist" or "help" or "quote" or "quotes" in message.content:
        pass

    if message.content.startswith("hi") or message.content.startswith("hey") or message.content.startswith("hello"): #condition pointing to messages that start with specified phrases
        await message.channel.send(random.choice(hiResponses) + ", " + message.author.mention + "!" + " How are you? " + random.choice(goodEmojis)) #bot will return a response by randomly choosing a relevant response (element from the relevant tuple) and mentioning the user on discord
    elif message.content.startswith("how are you") or message.content.startswith("you're") or message.content.startswith("you are") or message.content.startswith("hows") or message.content.startswith("how's"):
        await message.channel.send(random.choice(hruResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    elif message.content.startswith("good") or message.content.startswith("fine") or message.content.startswith("im") or message.content.startswith("i'm") or message.content.startswith("bad") or message.content.startswith("nice") or message.content.startswith("cool") or message.content.startswith("great"):
        await message.channel.send(random.choice(niceResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    elif message.content.startswith("popcorn"):
        await message.channel.send(random.choice(popcornResponses) + ", " + message.author.mention + "? " + "🍿")
    elif message.content.startswith("yes") or message.content.startswith("yeah") or message.content.startswith("yup") or message.content.startswith("ye") or message.content.startswith("yeh"):
        await message.channel.send(random.choice(yesResponses) + " " + message.author.mention + " " + random.choice(misunderstoodEmojis))
    elif message.content.startswith("no") or message.content.startswith("nah") or message.content.startswith("nope") or message.content.startswith("stop"):
        await message.channel.send("I'll just go back to sleep with my popcorn waifu then... " + message.author.mention + " 🤪👊")
    elif message.content.startswith("bye") or message.content.startswith("goodbye") or message.content.startswith("cya") or message.content.startswith("see ya") or message.content.startswith("goodnight"):
        await message.channel.send(random.choice(byeResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis) + "👋")
    elif message.content.startswith("fuck") or message.content.startswith("bad") or message.content.startswith("shit") or message.content.startswith("shut up"):
        await message.channel.send(random.choice(badResponses) + ", " + message.author.mention + "! " + random.choice(badEmojis))
    elif message.content.startswith("ok") or message.content.startswith("okay") or message.content.startswith("alright"):
        await message.channel.send(random.choice(okResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    elif message.content.startswith("thanks") or message.content.startswith("thank you") or message.content.startswith("cheers"):
        await message.channel.send(random.choice(thanksResponses) + " " + message.author.mention + "!" + " " + random.choice(goodEmojis))
    elif message.content.startswith("deletewatchlist") or message.content.startswith("delete"):
        pass
    elif message.content.startswith("createwatchlist") or message.content.startswith("create"):
        pass
    elif message.content.startswith("help"):
        pass
    elif message.content.startswith("view") or message.content.startswith("viewwatchlist"):
        pass
    elif message.content.startswith("quote") or message.content.startswith("quotes"): #this elif clause ensures the on_message() function does not overlap with the quote command function
        pass
    elif message.content not in positive_response_list and message.content not in negative_response_list:
        await asyncio.create_task(find_is_film(message, bot))
    else:
        await message.channel.send(random.choice(misunderstoodResponses) + ", " + message.author.mention + ". " + random.choice(misunderstoodEmojis))  #gives feedback on misunderstood user inputs

    await bot.process_commands(message) #allows for commands to execute without the event (on_message()) function interfering or overlapping



#command that returns random popular movie quote when triggered
@bot.command(aliases = ["quotes"], description = ": Random quotes from the best movies this century!", brief = ": Random quotes from the best movies this century!") #aliase refers to alternative command trigger 'quotes', description/brief explains what the command does on README document
async def quote(cntxt): #function name 'quote' is the primary command trigger a user can input
    #quotes is a list that stores movie quotes as elements, with movie reference and its year of release
    quotes = ["Just keep swimming. | Finding Nemo (2003)", "What's the most you ever lost on a coin toss? | No Country for Old Men (2007)", "Well, I don't want to survive. I want to live. | 12 Years a Slave (2013)", "I wish I knew how to quit you. | Brokeback Mountain (2005)", "May the odds ever be in your favor | The Hunger Games (2008)", "Are you not entertained? | Gladiator (2000)", "Chewie, we're home. | The Force Awakens (2015)", "I love lamp. | Anchorman: The Legend of Ron Burgundy (2004)", "You shall not pass! | Lord of the Rings: The Fellowship of the Ring (2001)", "That is so fetch. | Mean Girls (2004)", "I am Iron Man. | Iron Man (2008)", "You're going to go through life thinking that girls don't like you because you're a nerd. And I want you to know, from the bottom of my heart, that won't be true. It'll be because you're an a**hole. | The Social Network (2010)", "This is Sparta! | 300 (2006)", "I've been a poor man and I've been a rich man. And I choose rich every f****** time! | The Wolf of Wall Street (2013)", "With great power comes great responsibility. | Spider-Man (2002)", "I have nipples Greg. Could you milk me? | Meet the Parents (2000)", "Get off my lawn. | Gran Torino (2008)", "My precious. | Lord of the Rings: The Two Towers (2002)", "Argo f*** yourself. | Argo (2012)", "I love you, 3000. | Avengers: Endgame (2019)", "I am a golden god! | Almost Famous (2000)", "I drink your milkshake. I drink it up. | There Will Be Blood (2007)", "I am Groot. | Guardians of the Galaxy (2014)", "I'm just one stomach flu away from my goal weight. | The Devil Wears Prada (2006)", "Look at me. I'm the captain now. | Captain Phillips (2013)", "I don't have friends. I got family. | Furious 7 (2015)", "Ogres are like onions. | Shrek (2001)", "Dude, where's my car? | Dude, Where's My Car? (2000)", "I just wanted to take another look at you. | A Star Is Born (2018)", "You gotta hear this one song. It'll change your life, I swear. | Garden State (2004)", "King Kong ain't got shit on me! | Training Day (2001)", "I'm the guy who does his job. You must be the other guy. | The Departed (2006)", "You know how I know that you're gay? | The 40-Year-Old Virgin (2005)", "I could do this all day. | Captain America: Civil War (2016)", "It's the sense of touch. In any real city, you walk, you know? You brush past people, people bump into you. In L.A., nobody touches you. We're always behind this metal and glass. I think we miss that touch so much, that we crash into each other, just so we can feel something. | Crash (2004)", "Nobody makes me bleed my own blood. Nobody! | Dodgeball: A True Underdog Story (2004)", "That's my secret, Captain: I'm always angry. | Marvel's The Avengers (2012)", "I'm going to have to science the s*** out of this. | The Martian (2015)", "That's a bingo! | Inglourious Basterds (2009)", "Exercise gives you endorphins. Endorphins make you happy. Happy people just don't shoot their husbands. They just don't. | Legally Blonde (2001)", "I know who I am. I'm the dude playing a dude disguised as another dude! | Tropic Thunder (2008)", "Which would be worse, to live a monster or die as a good man? | Shutter Island (2010)", "Release the Kraken! | Clash of the Titans (2010)", "It is the titular role! | Lady Bird (2017)", "In one of our designs even these mosquito bites will look like juicy, juicy mangoes! | Bend It Like Beckham (2002)", "I wanna rob. | The Bling Ring (2013)", "You're putting the pussy on a pedestal. | The 40-Year-Old Virgin (2005)", "Didn't I tell you not to come to my house? Nobody touches my child! | Obsessed (2009)", "Hell is a teenage girl. | Jennifer's Body (2009)", "You gonna eat your tots? | Napoleon Dynamite (2004)", "To me, you are perfect. | Love Actually (2003)", "For a guy with a four digit IQ, I must have missed something. | Limitless (2011)", "My tastes are very singular. | Fifty Shades of Grey (2015)", "Do you know what happens to a toad when it's struck by lightning? The same thing that happens to everything else. | X-Men (2000)", "In moonlight, black boys look blue. | Moonlight (2016)", "Look at my shit. | Spring Breakers (2012)", "Just keep swimming. | Finding Nemo (2003)", "Girl, you can't get no infection in your booty hole! It's a booty hole! | Girls Trip (2017)", "I volunteer as tribute. | Hunger Games (2012)", "With great power comes great responsibility. | Spider-Man (2002)", "Would that it were so simple. | Hail, Caesar! (2016)", "Ass to ass. | Requiem for a Dream (2000)", "You will ride eternal, shiny and chrome. | Mad Max: Fury Road (2015)", "I am the motherf***er that found this place, sir. | Zero Dark Thirty (2012)", "Kiss me, my girl, before I am sick. | Phantom Thread (2017)", "I'm glad he's single because I'm going to climb that like a tree. | Bridesmaids (2011)", "Not the bees! | The Wicker Man (2006)", "Dear 8-pound, 6-ounce newborn infant Jesus... | Talladega Nights: The Ballad of Ricky Bobby (2006)", "Would it be all right if I showed the children the whoring bed? | Nymphomaniac Part I (2014)", "I was perfect. | Black Swan (2010)", "I know that babies taste the best. | Snowpiercer (2013)", "Honey? Where's my super suit? | The Incredibles (2004)", "Meet me in Montauk. | Eternal Sunshine of the Spotless Mind (2004)", "Now you're in the sunken place. | Get Out (2017)", "Why so serious? | The Dark Knight (2008)", "Is this your king? | Black Panther (2018)", "I have had it with these motherfuckin' snakes on this motherfu**in' plane! | Snakes on a Plane (2006)", "Look at my shit. | Spring Breakers (2012)", "I am Shiva, the god of death. | Michael Clayton (2007)", "Boy, that escalated quickly. | Anchorman: The Legend of Ron Burgundy (2004)", "King Kong ain't got shit on me! | Training Day (2001)", "I wish I knew how to quit you. | Brokeback Mountain (2005)", "I drink your milkshake. | There Will Be Blood (2007)", "I live my life a quarter mile at a time. | The Fast and the Furious (2001)", "I'm a fiend for mojitos. | Miami Vice (2006)", "Wouldst thou like to live deliciously? | The VVitch (2016)", "You sit on a throne of lies. | Elf (2003)", "My wife! | Borat (2006)", "But what I do have are a very particular set of skills, skills I have acquired over a very long career, skills that make me a nightmare for people like you. | Taken (2008)", "Which would be worse, to live a monster or die as a good man? | Shutter Island (2010)", "I know who I am. I'm the dude playing a dude disguised as another dude! | Tropic Thunder (2008)", "Perfection is not just about control. It's also about letting go. Surprise yourself so you can surprise the audience. Transcendence! And very few have it in them | Black Swan (2010)", "No amount of money ever bought a second of time. | Avengers: Endgame (2019)", "Eyes, lungs, pancreas. So many snacks, so little time. | Venom (2018)", "Assume everyone will betray you, and you will never be disappointed. | Solo: A Star Wars Story (2018)", "You know, the world's full of lonely people afraid to make the first move. | Green Book (2008)", "Mmm. They say money can’t buy happiness, darlings! But it does allow you to give it away! | Bohemian Rhapsody (2018)", "Wakanda will no longer watch from the shadows. We can not. We must not. We will work to be an example of how we as brothers and sisters on this earth should treat each other. Now, more than ever, the illusions of division threaten our very existence. We all know the truth: more connects us than separates us. But in times of crisis, the wise build bridges, while the foolish build barriers. We must find a way to look after one another, as if we were one single tribe. | Black Panther (2018)", "You know, Logan. This is what life looks like. A home, people who love each other. Safe place. You should take a moment and feel it. | Logan (2017)", "A man I knew used to say that hope was like your car keys. Easy to lose, but if you dig around, it's usually close by. | Justice League (2017)", "You don’t need everyone to love you, Phin. Just a few good people. | The Greatest Showman (2017)", "In this business, the moment you catch feelings is the moment you catch a bullet. | Baby Driver (2017)", "Thinking you can have a happy family and coach little leagues, and make car payments? Normal's a setting on the dryer. People like us, we don't get normal! | Suicide Squad (2016)", "People will want to go to it, because you're passionate about it. And people love what other people are passionate about. You remind people of what they forgot. | La La Land (2016)", "Our very strength incites challenge. Challenge incites conflict. And conflict... breeds catastrophe. | Captain America: Civil War (2016)", "Life is an endless series of train wrecks with only brief commercial-like breaks of happiness. | Deadpool (2016)", "The key to a happy life is to accept you are never actually in control. | Jurassic World (2015)", "They say that once you grow crops somewhere, you've officially colonized it. So, technically, I colonized Mars. In your face, Neil Armstrong! | The Martian (2015)", "When you pray for rain, you gotta deal with the mud too. | The Equalizer (2014)", "Hardest time to lie to somebody is when they’re expecting to be lied to. | The Imitation Game (2014)", "And as my father used to say, failure is the fog through which we glimpse triumph. | Iron Man 3 (2013)", "Hope. It is the only thing stronger than fear. A little hope is effective. A lot of hope is dangerous. A spark is fine, as long as it's contained. | The Hunger Games (2012)", "Happy Hunger Games! And may the odds be ever in your favor. | The Hunger Games (2012)", "You know, I've left so many behind. My family, the zoo, India, Anandi. I suppose, in the end, the whole of life becomes an act of letting go. But what always hurts the most is not taking a moment to say goodbye. | Life of Pi (2012)", "Hope. It is the only thing stronger than fear. A little hope is effective. A lot of hope is dangerous. A spark is fine, as long as it's contained. | The Hunger Games (2012)", "A hero can be anyone. Even a man doing something as simple and reassuring as putting a coat around a young boy’s shoulders to let him know the world hadn’t ended. | The Dark Knight Rises (2012)"]
    emojis = ["🍿", "🥤", "🎥", "🎬"]
    await cntxt.send(random.choice(quotes) + " " + cntxt.message.author.mention + " " + random.choice(emojis)) #random quote will be chosen from list and returned to user as well as mention user on discord

#command that allows the user to create a watchlist that can be accessed at any time
@bot.command(aliases = ["create", "Create", "Createwatchlist"], description = ": Create & save a movie watchlist!", brief = ": Create & save a movie watchlist!")
async def createwatchlist(cntxt, *, watchlist):
    username = cntxt.author
    realUsername = str(username)
    watchlist = str(watchlist)
    db = sqlite3.connect("bot.db")
    c = db.cursor()
    c.execute("SELECT Username FROM Watchlist WHERE Username = '" + realUsername + "'")
    if c.fetchall() == []:
        db = sqlite3.connect("bot.db")
        c = db.cursor()
        c.execute("INSERT INTO Watchlist(Username, Watchlist) VALUES('" + realUsername + "', '" + watchlist + "')")
        db.commit()
        await cntxt.send("You have successfully created a movie watchlist, " + cntxt.message.author.mention + "!" + " 🥳")
    else:
        await cntxt.send("Sorry, " + cntxt.message.author.mention + "," + " you can't have more than one watchlist." + " 😶")

#command that allows the user to view their watchlist after creation
@bot.command(aliases = ["view", "View", "Viewwatchlist"], description = ": View your movie watchlist!", brief = ": View your movie watchlist!")
async def viewwatchlist(cntxt):
    emojis = ["🍿", "🥤", "🎥", "🎬"]
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]
    username = cntxt.author
    realUsername = str(username)
    db = sqlite3.connect("bot.db")
    c = db.cursor()
    c.execute("SELECT Watchlist FROM Watchlist WHERE Username = '" + realUsername + "' ") #reminder to edit database so this sql statement works
    result = c.fetchall()
    if result == []:
        await cntxt.send("You don't have a movie watchlist to view, " + cntxt.message.author.mention + "!" + " " + random.choice(misunderstoodEmojis))
    else:
        for movie in result:
            await cntxt.send("Your movie watchlist: " + movie[0] + " | " + cntxt.message.author.mention + " " + random.choice(emojis))

#command that allows the user to delete their current watchlist
@bot.command(aliases = ["delete", "Delete", "Deletewatchlist"], description = ": Delete your movie watchlist!", brief = ": Delete your movie watchlist!")
async def deletewatchlist(cntxt):
    emojis = ["🍿", "🥤", "🎥", "🎬"]
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]
    username = cntxt.author
    realUsername = str(username)
    db = sqlite3.connect("bot.db")
    c = db.cursor()
    c.execute("SELECT Watchlist FROM Watchlist WHERE Username = '" + realUsername + "' ")
    if c.fetchall() == []:
        await cntxt.send("Sorry, " + cntxt.message.author.mention + ", I can't delete a watchlist that doesn't exist!" + " " + random.choice(misunderstoodEmojis))
    else:
        db = sqlite3.connect("bot.db")
        c = db.cursor()
        c.execute("DELETE FROM Watchlist WHERE Username = '" + realUsername + "' ")
        db.commit()
        await cntxt.send("Your movie watchlist has been deleted. Feel free to make a new one, " + cntxt.message.author.mention + "!" + " " + random.choice(emojis))


def strip_punctuation(user_input):
    """This function removes all punctuation from a user input to avoid confusing any keywords."""
    empty_list = []
    for char in user_input:
        if char.isalnum() or char == " " or char == "'":
            empty_list.append(char)
    stripped_user_input = "".join(empty_list)
    return stripped_user_input


async def find_is_film(message, bot):
    """
    This function carries out the most immediate search on the user input to determine whether they have simply
    written the name of a film. If this is the case, the function asks what they want to know and calls a new
    function to determine this. If the input is not a direct match for a film, the function passes the string to a
    separate function to determine what the input otherwise may be.
    """
    global awaiting_answer
    global asked_name
    goodEmojis = ["😊", "☺", "😉", "😄", "😃", "🙂", "😝"]
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]
    movie = omdb_get_request(message.content)
    if movie and 'Error' not in movie and check_input(message):
        movie_with_year = movie.get("Title") + ", " + movie.get("Year")
        await message.channel.send("Do you mean: " + movie_with_year + ", " + message.author.mention + "? " + random.choice(goodEmojis))
        asked_name = message.author
        awaiting_answer = True
        try:
            response = await bot.wait_for('message', timeout=15.0, check=lambda reply: reply.author != bot.user)
            if response.content.lower() in positive_response_list:
                await message.channel.send("What would you like to know about " + movie.get("Title") + ", " + message.author.mention + "? " + random.choice(goodEmojis))
                response = await bot.wait_for('message')
                await find_search_topic(response, movie.get("Title"), message)
                awaiting_answer = False
                return

            elif response.content.lower() in negative_response_list:
                movie_dict = get_imdb_list(message.content)
                for key in movie_dict:
                    selection = movie_dict.get(key)
                    movie_dict_year = selection[0] + ', ' + selection[1]
                    if movie_dict_year == movie_with_year:
                        continue

                    await message.channel.send("What about: " + movie_dict_year + ", " + message.author.mention + "? " + random.choice(misunderstoodEmojis))
                    asked_name = message.author
                    awaiting_answer = True
                    try:
                        response = await bot.wait_for('message', timeout=15.0,
                                                      check=lambda reply: reply.author != bot.user)
                        if response.content.lower() in negative_response_list:
                            continue
                        elif response.content.lower() in positive_response_list:
                            movie = selection[0]
                            await message.channel.send("What would you like to know about "
                                                       + movie_dict_year + ", " + message.author.mention + "? " + random.choice(goodEmojis))
                            response = await bot.wait_for('message', timeout=15.0)
                            await find_search_topic(response, movie, message)
                            awaiting_answer = False
                            return
                        elif response.content.lower() in stop_keywords_list:
                            await message.channel.send("Never mind then, " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
                            return
                        else:
                            await message.channel.send("Never mind then, " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
                            awaiting_answer = False
                            return

                    except TimeoutError:
                        await message.channel.send("Never mind then, " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
                        awaiting_answer = False
                        return
            else:
                await message.channel.send("Never mind then, " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
                awaiting_answer = False
                return
        except TimeoutError:
            await message.channel.send("Never mind then, " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
            awaiting_answer = False
            return
    elif movie and 'Error' not in movie and not check_input(message):
        await message.channel.send("So you're asking something about a movie... " + message.author.mention + " " + random.choice(misunderstoodEmojis))
    else:
        # print("You've not mentioned a movie in here, do you just want to chat?")
        await find_input(message)


async def film_check(message, possible_name):
    """
    This function carries out the most immediate search on the user input to determine whether they have simply
    written the name of a film. If this is the case, the function asks what they want to know and calls a new
    function to determine this. If the input is not a direct match for a film, the function passes the string to a
    separate function to determine what the input otherwise may be.
    """
    global awaiting_answer
    global asked_name
    movie = omdb_get_request(possible_name)
    if movie and 'Error' not in movie:
        movie_with_year = movie.get("Title") + ", " + movie.get("Year")
        await message.channel.send("Do you mean: " + movie_with_year + "?\n")
        asked_name = message.author
        awaiting_answer = True
        try:
            response = await bot.wait_for('message', timeout=15.0, check=lambda reply: reply.author == message.author)
            if response.content.lower() in positive_response_list:
                awaiting_answer = False
                return movie.get("Title")

            elif response.content.lower() in negative_response_list:
                movie_dict = get_imdb_list(possible_name)
                for key in movie_dict:
                    selection = movie_dict.get(key)
                    movie_dict_year = selection[0] + ', ' + selection[1]
                    if movie_dict_year == movie_with_year:
                        continue

                    await message.channel.send("What about: " + movie_dict_year + "?\n")
                    asked_name = message.author
                    awaiting_answer = True
                    try:
                        response = await bot.wait_for('message', timeout=15.0,
                                                      check=lambda reply: reply.author == message.author)
                        if response.content.lower() in negative_response_list:
                            continue
                        elif response.content.lower() in positive_response_list:
                            movie = selection[0]
                            awaiting_answer = False
                            return movie
                        else:
                            await message.channel.send("Never mind then")
                            awaiting_answer = False
                            return
                    except TimeoutError:
                        await message.channel.send("Never mind then")
                        awaiting_answer = False
                        return
            else:
                awaiting_answer = False
                return
        except TimeoutError:
            await message.channel.send("Never mind then")
            awaiting_answer = False
            return
    else:
        await message.channel.send("I can't find that movie")


def check_input(message):
    highest_probability = 0
    searches_list_index = 0
    for search_type in search_type_list:
        search_probability, search_code = search_type.search_keywords(message.content)
        if search_probability >= 5 and search_probability > highest_probability:
            highest_probability = search_probability
        searches_list_index += 1
    if highest_probability < 5:
        return True
    else:
        return False


async def find_input(message):
    """
    This function is called when the input does not exactly match a film title in its entirety and will work to
    determine what the user means by identifying potential keywords which indicate where in a sentence might be a
    title, and stripping words away until it finds a match. It does this by finding words that would typically come
    before a search topic, and then stripping the input from the following word until the end, then loops through,
    removing a word at a time until it gets a match. If there is no match, it carries out a similar function for words
    which would typically follow the title. If there is still no match, the string is passed on to another function to
    determine whether the text meets a different criteria.
    """
    user_input_no_punctuation = strip_punctuation(message.content)
    user_input_list = (user_input_no_punctuation.lower()).split()
    word_index = 0
    preceding_keyword_index = 0
    succeeding_keyword_index = 0
    preceding_keyword = False
    succeeding_keyword = False
    is_movie = False
    is_present = False
    is_location = 0
    for word in user_input_list:
        if word in preceding_keywords_list:
            if word == "is" or word == "was":
                if user_input_list[word_index + 1] in preceding_keywords_list:
                    word_index += 1
                elif word_index > 0 and user_input_list[word_index - 1] in preceding_keywords_list:
                    preceding_keyword = True
                    break
                else:
                    is_present = True
                    is_location = word_index
                    word_index += 1
                    continue
            preceding_keyword = True
            preceding_keyword_index = word_index
            break
        else:
            word_index += 1
    word_index = len(user_input_list)
    for word in reversed(user_input_list):
        if word in succeeding_keywords_list:
            succeeding_keyword = True
            succeeding_keyword_index = word_index
            break
        else:
            word_index -= 1
    loop_count = 0
    if is_present and succeeding_keyword:
        preceding_keyword = True
        preceding_keyword_index = is_location
    if preceding_keyword and preceding_keyword_index != len(user_input_list):
        after_keyword_list = user_input_list[preceding_keyword_index + 1:]
        while not is_movie and loop_count < len(user_input_list):
            possible_title = " ".join(after_keyword_list)
            is_movie = get_omdb_movie_details("Title", possible_title)
            if not is_movie:
                after_keyword_list = after_keyword_list[:len(after_keyword_list) - 1]
            else:
                movie_name = await film_check(message, possible_title)
                print(movie_name)
                input_without_title = " ".join(user_input_list[:preceding_keyword_index + 1]
                                               + user_input_list[(len(user_input_list) - loop_count):])
                if movie_name:
                    response = await find_search_topic(input_without_title, movie_name, message)
                else:
                    return
                return response
            loop_count += 1
    if succeeding_keyword:
        before_keyword_list = user_input_list[:succeeding_keyword_index - 1]
        while not is_movie:
            possible_title = " ".join(before_keyword_list)
            is_movie = get_omdb_movie_details("Title", possible_title)
            if not is_movie:
                before_keyword_list = before_keyword_list[1:]
            else:
                movie_name = await film_check(message, possible_title)
                input_without_title = " ".join(user_input_list[:loop_count]
                                               + user_input_list[succeeding_keyword_index - 1:])
                if movie_name:
                    response = await find_search_topic(input_without_title, movie_name, message)
                else:
                    response = await find_search_topic(input_without_title, is_movie, message)
                return response
            loop_count += 1
    else:
        return


class UserSearchTopics:
    """
    This class was developed to reduce repetition in the process of determining which search parameter is the most
    likely to have been searched for by the user.
    """

    def __init__(self, search_name_string, search_probability, list_high, list_medium, list_low, search_code):
        self.search_name_string = search_name_string
        self.search_probability = search_probability
        self.list_high = list_high
        self.list_medium = list_medium
        self.list_low = list_low
        self.search_code = search_code

    def search_keywords(self, user_input):
        """
        The following function assesses the user input and assigns a score to it against keywords for a given search
        criteria.
        """
        self.search_probability = 0
        for phrase in self.list_high:
            if phrase in user_input:
                self.search_probability += 10
        for phrase in self.list_medium:
            if phrase in user_input:
                self.search_probability += 5
        for phrase in self.list_low:
            if phrase in user_input:
                self.search_probability += 1
        return self.search_probability, self.search_code


"""
The following list assigns objects to each search criteria. A list has been used to aid in the later functions which
loop through it to assess the relevance of each search criteria
"""
search_type_list = [UserSearchTopics("age rating", 0, age_list_high, age_list_medium, age_list_low, "Rated"),
                    UserSearchTopics("review rating", 0, review_rating_list_high, review_rating_list_medium,
                                     review_rating_list_low, "Ratings"),
                    UserSearchTopics("synopsis", 0, synopsis_list_high, synopsis_list_medium, synopsis_list_low,
                                     "Plot"),
                    UserSearchTopics("trailer", 0, trailer_list_high, trailer_list_medium, trailer_list_low,
                                     ""),
                    UserSearchTopics("release year", 0, year_list_high, year_list_medium, year_list_low,
                                     "Year"),
                    UserSearchTopics("release date", 0, date_list_high, date_list_medium, date_list_low,
                                     "Released"),
                    UserSearchTopics("runtime", 0, runtime_list_high, runtime_list_medium, runtime_list_low,
                                     "Runtime"),
                    UserSearchTopics("genre", 0, genre_list_high, genre_list_medium, genre_list_low,
                                     "Genre"),
                    UserSearchTopics("director", 0, director_list_high, director_list_medium, director_list_low,
                                     "Director"),
                    UserSearchTopics("writer", 0, writer_list_high, writer_list_medium, writer_list_low,
                                     "Writer"),
                    UserSearchTopics("actors", 0, actor_list_high, actor_list_medium, actor_list_low,
                                     "Actors"),
                    UserSearchTopics("awards", 0, awards_list_high, awards_list_medium, awards_list_low,
                                     "Awards"),
                    UserSearchTopics("poster", 0, poster_list_high, poster_list_medium, poster_list_low,
                                     "Poster")]


async def find_search_topic(user_input, title, message):
    """
    This function loops through the different search types and carries out the "search_keywords" method from the
    above class on each one. In each iteration, the function compares the score of the search criteria against the
    previous highest scoring to determine which is the most likely type to be searched for. If the loop does not
    obtain a high enough score, it will pass the query back to the user and ask for clarification. Likewise,
    if multiple possibilities are tied, it will ask the user to determine which is correct.
    """
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]
    goodEmojis = ["😊", "☺", "😉", "😄", "😃", "🙂", "😝"]
    possible_matches = []
    global awaiting_answer
    global asked_name

    def check(m):
        return message.author == m.author and m.channel == message.channel

    loop_iteration = 0
    while loop_iteration < 3:
        if len(possible_matches) == 1:
            break

        if len(possible_matches) > 1:
            matches_string = ""
            matches_list_index = 0
            for matches in possible_matches:
                if matches == possible_matches[-1]:
                    matches_string = matches_string + " or " + search_type_list[matches_list_index].search_name_string \
                                     + "?\n"
                elif matches_string != "":
                    matches_string = matches_string + ", " + search_type_list[matches_list_index].search_name_string
                else:
                    matches_string = search_type_list[matches_list_index].search_name_string
                matches_list_index += 1
            await message.channel.send("Are you looking for " + matches_string + " " + message.author.mention + "? " + random.choice(goodEmojis))
            asked_name = message.author
            awaiting_answer = True
            try:
                user_input = await bot.wait_for("message", timeout=15.0,
                                                check=check)
                await find_search_topic(user_input, title, message)
                return
            except asyncio.TimeoutError:
                awaiting_answer = False
                return

        highest_probability = 0
        possible_matches.clear()
        searches_list_index = 0
        for search_type in search_type_list:
            if type(user_input) is Message:
                search_probability, search_code = search_type.search_keywords(user_input.content)
            else:
                search_probability, search_code = search_type.search_keywords(user_input)
            if search_probability >= 5 and search_probability > highest_probability:
                possible_matches.clear()
                highest_probability = search_probability
                possible_matches.append(searches_list_index)
            elif search_probability > 0 and search_probability == highest_probability:
                possible_matches.append(searches_list_index)
            searches_list_index += 1
        if highest_probability < 5 and loop_iteration < 3:
            await message.channel.send("I don't understand what you're asking, " + message.author.mention + "! " + random.choice(misunderstoodEmojis))
            asked_name = message.author
            awaiting_answer = True
            return

    loop_iteration += 1
    if len(possible_matches) == 1:
        await search_imdb(search_type_list[possible_matches[0]], title, message)
        return
    elif len(possible_matches) > 1:
        print("I don't think you're getting this...\n")

    return "Never mind then "


async def search_imdb(search_type_object, title, message):
    """
    This function takes the search topic as determined by the find_search_topic function, carries out the search,
    and returns the requested information to the user.
    """
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]
    goodEmojis = ["😊", "☺", "😉", "😄", "😃", "🙂", "😝"]
    if title.isdigit():
        movie_name = get_omdb_movie_details("Title", title)
    else:
        movie_name = title
    print(movie_name)
    if search_type_object.search_name_string == "trailer":
        release_year = get_omdb_movie_details("Year", title)
        try:
            trailer = outUrl(title + release_year)
            await message.channel.send("Here's the trailer for " + movie_name + ": " + str(trailer) + " " + message.author.mention)
        except TypeError:
            await message.channel.send("Sorry, I couldn't find a trailer for {}".format(title) + ", " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
        await asyncio.sleep(1)
        await follow_up(title, message)
    else:
        search_response = get_omdb_movie_details(search_type_object.search_code, title)
        try:
            if search_type_object.search_name_string == "review rating":
                await message.channel.send("The IMDb rating for " + movie_name + " is " + search_response[0]["Value"] + " " + message.author.mention + " " + random.choice(goodEmojis))
            elif search_type_object.search_name_string == "director":
                await message.channel.send(movie_name + " was directed by " + str(search_response) + " " + message.author.mention + " " + random.choice(goodEmojis))
            elif search_type_object.search_name_string == "writer":
                await message.channel.send(movie_name + " was written by " + str(search_response) + " " + message.author.mention + " " + random.choice(goodEmojis))
            elif search_type_object.search_name_string == "actors":
                await message.channel.send("Some of the actors that starred in " +
                                           movie_name + " were " + str(search_response) + " " + message.author.mention + " " + random.choice(goodEmojis))
            elif search_type_object.search_name_string == "awards":
                await message.channel.send(movie_name + " won the following awards; " + str(search_response) + " " + message.author.mention + " " + random.choice(goodEmojis))
            elif search_type_object.search_name_string == "poster":
                await message.channel.send("This is the poster for " + movie_name + ": " + str(search_response) + "\n" + " " + message.author.mention + " " + random.choice(goodEmojis))
            else:
                await message.channel.send("The " + search_type_object.search_name_string + " of " +
                                           movie_name + " is " + str(search_response) + " " + message.author.mention + " " + random.choice(goodEmojis))
        except IndexError:
            await message.channel.send("Sorry, I couldn't find the requested info")
        await asyncio.sleep(1)
        await follow_up(title, message)


async def follow_up(title, message):
        goodEmojis = ["😊", "☺", "😉", "😄", "😃", "🙂", "😝"]

        await message.channel.send("Would you like to know anything else about {0}".format(title) + ", " + message.author.mention + "? " + random.choice(goodEmojis))
        try:
            response = await bot.wait_for('message', timeout=15.0)
            if response.content.lower() in positive_response_list:
                await message.channel.send("What would you like to know" + ", " + message.author.mention + "? " + random.choice(goodEmojis))
                response = await bot.wait_for('message', timeout=15.0)
                await find_search_topic(response, title, message)
            elif response.content.lower() in negative_response_list:
                await message.channel.send("That's all then" + ", " + message.author.mention + ". " + random.choice(goodEmojis))
            elif response.content is None:
                pass
            else:
                await find_search_topic(response, title, message)
        except TimeoutError:
            await message.channel.send("That's all then" + ", " + message.author.mention + ". " + random.choice(goodEmojis))


async def cinema_finder(message):
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]
    goodEmojis = ["😊", "☺", "😉", "😄", "😃", "🙂", "😝"]
    global awaiting_answer
    global asked_name
    key = 'AIzaSyB0Qwc0X0pybqsVhss9eENMA5h1OcO4b9Y'

    def check(m):
        return message.author == m.author and m.channel == message.channel

    await message.channel.send("Where are you looking for a cinema near to" + ", " + message.author.mention + "? " + random.choice(goodEmojis))
    asked_name = message.author
    awaiting_answer = True
    try:
        user_location = await bot.wait_for("message", timeout=15.0, check=check)
    except TimeoutError:
        await message.channel.send("Never mind then" + ", " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
        awaiting_answer = False
        return
    lat_long_search = "https://maps.googleapis.com/maps/api/geocode/json?address=" + user_location.content.lower() \
                      + "&key=AIzaSyB0Qwc0X0pybqsVhss9eENMA5h1OcO4b9Y"
    latitude, longitude = str(requests.get(lat_long_search).json()['results'][0]['geometry']['location']['lat']), \
                          str(requests.get(lat_long_search).json()['results'][0]['geometry']['location']['lng'])
    # The following original search format was abandoned in favour of the below as it returned only one result
    #   cinema_search = "https://maps.googleapis.com/maps/api/place/findplacefromtext/json?input=cinema" \
    #                   "&inputtype=textquery&language=english&fields=formatted_address,name,opening_hours,rating" \
    #                   "&locationbias=circle:5000" + latitude + "," + longitude + "&key=" + key
    cinema_search = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=" + latitude + "," \
                    + longitude + "&radius=6000&keyword=cinema&key=" + key
    cinemas = requests.get(cinema_search).json()
    if cinemas['status'] != 'OK':
        await message.channel.send("Hmm... It doesn't look like there are any cinemas near there, want to try somewhere"
                                   " else" + ", " + message.author.mention + "? " + random.choice(goodEmojis))
        asked_name = user_location.author
        awaiting_answer = True
        try:
            response = await bot.wait_for("message", timeout=15.0, check=check)
        except TimeoutError:
            await message.channel.send("Never mind then" + ", " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
            awaiting_answer = False
            return
        if response.content.lower() not in positive_response_list and response.content.lower() not in \
                negative_response_list:
            await message.channel.send("Is that a yes or a no" + ", " + message.author.mention + "? " + random.choice(misunderstoodEmojis))
            asked_name = response.author
            awaiting_answer = True
            try:
                response = await bot.wait_for("message", timeout=10, check=check)
            except TimeoutError:
                await message.channel.send("Never mind then" + ", " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
                awaiting_answer = False
                return
        if response.content.lower() in positive_response_list:
            await message.channel.send("Okay, where" + ", " + message.author.mention + "? " + random.choice(goodEmojis))
            asked_name = response.author
            awaiting_answer = True
            try:
                response = await bot.wait_for("message", timeout=15.0, check=check)
            except TimeoutError:
                await message.channel.send("Never mind then" + ", " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
                awaiting_answer = False
                return
            lat_long_search = "https://maps.googleapis.com/maps/api/geocode/json?address=" + response.content.lower() \
                              + "&key=AIzaSyB0Qwc0X0pybqsVhss9eENMA5h1OcO4b9Y"
            latitude, longitude = str(requests.get(lat_long_search).json()['results'][0]['geometry']['location']
                                      ['lat']), str(requests.get(lat_long_search).json()['results'][0]['geometry']
                                                                                      ['location']['lng'])
            cinema_search = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=" + latitude + "," \
                            + longitude + "&radius=6000&keyword=cinema&key=" + key
            cinemas = requests.get(cinema_search).json()
            if cinemas['status'] != 'OK':
                await message.channel.send("I'm having a bit of trouble, please try again in a bit" + ", " + message.author.mention + ". " + random.choice(misunderstoodEmojis))
        else:
            return await message.channel.send("Okay, no problem" + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    cinemas = cinemas['results']
    await message.channel.send("Your nearest cinema is " + cinemas[0].get('name') + ": " + cinemas[0].get('vicinity') + ", " + message.author.mention + ". " + random.choice(goodEmojis))
    await message.channel.send("Do you want some more results" + ", " + message.author.mention + "? " + random.choice(goodEmojis))
    asked_name = message.author
    awaiting_answer = True
    try:
        response = await bot.wait_for("message", timeout=15.0, check=check)
    except TimeoutError:
        awaiting_answer = False
        return await message.channel.send("Guess not, have fun" + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    if response.content.lower() in positive_response_list:
        await message.channel.send("Here you go:")
        for cinema in cinemas[1:min(6, len(cinemas))]:
            await message.channel.send(cinema.get('name') + ": " + cinema.get('vicinity') + " " + message.author.mention)
            awaiting_answer = False
        return
    else:
        awaiting_answer = False
        return await message.channel.send("No worries, enjoy " + cinemas[0].get('name') + ", " + message.author.mention + "! " + random.choice(goodEmojis))


bot.run("")
