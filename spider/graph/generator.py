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
        self.username_sets = []

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

    def generate_username_sets(self):
        for mov in self.movies:
            username_list = [val.username for val in mov.reviews]
            self.username_sets.append(set(username_list))
            # print(set(username_list))

    def generate_nodes_file(self):
        nodes_f = open(output_dir_root + output_nodes_name, 'w')
        for mov in self.movies:
            nodes_f.write(movie.Movie.movie_to_node(mov))

        nodes_f.close()

    def generate_edges_file(self):
        edges_f = open(output_dir_root + output_edges_name, 'w')
        list_num = self.username_sets.__len__()

        max_num = 0
        for i in range(list_num):
            print('Processing ' + str(i) + ' Edges')
            for j in range(i + 1, list_num):
                shared_num = list(self.username_sets[i].intersection(self.username_sets[j])).__len__()
                if shared_num > 0:
                    edges_f.write(str(self.movies[i].rank) + ' ' + str(self.movies[j].rank) + ' ' + str(shared_num) +
                                  '\n')
                if shared_num > max_num:
                    max_num = shared_num

        print('Max Number ' + str(max_num))


def test(gen):
    sample_a = 219
    sample_b = 137

    index_a = list(filter(lambda x: gen.movies[x].rank == sample_a, range(gen.movies.__len__())))[0]
    index_b = list(filter(lambda x: gen.movies[x].rank == sample_b, range(gen.movies.__len__())))[0]

    shared_num = 0
    for user in gen.username_sets[index_a]:
        if user in gen.username_sets[index_b]:
            shared_num += 1

    print("Test Shared Num " + str(shared_num))


def main():
    generator = Generator()
    generator.generate_nodes_file()
    generator.generate_username_sets()
    generator.generate_edges_file()
    # test(generator)


if __name__ == '__main__':
    main()
