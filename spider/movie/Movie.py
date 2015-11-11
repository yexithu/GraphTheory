import movie.Review
import json
__author__ = 'Re'


class Movie(object):

    def __init__(self, rank, movie_id, title):
        self.rank = rank
        self.title = title
        self.movie_id = movie_id
        self.reviews = []

    def add_review(self, review):
        self.reviews.append(review)


def movie_to_dict(mov):
    return {
        'rank': mov.rank,
        'title': mov.title,
        'movie_id': mov.movie_id,
        'reviews': [movie.Review.reviews_to_dict(rev) for rev in mov.reviews]
    }


def dict_to_movie(movie_dict):
    print(movie_dict)
    a_movie = Movie(int(movie_dict['rank']), movie_dict['title'], movie_dict['movie_id'])
    a_movie.reviews = [movie.Review.dict_to_reviews(rev_dict) for rev_dict in movie_dict['reviews']]
    return a_movie
