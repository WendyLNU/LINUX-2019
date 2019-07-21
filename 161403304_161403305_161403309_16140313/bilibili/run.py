from concurrent.futures import ThreadPoolExecutor
from settings import SETTINGS
from spider import get_data
#from mongodb import DbClinet

s = SETTINGS["spider"]
#db = DbClinet()

def main():
    # begin = 1
    # end = 10001
    # while True:
    #     with ThreadPoolExecutor(s["maxthread"]) as executor:
    #         executor.map(run, range(begin, end))
    #     begin += 10000
    #     end += 10000
    for i in range(1,100):
        run(i)

def run(aid):
    # if db.exists(aid):
    #     return
    d = get_data(aid)
    print(d)
    #db.add(d)

if __name__ == "__main__":
    main()