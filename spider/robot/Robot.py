from movie.Movie import  Movie
from urllib import request
import json

__author__ = 'Re'


def get_url_data(target_url):
    req = request.Request(target_url)
    req.add_header('Host', 'movie.douban.com')
    req.add_header('Connection', 'keep-alive')
    req.add_header('Accept', 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8')
    req.add_header('User-Agent', 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 '
                                 '(KHTML, like Gecko) Chrome/46.0.2490.71 Safari/537.36')
    req.add_header('Cookie', 'bid="Kpv5dqRFFA0"; ll="108288"')

    with request.urlopen(req) as resp:
        data = str(resp.read(), 'UTF-8', 'ignore')
        print('Status:', resp.status, resp.reason)
        if resp.status != 200:
            raise ValueError('Get Url Data failed')
        data = data.encode('GBK', 'ignore').decode('GBK')
        # print(data)

    return data


def load_movies_link_list():
    link_file = open("movie_link.txt", 'r')
    movie_link_list = json.load(link_file)
    # print(movie_link_list)
    # for ahref in movie_link_list:
    #    print(ahref)
    return movie_link_list
