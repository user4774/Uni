import discord # import the functionality of discord API
from discord.ext import commands # import command functionality from discord API extension
import random # this is to give me the method that randomly selects an element from a data structure like a list
import sqlite3 # import sqlite3 to create/integrate database and run SQL queries/inserts

# reference 1: https://discordpy.readthedocs.io/en/latest/ext/commands/api.html
# reference 2: https://discordpy.readthedocs.io/en/latest/ext/commands/commands.html
# reference 3: https://docs.python.org/3/library/sqlite3.html
# reference 4: https://www.sitepoint.com/getting-started-sqlite3-basic-commands/

bot = commands.Bot(command_prefix = "", description = "Movie bot for your entertainment!") # reference #instance of a bot created with specified command prefix (set to none)

@bot.event
async def on_ready(): # this event function is called when the bot is run and ready to operate
    db = sqlite3.connect("bot.db") # connects to DB
    c = db.cursor() # sets up cursor in order to control DB
    # Creates Watchlist table with primary key UserWatchlistID, a watchlist attribute that stores watchlists, and User_name attribute that stores username
    c.execute("CREATE TABLE IF NOT EXISTS Watchlist (UserWatchlistID INTEGER PRIMARY KEY AUTOINCREMENT, Watchlist TEXT, Username TEXT)")
    db.commit() # Saves changes to DB

    print("Bot is ready!")  # indicator on the console that the bot is up and running
    await bot.change_presence(activity=discord.Game(name=" with James' waifu"))  # customises bot 'playing game' status on discord


@bot.event
async def on_disconnect(): #event indicating bot has been disconnected from discord
    print("Bot has been disconnected.") #indicator of the bot disconnecting

@bot.event
async def on_message(message): # this function takes the user input as argument and will process it to determine a relevant response that is returned to the user
    message.content = message.content.lower() #inclusion of all indices of a user input, whether upper case or lower case, so case sensitivity is not a constraint # reference: https://stackoverflow.com/questions/50359600/can-a-discord-py-bot-not-be-case-sensitive​
    if message.author == bot.user:  # this ensures the bot doesn't respond to itself nor misinterprets its responses as user inputs by halting the function if the message processed was sent by itself
        return # reference: https://stackoverflow.com/questions/48320766/how-to-stop-discord-bot-respond-to-itself-all-other-bots-discord-bot-in-python​
    #lists of various responses & emojis relevant to specified user inputs to enhance bot personality
    hiResponses = ["Hello", "Hey", "Hi", "Yo"]
    hruResponses = ["I'm fine, thank you", "Not too bad", "Doing just fine", "I'm alright", "We gucci out here"]
    niceResponses = ["Good to know", "That's lovely", "Nice one", "Great", "Cheers", "Cool"]
    byeResponses = ["See ya", "See you", "See you in a bit", "Ttyl", "Don't forget your popcorn"]
    thanksResponses = ["My pleasure", "You're welcome", "No worries", "No need to thank me", "It's all gucci"]
    popcornResponses = ["You talkin' to me", "Who, me", "That's me", "What's up"]
    badResponses = ["Excuse me", "That's not very nice", "I dare you to say that again", "Take that back", "Not cool", "Sorry for that"]
    okResponses = ["Okay", "Alright then", "Glad you approve"]
    misunderstoodResponses = ["I didn't quite get that", "I didn't understand that", "That is beyond the grasp of my understanding", "That didn't make sense to me", "I'm sorry, I didn't catch that"]
    goodEmojis = ["😊", "☺", "😉", "😄", "😃", "🙂", "😝"]
    badEmojis = ["😡", "🤬", "😠", "😑", "👿"]
    misunderstoodEmojis = ["🙄", "😬", "🤔", "😓", "😒", "🤥", "🧐", "😳"]

    if "cinema" in message.content.lower() or "cinemas" in message.content.lower() or "theatre" in message.content.lower():
        return await cinema_finder(message) # if the words cinema, cinemas, or theatre are passed in as (part of) arguments into on_message() function, it will call the cinema finder function by passing in the user message as argument
    if "hi" or "hey" or "hello" or "how are you" or "you're" or "you are" or "hows" or "how's" or "good" or "fine" or "im" or "i'm" or "bad" or "bad" or "nice" or "cool" or "great" or "popcorn" or "yes" or "yeah" or "yup" or "ye" or "yeh" or "no" or "nah" or "nope" or "nope" or "bye" or "goodbye" or "goodnight" or "see ya" or "cya" or "bad" or "shit" or "shut up" or "fuck" or "ok" or "okay" or "alright" or "thanks" or "thank you" or "cheers" or "delete" or "deletewatchlist" or "create" or "createwatchlist" or "view" or "viewwatchlist" or "help" or "quote" or "quotes" in message.content:
        pass # if generic general chit chat is passed in as argument into on_message() function, the pass statement is placed there to allow the program to flow sequentially to process relevant responses to the user input
             # this is necessary as there are specific keywords that should only be used for movie searches

    if message.content.startswith("hi") or message.content.startswith("hey") or message.content.startswith("hello"): #condition pointing to messages that start with specified phrases
        await message.channel.send(random.choice(hiResponses) + ", " + message.author.mention + "!" + " How are you? " + random.choice(goodEmojis)) #bot will return a response by randomly choosing a relevant response (element from the relevant tuple) and mentioning the user on discord
    elif message.content.startswith("how are you") or message.content.startswith("you're") or message.content.startswith("you are") or message.content.startswith("hows") or message.content.startswith("how's"):
        await message.channel.send(random.choice(hruResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    elif message.content.startswith("i") or message.content.startswith("good") or message.content.startswith("fine") or message.content.startswith("im") or message.content.startswith("i'm") or message.content.startswith("bad") or message.content.startswith("nice") or message.content.startswith("cool") or message.content.startswith("great"):
        await message.channel.send(random.choice(niceResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    elif message.content.startswith("popcorn"):
        await message.channel.send(random.choice(popcornResponses) + ", " + message.author.mention + "? " + "🍿")
    elif message.content.startswith("yes") or message.content.startswith("yeah") or message.content.startswith("yup") or message.content.startswith("ye") or message.content.startswith("yeh"):
        await message.channel.send("Speak up then, I ain't got all the time in the world " + message.author.mention + " 🙄")
    elif message.content.startswith("no") or message.content.startswith("nah") or message.content.startswith("nope") or message.content.startswith("stop"):
        await message.channel.send("I'll just go back to sleep with my popcorn waifu then... " + message.author.mention + " 🤪👊")
    elif message.content.startswith("bye") or message.content.startswith("goodbye") or message.content.startswith("cya") or message.content.startswith("see ya") or message.content.startswith("goodnight"):
        await message.channel.send(random.choice(byeResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis) + "👋")
    elif message.content.startswith("fuck") or message.content.startswith("die") or message.content.startswith("bad") or message.content.startswith("shit") or message.content.startswith("shut up"):
        await message.channel.send(random.choice(badResponses) + ", " + message.author.mention + "! " + random.choice(badEmojis))
    elif message.content.startswith("ok") or message.content.startswith("okay") or message.content.startswith("alright"):
        await message.channel.send(random.choice(okResponses) + ", " + message.author.mention + "! " + random.choice(goodEmojis))
    elif message.content.startswith("thanks") or message.content.startswith("thank you") or message.content.startswith("cheers"):
        await message.channel.send(random.choice(thanksResponses) + " " + message.author.mention + "!" + " " + random.choice(goodEmojis))
    # if user message passed in as arg is the trigger word for a command, the program is allowed to pass, or flow sequentially to line 83 so the command is triggered without the intereference of the event function
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
    else: # if user input is unexpected, a feedback response from the bot will be provided, notifying the user it cannot comprehend what they have said
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
async def createwatchlist(cntxt, *, watchlist): # name of async function is primary command trigger, watchlist parameter will be assigned the argument inputted by user which contains the watchlist
    username = cntxt.author # the sender of the message is assigned to variable username
    realUsername = str(username) # the formatted username is converted into a string data type which is then assigned to a new variable
    watchlist = str(watchlist) # the watchlist passed in as argument is converted into a string data type and is assigned to variable watchlist
    db = sqlite3.connect("bot.db")
    c = db.cursor()
    c.execute("SELECT Username FROM Watchlist WHERE Username = '" + realUsername + "'") # SQL statement conducting a query to check if user has an existing watchlist by checking if a record with their username exists
    if c.fetchall() == []: # if result of query is an empty list, a new record is created for the user with the information they inputted for a movie watchlist, this is then saved and the user is notified by the creation of the watchlist
        db = sqlite3.connect("bot.db")
        c = db.cursor()
        c.execute("INSERT INTO Watchlist(Username, Watchlist) VALUES('" + realUsername + "', '" + watchlist + "')") #sql statement that stores the watchlist that corresponds to the user via string concatentation
        db.commit()
        await cntxt.send("You have successfully created a movie watchlist, " + cntxt.message.author.mention + "!" + " 🥳")
    else: # if the result of query isn't an empty list, this implies the existence of a watchlist for that specific user, so the bot notifies the user they can't create more than one watchlist
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
    c.execute("SELECT Watchlist FROM Watchlist WHERE Username = '" + realUsername + "' ") # SQL statement that conducts a query to search for a watchlist with the corresponding username of the user
    if c.fetchall() == []: # if result of query is an empty list, user is told they have no watchlist to delete
        await cntxt.send("Sorry, " + cntxt.message.author.mention + ", I can't delete a watchlist that doesn't exist!" + " " + random.choice(misunderstoodEmojis))
    else: # otherwise, the watchlist is deleted via SQL statement on line 150, and the user is notified of the deletion
        db = sqlite3.connect("bot.db")
        c = db.cursor()
        c.execute("DELETE FROM Watchlist WHERE Username = '" + realUsername + "' ")
        db.commit()
        await cntxt.send("Your movie watchlist has been deleted. Feel free to make a new one, " + cntxt.message.author.mention + "!" + " " + random.choice(emojis))



bot.run("") #runs the bot - the token in the string allows the code to connect to discord
