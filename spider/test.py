import movie.Movie
import movie.Review
from movie.Review import Review
from movie.Movie import Movie

import re
import json
import time
from urllib import request
__author__ = 'Re'

base_url = 'http://movie.douban.com/top250'
start = 0

target_str = r'\<a\shref=\"http\:\/\/movie.douban.com\/subject\/\d*\/\"\>'
target_reg = re.compile(target_str)

movieIDList = []


def get_url_data(target_url):
    with request.urlopen(target_url) as resp:
        data = str(resp.read(), 'UTF-8', 'ignore')
        print('Status:', resp.status, resp.reason)
        data = data.encode('GBK', 'ignore').decode('GBK')
        # print(data)

        return data


# for x_start in range(10):
#     print('Start to Parse Number ' + str(x_start) + 'Page\n')
#     target_str = base_url + '?start=' + str(x_start * 25) + '&filter=&type='
#     data_str = get_url_data(target_str)
#     mat = target_reg.findall(data_str)
#     for ahref in mat:
#         ahref = str(ahref)
#         ahref = ahref[9:ahref.__len__() - 2]
#         print(ahref)
#         movieIDList.append(ahref)
#     time.sleep(5)
#
# print(movieIDList.__len__())
# f = open("movie_link.txt", 'w')
# f.write(json.dumps(movieIDList))
# f.close()


aMovie = Movie(1, '0', 'MovieTitle')
aMovie.add_review(Review('1', 'u1'))
aMovie.add_review(Review('2', 'u2'))
aMovie.add_review(Review('3', 'u3'))
print(movie.Movie.movie_to_dict(aMovie))

f = open('movie.json', 'w')

f.write(json.dumps(aMovie,indent=1, default=movie.Movie.movie_to_dict))
f.close()

f = open('movie.json', 'r')
data_str = f.read()
bmovie = movie.Movie.dict_to_movie(eval(data_str))
print(bmovie.reviews)
f.close()



