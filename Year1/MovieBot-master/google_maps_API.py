"""
General references:
https://developers.google.com/places/web-service/search
https://developers.google.com/maps/documentation/javascript/geocoding
https://realpython.com/python-json/
"""
import asyncio
import json
import requests
from search_keyword_lists import *
from discord import *
from discord.ext import commands

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
    if message.author == bot.user:
        return
    else:
        await asyncio.create_task(cinema_finder(message))


async def cinema_finder(message):
    global awaiting_answer
    global asked_name
    key = 'secret'

    def check(m):
        return message.author == m.author and m.channel == message.channel

    await message.channel.send("Where are you looking for a cinema near to?")
    asked_name = message.author
    awaiting_answer = True
    try:
        user_location = await bot.wait_for("message", timeout=10, check=check)
    except asyncio.exceptions.TimeoutError:
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
            response = await bot.wait_for("message", timeout=10, check=check)
        except asyncio.exceptions.TimeoutError:
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
            except asyncio.exceptions.TimeoutError:
                await message.channel.send("Never mind then")
                awaiting_answer = False
                return
        if response.content.lower() in positive_response_list:
            await message.channel.send("Okay, where?")
            asked_name = response.author
            awaiting_answer = True
            try:
                response = await bot.wait_for("message", timeout=10, check=check)
            except asyncio.exceptions.TimeoutError:
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
        response = await bot.wait_for("message", timeout=10, check=check)
    except asyncio.exceptions.TimeoutError:
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


def jprint(obj):
    text = json.dumps(obj, sort_keys=True, indent=4)
    print(text)


bot.run(TOKEN)

