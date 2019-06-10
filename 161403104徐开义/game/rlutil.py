# -*- coding: utf-8 -*-
"""
Created on Thu Jul 13 21:55:58 2017

@author: XuGang
"""
import numpy as np
import config


############################################
#                   LR相关                 #
############################################   
def get_state(playrecords, player):
    state = np.zeros(33).astype("int")
    # 后三位 三个人的手牌个数
    if player == 1:
        cards_left = playrecords.cards_left1
        state[30] = len(playrecords.cards_left1)
        state[31] = len(playrecords.cards_left2)
        state[32] = len(playrecords.cards_left3)
    elif player == 2:
        cards_left = playrecords.cards_left2
        state[30] = len(playrecords.cards_left2)
        state[31] = len(playrecords.cards_left3)
        state[32] = len(playrecords.cards_left1)
    else:
        cards_left = playrecords.cards_left3
        state[30] = len(playrecords.cards_left3)
        state[31] = len(playrecords.cards_left1)
        state[32] = len(playrecords.cards_left2)
    # 前15 自己的剩余卡牌个数
    for i in cards_left:
        state[i.rank - 1] += 1
    # 16-30位
    for cards in playrecords.records:
        if cards[1] in ["buyao", "yaobuqi"]:
            continue
        for card in cards[1]:
            state[card.rank - 1 + 15] += 1

    return state


def get_actions(next_moves, actions_lookuptable, game):
    """
    将[[Card,Card,...]]的action转换为一个值的action
    """
    actions = []
    for cards in next_moves:
        key = []
        for card in cards:
            key.append(int(card.name))
        key.sort()
        actions.append(actions_lookuptable[str(key)])

    # yaobuqi
    if len(actions) == 0:
        actions.append(config.ACTION_SIZE)#原为429
    # buyao
    elif game.last_move != "start":
        actions.append(config.ACTION_SIZE+1)#原为430

    return actions
