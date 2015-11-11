__author__ = 'Re'


class Review(object):

    def __init__(self, star, username):
        self.star = star
        self.username = username


def reviews_to_dict(rev):
        return {
            'star': rev.star,
            'username': rev.username
        }


def dict_to_reviews(review_dict):
    return Review(int(review_dict['star']), review_dict['username'])
