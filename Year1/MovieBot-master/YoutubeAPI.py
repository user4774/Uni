##################################################################
#modify start: https://www.youtube.com/watch?v=b_jOJNUD350
from googleapiclient.discovery import build

api_key_youtube = 'secret'
youtube = build('youtube', 'v3', developerKey=api_key_youtube)

'''Returns the first video result with name and video id'''
def getIdAndTitle(search_query):
    #search request to api, with these conditions
    request = youtube.search().list(q = search_query, part = 'snippet', type = 'video', maxResults=1)
    response = request.execute()
    for movie in response['items']:
        #print(movie['snippet']['title'])
        return(movie['id']['videoId'])
    #modify end: https://www.youtube.com/watch?v=b_jOJNUD350
    #modified what items in list were returned

'''Uses video id to make a full url'''
def outUrl(movie_name):
    url = 'https://www.youtube.com/watch?v='+getIdAndTitle(movie_name)
    return url

'''Returns url of the best match of <movie name> ost'''
def getSoundtrack (user_input):
    if 'soundtrack' not in user_input:
        user_input = str(user_input) + 'ost'
    outUrl(user_input)

'''Returns url of the best match of <movie name> trailer'''
def getTrailer(user_input):
    if 'trailer' not in (user_input):
        user_input = str(user_input) + 'trailer'
    outUrl(user_input)

'''Should get the top comment from a trailer video'''
def getComments(search_query):
    if 'trailer' not in search_query:
        search_query = str(search_query) + 'trailer'
#from https://developers.google.com/youtube/v3/docs/commentThreads/list
    request = youtube.commentThreads().list(part = 'snippet', videoId = getIdAndTitle(search_query), maxResults =1, textFormat = 'plainText')
    response = request.execute()
    for comment in response['items']:
        return(comment["snippet"]["topLevelComment"]["snippet"]["textDisplay"])

##################################################################