import http.client
import json
import imdb
from random import randrange
from urllib import parse


IMDB_API_BASE = "sg.media-imdb.com"
OMDB_API_BASE = "omdbapi.com"
OMDB_API_KEY = "secret"

imdbpy = imdb.IMDb()


def get_omdb_movie_details(request, movie):
    """
    Returns specified movie information as a string.
    :param movie: Movie id or name
    :param request: Request type, eg: Title, synopsis, rating, etc.`
    :rtype: String
    """
    details = omdb_get_request(movie)
    if details is None:
        return
    return details.get(request)


def get_other_ratings(request, movie):
    selected_movie = omdb_get_request(movie)
    ratings = selected_movie.get("Ratings")
    for rating in ratings:
        if rating.get("Source") == request:
            return rating.get("Value")


def omdb_get_request(movie):
    """
    Make GET request to OMDb api.
    :param movie: Movie id or name
    :rtype: json, dictionary
    """
    identification = 't'
    if movie[:2] == "tt" and movie[2:].isdigit():
        identification = 'i'
    elif movie.isdigit():
        movie = "tt" + movie
        identification = 'i'
    movie = parse.quote(movie)
    conn = http.client.HTTPSConnection(OMDB_API_BASE)
    conn.request("GET", "/?apikey={0}&{1}={2}".format(OMDB_API_KEY, identification, movie))
    result = conn.getresponse()
    if result.getcode() != 200:
        return
    result = result.read().decode("utf-8")
    return json.loads(result)


def get_imdb_name(movie_title):
    """
    IMDb api based search for cases where the title might be heavily misspelled.
    :param movie_title: Movie title as a string
    :rtype: String
    """
    conn = http.client.HTTPSConnection(IMDB_API_BASE)
    conn.request("GET", "/suggests/{0}/{1}.json".format(movie_title[0], movie_title))
    result = conn.getresponse()
    if result.getcode() != 200:
        return
    result = result.read().decode("utf-8")
    result = format_jsonp(result)
    if 'd' not in result or result.get('d')[0].get('id')[:2] != 'tt':
        return
    return result


def format_jsonp(jsonp):
    """
    Converts jsonp to json.
    :param jsonp: IMDb GET result in jsonp format
    :rtype: json
    """
    jsonp = jsonp[jsonp.index('(') + 1: jsonp.rindex(')')]
    json_format = json.loads(jsonp)
    return json_format


def get_recommendations(movie_title):
    """
    Looks for movie recommendations based on a movie and returns a list of up to ten recommendations.
    :param movie_title: Movie title as a string
    :rtype: list
    """
    movie_list = []
    recommendations = get_imdbpy(movie_title, "recommendations")
    if recommendations is None or recommendations.get("recommendations") is None:
        return
    recommendations = recommendations.get("recommendations")

    if len(recommendations) > 0:
        if len(recommendations) > 10:
            for idx in range(10):
                movie_list.append(recommendations[idx].__str__())
        elif len(recommendations) <= 10:
            for idx in range(len(recommendations)):
                movie_list.append(recommendations[idx].__str__())
    return movie_list


def get_review(movie_title):
    """
    Finds reviews for a movie and returns a random one as a string.
    :param movie_title: Movie title as a string
    :rtype: String
    """
    reviews = get_imdbpy(movie_title, "reviews")
    if reviews is None or reviews.get("reviews") is None:
        return
    review_count = len(reviews.get("reviews"))
    if review_count != 0:
        return reviews.get("reviews")[randrange(review_count)].get("content")


def get_cast(movie_title):
    """
    Looks for movie cast and returns a list of up to ten cast members.
    :param movie_title: Movie title as a string
    :rtype: list
    """
    cast_list = []
    movie = get_imdbpy(movie_title)
    if movie is None or movie.get("cast") is None:
        return
    cast = movie.get("cast")
    if len(cast) > 0:
        if len(cast) > 10:
            for idx in range(10):
                cast_list.append(cast[idx].__str__())
        elif len(cast) <= 10:
            for idx in range(len(cast)):
                cast_list.append(cast[idx].__str__())
    return cast_list


def get_imdbpy(movie_id, request=None):
    """
    Finds requested movie from IMDb and returns a Movie object with requested parameters.
    :param movie_id: Movie id as a string
    :param request: request type as string, eg: "cast"
    :rtype: Movie
    """
    if len(movie_id) != 0:
        movie_id = movie_id[0].movieID
    else:
        return
    if request is None:
        return imdbpy.get_movie(movie_id)
    return imdbpy.get_movie(movie_id, request)


def get_imdb_list(movie_title):
    movie_dictionary = {}
    movies = imdbpy.search_movie(movie_title)
    for movie in movies:
        try:
            movie_dictionary.update({movie.movieID: [str(movie), str(movie["year"])]})
        except KeyError:
            continue
    return movie_dictionary


if __name__ == '__main__':
    print(print(get_imdb_list("avengers")))
