import json
import re
import robot.Robot
import time
import movie
import urllib
from movie.Movie import Movie
from movie.Review import Review


__author__ = 'Re'

movie_title_reg = re.compile(r'<title>\s*(\S*)')
movie_id_reg = re.compile(r'\d+')

review_next_page_reg = re.compile(r'href="\?start=(\d+)&amp;filter=&amp;limit=20')
review_allstar_reg = re.compile(r'allstar(\d{1})')
review_people_reg = re.compile(r'http://www.douban.com/people/(\S*)')


def get_movie_base_info(movie_url, rank):
    movie_id = movie_id_reg.search(movie_url)
    # print(movie_id.group())
    movie_data_str = robot.Robot.get_url_data(movie_url)
    # print(data_str)
    mat = movie_title_reg.findall(movie_data_str)
    movie_title = mat[0]
    # print(mat)

    single_movie = Movie(rank, movie_id.group(), movie_title)
    return single_movie


def get_movie_reviews_info(single_movie, reviews_url):
    review_data_str = robot.Robot.get_url_data(reviews_url)
    # print(review_data_str)
    next_id = review_next_page_reg.findall(review_data_str)
    # print(next_id[0])
    star_mat = review_allstar_reg.findall(review_data_str)
    # print(star_mat)
    people_mat = review_people_reg.findall(review_data_str)
    people_mat = [x[0:len(x) - 2] for x in people_mat]

    for index in range(int(people_mat.__len__() / 2)):
        # print(people_mat[2 * index])
        if index < star_mat.__len__():
            single_movie.add_review(Review(star_mat[index], people_mat[2*index]))
        else:
            single_movie.add_review(Review(0, people_mat[2*index]))

    if next_id.__len__() == 0:
        return 0
    else:
        return next_id[0]


movie_link_list = robot.Robot.load_movies_link_list()

start_pos = 10
end_pos = 11
tale_str = '&filter=&limit=20'

log_file = open('Log.txt', 'w')
log_file.write('Begin Log\n')
log_file.close()

for i in range(start_pos, end_pos):
    log_file = open('Log.txt', 'a')

    try:
        print('Begin to get ' + str(i) + ' BaseInfo')
        log_file.write('Begin to get ' + str(i) + ' BaseInfo\n')

        a_movie = get_movie_base_info(movie_link_list[i], i)
        print(str(i) + ' BaseInfo Success')
        log_file.write(str(i) + ' BaseInfo Success\n')

        time.sleep(1)

        print('Begin to get ' + str(i) + ' Advance Info')
        log_file.write('Begin to get ' + str(i) + ' Advance Info\n')

        next_page_id = get_movie_reviews_info(a_movie, movie_link_list[i] + 'reviews')

        while next_page_id != 0:
            print('Movie ' + str(i)+' Next Page Id ' + str(next_page_id))
            time.sleep(1)
            target_url = movie_link_list[i] + 'reviews?start=' + str(next_page_id) + tale_str
            next_page_id = get_movie_reviews_info(a_movie, target_url)

        print(str(i) + ' AdvanceInfo Success\n')
        log_file.write(str(i) + ' AdvanceInfo Success\n')
    except ValueError as valueEr:
        print('Failed to get ' + str(i) + 'Info')
        log_file.write('Failed to get ' + str(i) + 'Info\n')
    except IndexError as valueEr:
        print('Failed to get ' + str(i) + 'Info')
        log_file.write('Failed to get ' + str(i) + 'Info\n')
    # except urllib.error.HTTPError as httpError:
    #     print('Failed to get ' + str(i) + 'Info')
    #     log_file.write('Failed to get ' + str(i) + 'Info\n')
    except urllib.error.URLError as urlError:
        print('Failed to get ' + str(i) + 'Info')
        log_file.write('Failed to get ' + str(i) + 'Info\n')
    # except Exception as exce:
    #     print('Failed to get ' + str(i) + 'Info')
    #     log_file.write('Failed to get ' + str(i) + 'Info\n')

    log_file.close()
    f = open('movies/'+str(a_movie.movie_id) + '.json', 'w')
    f.write(json.dumps(a_movie, ensure_ascii=False, indent=2, default=movie.Movie.movie_to_dict))
    f.close()






