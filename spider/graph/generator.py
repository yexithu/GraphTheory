__author__ = 'Re'

import movie.Movie
import movie.Review

from movie.Movie import Movie
from movie.Review import Review

import os
import json

movie_file_dir = '../robot/movies/'
output_dir_root = './GraphInfo/'
output_nodes_name = 'Nodes.txt'
output_edges_name = 'Edges.txt'


class Generator(object):

    def __init__(self):
        self.movies = Generator.load_movies()

    @staticmethod
    def load_movies():
        movie_list = []
        movie_file_list = os.listdir(movie_file_dir)
        for movie_file in movie_file_list:
            movie_list.append(Generator.get_movie_from_json(movie_file_dir + movie_file))

        return movie_list

    @staticmethod
    def get_movie_from_json(movie_file):
        movie_f = open(movie_file, 'r')
        data_str = movie_f.read()
        mov = movie.Movie.dict_to_movie(eval(data_str))
        movie_f.close()
        # print(str(mov.movie_id) + ' ' + str(mov.reviews.__len__()) + '\n')
        return mov

    def generate_nodes_file(self):
        nodes_f = open(output_dir_root + output_nodes_name, 'w')
        for mov in self.movies:
            nodes_f.write(movie.Movie.movie_to_node(mov))

        nodes_f.close()

    # def generate_edges_file(self):
    #     movie_num = self.movies.__len__()
    #
    #     for i in range(movie_num):
    #         for j in range(i + 1, movie_num):
    #


def main():
    generator = Generator()
    generator.generate_nodes_file()

if __name__ == '__main__':
    main()
