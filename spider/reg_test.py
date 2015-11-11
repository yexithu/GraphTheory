import re
import pickle
import json
__author__ = 'Re'


target_str = r'\<a\shref=\"http\:\/\/movie.douban.com\/subject\/\d*\/\"\>'
target_str_plus = r'http\:\/\/movie.douban.com\/subject\/\d*\/'
movie_title_reg = re.compile(r'<title>\s*(\S*)')
# movie_title_reg = re.compile(r'<title>')
movie_id_reg = re.compile(r'\d+')

review_next_page_reg = re.compile(r'href="\?start=(\d+)&amp;filter=&amp;limit=20')
review_allstar_reg = re.compile(r'allstar(\d{1})')
review_people_reg = re.compile(r'http://movie.douban.com/people/(\S*)')

f = open('movie_sample.txt', 'r',   encoding='GBK', errors='ignore')
data_str = f.read().encode('GBK', 'ignore').decode('GBK')
# data_str = f.read().encode('GBK', 'ignore').decode('GBK')
print(data_str)
f.close()

# print(data_str)
# next_id = review_next_page_reg.findall(data_str)
# print(next_id.__len__())
# star_mat = review_allstar_reg.findall(data_str)
# print(star_mat)
# people_mat = review_people_reg.findall(data_str)
# people_mat = [x[0:len(x) -2] for x in people_mat]
# print(people_mat)
# print(mat.groups()[0])

# mat = movie_id_reg.search('http://movie.douban.com/subject/1292052/')
#  print(mat.group())

mat = movie_title_reg.findall(data_str)
print(mat[0])
