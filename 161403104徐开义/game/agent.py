from game.myclass import Game
from game.rlutil import get_state, get_actions
from config import ACTIONS,ACTION_SIZE




############################################
#               LR接口类                   #
############################################
class Agent(object):
    """
    只可以在player 1进行训练,player 2/3可以random,规则或rl的val_net
    """

    def __init__(self, player=1, models=["rl", "random", "random"]):
        self.game = None
        self.player = player
        self.models = models
        self.actions_lookuptable =ACTIONS
        self.dim_actions = ACTION_SIZE + 2  # -2 buyao, -1 yaobuqi
        self.dim_states = 30 + 3

        self.actions = []

    def reset(self):
        self.game = Game(self.models)
        self.game.game_start()
        return get_state(self.game.playrecords, self.player)

    def get_actions_space(self):
        self.next_move_types, self.next_moves = self.game.get_next_moves()
        self.actions = get_actions(self.next_moves, self.actions_lookuptable, self.game)
        return self.actions

    # 传入actions的id
    def step(self, action_id=0):
        action = [self.next_move_types, self.next_moves, action_id, self.actions]
        winner, done = self.game.get_next_move(action=action)
        new_state = get_state(self.game.playrecords, self.player)

        if winner == 0:
            reward = 0
        elif winner == self.player:
            reward = 1
        else:
            reward = -1
        return new_state, reward, done


# rl
def main():
    agent = Agent()
    s = agent.reset()
    done = False
    while (not done):
        print('玩家1的剩余卡牌为：', agent.game.get_record().cards_left1)
        actions = agent.get_actions_space()  # 如果actions为[]，step()
        # GY的RL程序
        s_, r, done = agent.step(action_id=0)
        print('玩家1出完卡牌的剩余卡牌：', agent.game.get_record().cards_left1)
        print('玩家2剩余卡牌：', agent.game.get_record().cards_left2)
        print('玩家3剩余卡牌:', agent.game.get_record().cards_left3)
        print('出牌记录:', agent.game.get_record().records)
        print('奖励:', r)
        print('获胜玩家：', agent.game.get_record().winner)
        print("====================")


if __name__ == '__main__':
    main()
