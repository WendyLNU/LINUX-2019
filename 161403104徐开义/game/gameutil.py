import numpy as np
from config import ACTION_SIZE
# 展示扑克函数
def card_show(cards, info, n):
    # 扑克牌记录类展示
    if n == 1:
        print(info)
        names = []
        for i in cards:
            names.append(i.name + i.color)
        print(names)
        # Moves展示
    elif n == 2:
        if len(cards) == 0:
            return 0
        print(info)
        moves = []
        for i in cards:
            names = []
            for j in i:
                names.append(j.name + j.color)
            moves.append(names)
        print(moves)
        # record展示
    elif n == 3:
        print(info)
        names = []
        for i in cards:
            tmp = []
            tmp.append(i[0])
            tmp_name = []
            # 处理要不起
            try:
                for j in i[1]:
                    tmp_name.append(j.name + j.color)
                tmp.append(tmp_name)
            except:
                tmp.append(i[1])
            names.append(tmp)
        print(names)


# 在Player的next_moves中选择出牌方法
def choose(next_move_types, next_moves, last_move_type, model, action):
    if model == "random":
        return choose_random(next_move_types, next_moves, last_move_type)
    elif model == 'human':
        return choose_human(next_move_types,next_moves,last_move_type)


    elif model == "rl":#action的格式   action = [self.next_move_types, self.next_moves, action_id, self.actions]
        if action[3][action[2]] == ACTION_SIZE:
            return "buyao", []
        elif action[3][action[2]] == ACTION_SIZE+1:
            return "yaobuqi", []
        else:
            return action[0][action[2]], action[1][action[2]]

        # random
def choose_human(next_move_types, next_moves, last_move_type):
    print('上次出牌为', last_move_type)
    action_index = int(input('请输入要出的牌的索引：(不要-1，要不起-2）'))
    next_move_type = ''
    next_move = []
    if action_index == -1:
        next_move_type = 'buyao'
        next_move = []
    elif action_index == -2:
        next_move_type = 'yaobuqi'
        next_move = []
    else:
        next_move_type = next_move_types[action_index]
        next_move = next_moves[action_index]

    return next_move_type, next_move


def choose_random(next_move_types, next_moves, last_move_type):
    # 要不起
    if len(next_moves) == 0:
        return "yaobuqi", []
    else:
        # start不能不要
        if last_move_type == "start":
            r_max = len(next_moves)
        else:
            r_max = len(next_moves) + 1
        r = np.random.randint(0, r_max)
        # 添加不要
        if r == len(next_moves):
            return "buyao", []

    return next_move_types[r], next_moves[r]


# 发牌
def game_init(players, playrecords, cards):
    # 洗牌
    np.random.shuffle(cards.cards)
    # 排序
    p1_cards = cards.cards[:18]
    p1_cards.sort(key=lambda x: x.rank)
    p2_cards = cards.cards[18:36]
    p2_cards.sort(key=lambda x: x.rank)
    p3_cards = cards.cards[36:]
    p3_cards.sort(key=lambda x: x.rank)
    players[0].cards_left = playrecords.cards_left1 = p1_cards
    players[1].cards_left = playrecords.cards_left2 = p2_cards
    players[2].cards_left = playrecords.cards_left3 = p3_cards
