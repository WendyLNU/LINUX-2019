from pymongo import MongoClient
from settings import SETTINGS


class DbClinet(object):
    def __init__(self):
        s = SETTINGS["database"]
        self.client = MongoClient(s["host"], s["port"], password=s["password"])
        self.db = self.client[s["dbname"]]
        self.col = self.db[s["colname"]]

    def add(self, data):
        self.col.insert_one(data)

    def remove(self, aid):
        self.col.delete_many({"aid": aid})

    def remove_all(self):
        self.col.delete_many({})

    def get(self, aid):
        return self.col.find_one({"aid": aid})

    def exists(self, aid):
        return True if self.col.find_one({"aid": aid}) != None else False

    def count(self):
        return self.col.count_documents({})

if __name__ == "__main__":
    d = DbClinet()
    d.add({"aid": 1})
    print(d.exists(1))
    print(d.get(1))
    print(d.count())
    print(d.remove_all())
    print(d.count())
