from game.gameutil import card_show, choose, game_init
import itertools
import operator
from functools import reduce


############################################
#                 游戏类                   #
############################################                   
class Game(object):

    def __init__(self, models):
        # 初始化一副扑克牌类
        self.cards = Cards()

        # play相关参数
        self.end = False
        self.last_move_type = self.last_move = "start"
        self.playround = 1
        self.i = 0
        self.yaobuqis = []

        # choose模型
        self.models = models

    # 发牌
    def game_start(self):

        # 初始化players
        self.players = []
        self.players.append(Player(1, self.models[0]))
        self.players.append(Player(2, self.models[1]))
        self.players.append(Player(3, self.models[2]))

        # 初始化扑克牌记录类
        self.playrecords = PlayRecords()

        # 发牌
        game_init(self.players, self.playrecords, self.cards)

    # 返回扑克牌记录类
    def get_record(self):
        web_show = WebShow(self.playrecords)
        # return jsonpickle.encode(web_show, unpicklable=False)
        return web_show

    # 返回下次出牌列表
    def get_next_moves(self):
        next_move_types, next_moves = self.players[self.i].get_moves(self.last_move_type, self.last_move,
                                                                     self.playrecords)
        return next_move_types, next_moves

    # 游戏进行
    def get_next_move(self, action):
        while (self.i <= 2):
            if self.i != 0:
                self.get_next_moves()
            self.last_move_type, self.last_move, self.end, self.yaobuqi = self.players[self.i].play(self.last_move_type,
                                                                                                    self.last_move,
                                                                                                    self.playrecords,
                                                                                                    action)
            if self.yaobuqi:
                self.yaobuqis.append(self.i)
            else:
                self.yaobuqis = []
            # 都要不起
            if len(self.yaobuqis) == 2:
                self.yaobuqis = []
                self.last_move_type = self.last_move = "start"
            if self.end:
                self.playrecords.winner = self.i + 1
                break
            self.i = self.i + 1
        # 一轮结束
        self.playround = self.playround + 1
        self.i = 0
        return self.playrecords.winner, self.end


############################################
#              扑克牌相关类                 #
############################################
class Cards(object):
    """
    一副扑克牌类,54张排,abcd四种花色,小王14-a,大王15-a
    """

    def __init__(self):
        # 初始化扑克牌类型
        self.cards_type = ['1-a-12', '1-b-12', '1-c-12', '1-d-12',
                           '2-a-13', '2-b-13', '2-c-13', '2-d-13',
                           '3-a-1', '3-b-1', '3-c-1', '3-d-1',
                           '4-a-2', '4-b-2', '4-c-2', '4-d-2',
                           '5-a-3', '5-b-3', '5-c-3', '5-d-3',
                           '6-a-4', '6-b-4', '6-c-4', '6-d-4',
                           '7-a-5', '7-b-5', '7-c-5', '7-d-5',
                           '8-a-6', '8-b-6', '8-c-6', '8-d-6',
                           '9-a-7', '9-b-7', '9-c-7', '9-d-7',
                           '10-a-8', '10-b-8', '10-c-8', '10-d-8',
                           '11-a-9', '11-b-9', '11-c-9', '11-d-9',
                           '12-a-10', '12-b-10', '12-c-10', '12-d-10',
                           '13-a-11', '13-b-11', '13-c-11', '13-d-11',
                           '14-a-14', '15-a-15']
        # 初始化扑克牌类
        self.cards = self.get_cards()

    # 初始化扑克牌类
    def get_cards(self):
        cards = []
        for card_type in self.cards_type:
            cards.append(Card(card_type))
        # 打乱顺序
        # np.random.shuffle(cards)
        return cards


class Card(object):
    """
    扑克牌类
    """

    def __init__(self, card_type):
        self.card_type = card_type
        # 名称
        self.name = self.card_type.split('-')[0]
        # 花色
        self.color = self.card_type.split('-')[1]
        # 大小
        self.rank = int(self.card_type.split('-')[2])

    # 判断大小
    def bigger_than(self, card_instance):
        if (self.rank > card_instance.rank):
            return True
        else:
            return False

    def __str__(self):
        return self.name


class PlayRecords(object):
    """
    扑克牌记录类
    """

    def __init__(self):
        # 当前手牌
        self.cards_left1 = []
        self.cards_left2 = []
        self.cards_left3 = []

        # 可能出牌选择
        self.next_moves1 = []
        self.next_moves2 = []
        self.next_moves3 = []

        # 出牌记录
        self.next_move1 = []
        self.next_move2 = []
        self.next_move3 = []

        # 出牌记录
        self.records = []

        # 胜利者
        # winner=0,1,2,3 0表示未结束,1,2,3表示winner
        self.winner = 0

        # 出牌者
        self.player = 1

    # 展示
    def show(self, info):
        print(info)
        card_show(self.cards_left1, "player 1", 1)
        card_show(self.cards_left2, "player 2", 1)
        card_show(self.cards_left3, "player 3", 1)
        card_show(self.records, "record", 3)


############################################
#              出牌相关类                   #
############################################
class Moves(object):
    """
    定义出牌类型
    """

    def __init__(self):
        # 单类型牌
        self.dan = []
        self.dui = []
        self.san = []
        self.bomb = []
        # 顺子
        self.dan_shun = []
        self.shuang_shun = []
        self.san_shun = []

        # 带牌
        self.san_dai_yi = []
        self.san_dai_er = []
        self.si_dai_yi = []
        self.si_dai_er = []
        # self.san_shun_dai = []

        # 所有的出牌类型 方便输出以及修改
        self.moves_types = ['dan', 'dui', 'san', 'san_dai_yi', 'san_dai_er', 'si_dai_yi', 'si_dai_er','bomb',
                            'dan_shun', 'shuang_shun', 'san_shun']
        self.all_type = [self.dan, self.dui, self.san, self.san_dai_yi, self.san_dai_er, self.si_dai_yi, self.si_dai_er,self.bomb,
                         self.dan_shun, self.shuang_shun, self.san_shun]
        # 按牌名将牌整理成字典形式{'1':[Card,Card]}
        self.card_dict = {}
        # 王牌信息
        self.king = []

        # 下次出牌
        self.next_moves = []
        # 下次出牌类型
        self.next_moves_type = []

    # 获取全部出牌列表
    def get_total_moves(self, cards_left):

        # 统计牌数量/顺序/王牌信息
        for i in cards_left:
            # 王牌信息
            if i.rank in [14, 15]:
                self.king.append(i)
            # 数量
            tmp = self.card_dict.get(i.name, [])
            if len(tmp) == 0:
                self.card_dict[i.name] = [i]
            else:
                self.card_dict[i.name].append(i)

        # 王炸
        if len(self.king) == 2:
            self.bomb.append(self.king)

        # 出单,出对,出三,炸弹(考虑拆开)
        for k, v in self.card_dict.items():
            if len(v) == 1:
                self.dan.append(v)
            elif len(v) == 2:
                self.dui.append(v)
                self.dan.append(v[:1])
            elif len(v) == 3:
                self.san.append(v)
                self.dui.append(v[:2])
                self.dan.append(v[:1])
            elif len(v) == 4:
                self.bomb.append(v)
                self.san.append(v[:3])
                self.dui.append(v[:2])
                self.dan.append(v[:1])

        # 三带一,三带二
        for san in self.san:
            self._append_dai(self.san_dai_yi, san, self.dan, 1)
            self._append_dai(self.san_dai_er, san, self.dui, 1)

        # 四带一，四带二
        for si in self.bomb:
            if si[0].name != ('14' or '15'):
                self._append_dai(self.si_dai_yi, si, self.dan, 2)
                self._append_dai(self.si_dai_er, si, self.dui, 2)

        # 添加单顺子
        self._append_shunzi(self.dan, self.dan_shun, 5)
        # 添加双顺子
        self._append_shunzi(self.dui, self.shuang_shun, 3)
        # 添加三顺子
        self._append_shunzi(self.san, self.san_shun, 2)

        # # 三顺带
        # for san_shun in self.san_shun:
        #     self._append_dai(self.san_shun_dai, san_shun, self.dan, int(len(san_shun) / 3))  # 三顺带一
        #     self._append_dai(self.san_shun_dai, san_shun, self.dui, int(len(san_shun) / 3))  # 三顺带二

    def _append_dai(self, to_append, shun, dai_list, dai_num):
        '''
        给三带一 三带二 三顺带添加带牌
        :param to_append:要添加的带牌list e.g. self.san_dai_yi self.san_shun_dai
        :param shun:用作合成的顺子 e.g. self.san_shun
        :param dai_list:用作合成的带牌 e.g. self.dan
        :param dai_num:带牌数目 e.g. 四带二就写 2
        :return:
        '''
        for dai in itertools.combinations(dai_list, dai_num):
            dai = reduce(operator.add, dai)
            can_append = True
            for t in dai:
                if t in shun:
                    can_append = False
                    break
            if can_append:
                result = shun + dai
                if len(result) <= 20:
                    to_append.append(result)

    def _append_shunzi(self, to_append, shun_list, min_len):
        '''

        :param to_append:单类型牌列表 e.g. self.dan
        :param shun_list:t要生成的顺子列表 e.g. self.san_shun
        :param min_len:顺子成立的最小长度 单顺写5 3顺写2
        :return:
        '''
        # 获取最长顺子
        result = []
        max_len = []
        for i in to_append:
            if i[0].name != ('13' or '14' or '15'):
                if len(max_len) == 0:
                    max_len.append(i)
                elif max_len[-1][0].rank == i[0].rank - 1:
                    max_len.append(i)
                else:
                    if len(max_len) >= min_len:
                        result.append(max_len)

                    max_len = [i]
        # 最后一轮
        if len(max_len) >= min_len:
            result.append(max_len)
        # 拆顺子
        shunzi_sub = []
        for i in result:
            len_total = len(i)
            n = len_total - min_len
            # 遍历所有可能顺子长度
            while (n > 0):
                len_sub = len_total - n
                j = 0
                while (len_sub + j <= len(i)):
                    # 遍历该长度所有组合
                    shunzi_sub.append(i[j:len_sub + j])
                    j = j + 1
                n = n - 1

        result.extend(shunzi_sub)
        # 保持格式一致 将[[[Card]]]转换为[[Card]]
        for t in result:
            temp = []
            for j in t:
                if len(j) <= 20:#检测是否超过20张
                    temp.extend(j)
            if len(temp) != 0:
                shun_list.append(temp)

    def _compare_other_move(self, last_move_type, last_move):
        '''
        单 对 三 三带一 三带二 四带一 四带二的比较方法
        :param last_move_type:
        :param last_move:
        :return:
        '''
        for move in eval(f'self.{last_move_type}'):
            # 比last大
            if move[0].bigger_than(last_move[0]):
                self.next_moves.append(move)
                self.next_moves_type.append(last_move_type)

    def _compare_shunzi_move(self, last_move_type, last_move):
        '''
        比较单顺，双顺，三顺，以及三顺带 的大小
        :param last_move_type:
        :param last_move:
        :return:
        '''
        for move in eval(f'self.{last_move_type}'):
            # 相同长度
            if len(move) == len(last_move):
                # 比last大
                if move[0].bigger_than(last_move[0]):
                    self.next_moves.append(move)
                    self.next_moves_type.append(last_move_type)

    # 获取下次出牌列表
    def get_next_moves(self, last_move_type, last_move):
        # 没有last,全加上,除了bomb最后加
        if last_move_type == "start":

            for index,move_type in enumerate(self.all_type):
                for move in move_type:
                    self.next_moves.append(move)
                    self.next_moves_type.append(self.moves_types[index])

        # 出顺子 及三顺带
        elif last_move_type in self.moves_types[-3:]:
            self._compare_shunzi_move(last_move_type, last_move)
        # 出 单 对 三 三带一 三带二 四带一 四带二
        elif last_move_type in self.moves_types[:-4]:
                self._compare_other_move(last_move_type, last_move)
        else:
                print('last move wrong')

        # 除了bomb,都可以出炸
        if last_move_type != "bomb":
            for move in self.bomb:
                self.next_moves.append(move)
                self.next_moves_type.append("bomb")

        return self.next_moves_type, self.next_moves

    # 展示
    def show(self, info):
        print(info)
        for index, type in enumerate(self.all_type):
            card_show(type, self.moves_types[index], 2)


############################################
#              玩家相关类                   #
############################################        
class Player(object):
    """
    player类
    """

    def __init__(self, player_id, model):
        '''

        :param player_id:玩家id
        :param model:模型
        '''
        self.player_id = player_id
        self.cards_left = []
        # 出牌模式
        self.model = model

    # 展示
    def show(self, info):
        self.total_moves.show(info)
        card_show(self.next_move, "next_move", 1)
        # card_show(self.cards_left, "card_left", 1)

    # 根据next_move同步cards_left
    def record_move(self, playrecords):
        # 记录出牌者
        playrecords.player = self.player_id
        # playrecords中records记录[id,next_move]
        if self.next_move_type in ["yaobuqi", "buyao"]:
            self.next_move = self.next_move_type
            playrecords.records.append([self.player_id, self.next_move_type])
        else:
            playrecords.records.append([self.player_id, self.next_move])
            for i in self.next_move:
                self.cards_left.remove(i)
                # 同步playrecords
        if self.player_id == 1:
            playrecords.cards_left1 = self.cards_left
            playrecords.next_moves1.append(self.next_moves)
            playrecords.next_move1.append(self.next_move)
        elif self.player_id == 2:
            playrecords.cards_left2 = self.cards_left
            playrecords.next_moves2.append(self.next_moves)
            playrecords.next_move2.append(self.next_move)
        elif self.player_id == 3:
            playrecords.cards_left3 = self.cards_left
            playrecords.next_moves3.append(self.next_moves)
            playrecords.next_move3.append(self.next_move)
        # 是否牌局结束
        end = False
        if len(self.cards_left) == 0:
            end = True
        return end

    # 选牌
    def get_moves(self, last_move_type, last_move, playrecords):
        # 所有出牌可选列表
        self.total_moves = Moves()
        # 获取全部出牌列表
        self.total_moves.get_total_moves(self.cards_left)
        # 获取下次出牌列表
        self.next_move_types, self.next_moves = self.total_moves.get_next_moves(last_move_type, last_move)
        # 返回下次出牌列表
        return self.next_move_types, self.next_moves

    # 出牌
    def play(self, last_move_type, last_move, playrecords, action):
        # 在next_moves中选择出牌方法
        self.next_move_type, self.next_move = choose(self.next_move_types, self.next_moves, last_move_type, self.model,
                                                     action)
        # 记录
        end = self.record_move(playrecords)
        # 展示
        # self.show("Player " + str(self.player_id))
        # 要不起&不要
        yaobuqi = False
        if self.next_move_type in ["yaobuqi", "buyao"]:
            yaobuqi = True
            self.next_move_type = last_move_type
            self.next_move = last_move

        return self.next_move_type, self.next_move, end, yaobuqi


############################################
#               网页展示类                 #
############################################
class WebShow(object):
    """
    网页展示类
    """

    def __init__(self, playrecords):

        # 胜利者
        self.winner = playrecords.winner

        # 剩余手牌
        self.cards_left1 = []
        for i in playrecords.cards_left1:
            self.cards_left1.append(i.name + i.color)
        self.cards_left2 = []
        for i in playrecords.cards_left2:
            self.cards_left2.append(i.name + i.color)
        self.cards_left3 = []
        for i in playrecords.cards_left3:
            self.cards_left3.append(i.name + i.color)

            # 可能出牌
        self.next_moves1 = []
        if len(playrecords.next_moves1) != 0:
            next_moves = playrecords.next_moves1[-1]
            for move in next_moves:
                cards = []
                for card in move:
                    cards.append(card.name + card.color)
                self.next_moves1.append(cards)
        self.next_moves2 = []
        if len(playrecords.next_moves2) != 0:
            next_moves = playrecords.next_moves2[-1]
            for move in next_moves:
                cards = []
                for card in move:
                    cards.append(card.name + card.color)
                self.next_moves2.append(cards)
        self.next_moves3 = []
        if len(playrecords.next_moves3) != 0:
            next_moves = playrecords.next_moves3[-1]
            for move in next_moves:
                cards = []
                for card in move:
                    cards.append(card.name + card.color)
                self.next_moves3.append(cards)

                # 出牌
        self.next_move1 = []
        if len(playrecords.next_move1) != 0:
            next_move = playrecords.next_move1[-1]
            if next_move in ["yaobuqi", "buyao"]:
                self.next_move1.append(next_move)
            else:
                for card in next_move:
                    self.next_move1.append(card.name + card.color)
        self.next_move2 = []
        if len(playrecords.next_move2) != 0:
            next_move = playrecords.next_move2[-1]
            if next_move in ["yaobuqi", "buyao"]:
                self.next_move2.append(next_move)
            else:
                for card in next_move:
                    self.next_move2.append(card.name + card.color)
        self.next_move3 = []
        if len(playrecords.next_move3) != 0:
            next_move = playrecords.next_move3[-1]
            if next_move in ["yaobuqi", "buyao"]:
                self.next_move3.append(next_move)
            else:
                for card in next_move:
                    self.next_move3.append(card.name + card.color)

                    # 记录
        self.records = []
        for i in playrecords.records:
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
            self.records.append(tmp)
