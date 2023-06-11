"""This file was created to house scripts which were to act as placeholders whilst other team members were working on
the actual code."""
# from james_main import *
from titlecase import titlecase
from search_keyword_lists import *


def imdb_title_search(possible_title):
    """This is a dummy script used to simulate the searching of the title via the IMDb API in the absence of a the
    completed function whilst under development by a different team member"""
    film_titles = ["Die Hard", "The Godfather", "Legally Blonde", "The Breakfast Club", "Homeward Bound"]
    film_titles = [titles.lower() for titles in film_titles]
    if possible_title in film_titles:
        return True, titlecase(possible_title)
    else:
        return False, False


def imdb_search(title, search_code):
    """This is a dummy script used to confirm that the correct search is being carried out by the IMDb API as a result
    of the below function which identifies the desired search topic"""
    for search_type in search_type_list:
        if search_code == search_type.search_code:
            print("You are trying to find the " + search_type.search_name_string + " of " + title)
