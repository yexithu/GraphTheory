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


for x_start in range(10):
    print('Start to Parse Number ' + str(x_start) + 'Page\n')
    target_str = base_url + '?start=' + str(x_start * 25) + '&filter=&type='
    data_str = get_url_data(target_str)
    mat = target_reg.findall(data_str)
    for ahref in mat:
        ahref = str(ahref)
        ahref = ahref[9:ahref.__len__() - 2]
        print(ahref)
        movieIDList.append(ahref)
    time.sleep(5)

print(movieIDList.__len__())
f = open("movie_link.txt", 'w')
f.write(json.dumps(movieIDList))
f.close()







