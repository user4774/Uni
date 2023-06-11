import asyncio
from asyncio import TimeoutError
import requests
from discord import *
from discord.ext import commands
from YoutubeAPI import *
from movies import *
from search_keyword_lists import *

"""
To improve readability, larger lists including keywords have been stored in a separate document which is
imported here.
Other team members' files are also imported here to gain access to their functions.

General references:
https://discordpy.readthedocs.io/en/latest/api.html
https://discordpy.readthedocs.io/en/async/faq.html#where-can-i-use-await    
"""

TOKEN = "secret"
bot = commands.Bot(command_prefix="", description="Movie bot for your entertainment!")


@bot.event
async def on_ready():
    print(f'{bot.user.name} has connected to Discord!')


awaiting_answer = False
asked_name = ""


@bot.event
async def on_message(message):
    global asked_name

    if awaiting_answer and asked_name == message.author:
        return
    if message.content.startswith("."):
        return
    if message.author == bot.user:
        return
    if "cinema" in message.content.lower() or "theatre" in message.content.lower():
        return await cinema_finder(message)
    elif message.content not in positive_response_list and message.content not in negative_response_list:
        await asyncio.create_task(find_is_film(message, bot))


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
    movie = omdb_get_request(message.content)
    if movie and 'Error' not in movie and check_input(message):
        movie_with_year = movie.get("Title") + ", " + movie.get("Year")
        await message.channel.send("Do you mean: " + movie_with_year + "?\n")
        asked_name = message.author
        awaiting_answer = True
        try:
            response = await bot.wait_for('message', timeout=15.0, check=lambda reply: reply.author != bot.user)
            if response.content.lower() in positive_response_list:
                await message.channel.send("What would you like to know about " + movie.get("Title") + "?\n")
                response = await bot.wait_for('message')
                await find_search_topic(response, movie.get("Title"), message)
                awaiting_answer = False
                return

            elif response.content.lower() in negative_response_list:
                movie_dict = get_imdb_list(message.content)
                for key in movie_dict:
                    if movie_dict.get(key) == movie_with_year:
                        continue

                    await message.channel.send("What about: " + movie_dict.get(key) + "?\n")
                    asked_name = message.author
                    awaiting_answer = True
                    try:
                        response = await bot.wait_for('message', timeout=15.0,
                                                      check=lambda reply: reply.author != bot.user)
                        if response.content.lower() in negative_response_list:
                            continue
                        elif response.content.lower() in positive_response_list:
                            movie = key
                            await message.channel.send("What would you like to know about "
                                                       + movie_dict.get(movie) + "?\n")
                            response = await bot.wait_for('message', timeout=15.0)
                            print(movie_dict.get(movie))
                            await find_search_topic(response, movie_dict.get(movie), message)
                            awaiting_answer = False
                            return
                        elif response.content.lower() in stop_keywords_list:
                            await message.channel.send("Never mind then")
                        else:
                            await message.channel.send("Never mind then")
                            awaiting_answer = False
                            return

                    except TimeoutError:
                        await message.channel.send("Never mind then")
                        awaiting_answer = False
                        return
            else:
                await message.channel.send("Never mind then")
                awaiting_answer = False
                return
        except TimeoutError:
            await message.channel.send("Never mind then")
            awaiting_answer = False
            return
    elif movie and 'Error' not in movie and not check_input(message):
        await message.channel.send("So you're asking something about a movie...")
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
                    if movie_dict.get(key) == movie_with_year:
                        continue

                    await message.channel.send("What about: " + movie_dict.get(key) + "?\n")
                    asked_name = message.author
                    awaiting_answer = True
                    try:
                        response = await bot.wait_for('message', timeout=15.0,
                                                      check=lambda reply: reply.author == message.author)
                        if response.content.lower() in negative_response_list:
                            continue
                        elif response.content.lower() in positive_response_list:
                            movie = movie_dict.get(key)
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
                input_without_title = " ".join(user_input_list[:preceding_keyword_index + 1]
                                               + user_input_list[(len(user_input_list) - loop_count):])
                if movie_name:
                    response = await find_search_topic(input_without_title, movie_name, message)
                else:
                    response = await find_search_topic(input_without_title, is_movie, message)
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
            await message.channel.send("Are you looking for " + matches_string)
            asked_name = message.author
            awaiting_answer = True
            try:
                user_input = await bot.wait_for("message", timeout=15.0,
                                                check=check)
                user_input = user_input.content
            except asyncio.TimeoutError:
                awaiting_answer = False
                break

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
            await message.channel.send("I don't understand what you're asking")
            asked_name = message.author
            awaiting_answer = True
            try:
                user_input = await bot.wait_for("message", timeout=15.0, check=check)
                await find_search_topic(user_input, title, message)

            except asyncio.TimeoutError:
                awaiting_answer = False
                break

    loop_iteration += 1
    if len(possible_matches) == 1:
        await search_imdb(search_type_list[possible_matches[0]], title, message)
    elif len(possible_matches) > 1:
        print("I don't think you're getting this...\n")

    return "Never mind then"


async def search_imdb(search_type_object, title, message):
    """
    This function takes the search topic as determined by the find_search_topic function, carries out the search,
    and returns the requested information to the user.
    """
    if title.isdigit():
        movie_name = get_omdb_movie_details("Title", title)
    else:
        movie_name = title
    if search_type_object.search_name_string == "trailer":
        release_year = get_omdb_movie_details("Year", title)
        try:
            trailer = outUrl(title + release_year)
            await message.channel.send("Here's the trailer for " + movie_name + ": " + str(trailer))
        except TypeError:
            await message.channel.send("Sorry, I couldn't find a trailer for {}".format(title))
        await asyncio.sleep(1)
        await follow_up(title, message)
    else:
        try:
            search_response = get_omdb_movie_details(search_type_object.search_code, title)
            if search_type_object.search_name_string == "review rating":
                await message.channel.send("The IMDb rating for " + movie_name + " is " + search_response[0]["Value"])
            elif search_type_object.search_name_string == "director":
                await message.channel.send(movie_name + " was directed by " + str(search_response))
            elif search_type_object.search_name_string == "writer":
                await message.channel.send(movie_name + " was written by " + str(search_response))
            elif search_type_object.search_name_string == "actors":
                await message.channel.send("Some of the actors that starred in " +
                                           movie_name + " were " + str(search_response))
            elif search_type_object.search_name_string == "awards":
                await message.channel.send(movie_name + " won the following awards; " + str(search_response))
            elif search_type_object.search_name_string == "poster":
                await message.channel.send("This is the poster for " + movie_name + + str(search_response))
            elif search_type_object.search_name_string == "synopsis":
                await message.channel.send("The " + search_type_object.search_name_string + " of " +
                                           movie_name + " is " + str(search_response))
            else:
                return
        except IndexError:
            await message.channel.send("blyat")
        await asyncio.sleep(1)
        await follow_up(title, message)


async def follow_up(title, message):
        await message.channel.send("Would you like to know anything else about {0}?".format(title))
        try:
            response = await bot.wait_for('message', timeout=15.0)
            if response.content.lower() in positive_response_list:
                await message.channel.send("What would you like to know?")
                response = await bot.wait_for('message', timeout=15.0)
                await find_search_topic(response, title, message)
            elif response.content.lower() in negative_response_list:
                await message.channel.send("That's all then")
            else:
                await find_search_topic(response, title, message)
        except TimeoutError:
            await message.channel.send("That's all then.")


async def cinema_finder(message):
    global awaiting_answer
    global asked_name
    key = 'AIzaSyB0Qwc0X0pybqsVhss9eENMA5h1OcO4b9Y'

    def check(m):
        return message.author == m.author and m.channel == message.channel

    await message.channel.send("Where are you looking for a cinema near to?")
    asked_name = message.author
    awaiting_answer = True
    try:
        user_location = await bot.wait_for("message", timeout=15.0, check=check)
    except TimeoutError:
        await message.channel.send("Never mind then")
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
                                   " else?")
        asked_name = user_location.author
        awaiting_answer = True
        try:
            response = await bot.wait_for("message", timeout=15.0, check=check)
        except TimeoutError:
            await message.channel.send("Never mind then")
            awaiting_answer = False
            return
        if response.content.lower() not in positive_response_list and response.content.lower() not in \
                negative_response_list:
            await message.channel.send("Is that a yes or a no?")
            asked_name = response.author
            awaiting_answer = True
            try:
                response = await bot.wait_for("message", timeout=10, check=check)
            except TimeoutError:
                await message.channel.send("Never mind then")
                awaiting_answer = False
                return
        if response.content.lower() in positive_response_list:
            await message.channel.send("Okay, where?")
            asked_name = response.author
            awaiting_answer = True
            try:
                response = await bot.wait_for("message", timeout=15.0, check=check)
            except TimeoutError:
                await message.channel.send("Never mind then")
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
                await message.channel.send("I'm having a bit of trouble, please try again in a bit")
        else:
            return await message.channel.send("Okay, no problem")
    cinemas = cinemas['results']
    await message.channel.send("Your nearest cinema is " + cinemas[0].get('name') + ": " + cinemas[0].get('vicinity'))
    await message.channel.send("Do you want some more results?")
    asked_name = message.author
    awaiting_answer = True
    try:
        response = await bot.wait_for("message", timeout=15.0, check=check)
    except TimeoutError:
        awaiting_answer = False
        return await message.channel.send("Guess not, have fun!")
    if response.content.lower() in positive_response_list:
        await message.channel.send("Here you go:")
        for cinema in cinemas[1:min(6, len(cinemas))]:
            await message.channel.send(cinema.get('name') + ": " + cinema.get('vicinity'))
            awaiting_answer = False
        return
    else:
        awaiting_answer = False
        return await message.channel.send("No worries, enjoy " + cinemas[0].get('name'))


bot.run(TOKEN)
