# -*- coding: utf-8 -*-
"""
Created on Thu Jul 13 21:55:58 2017

@author: XuGang
"""
import torch
from game.agent import Agent
from rl.mydqn import DQN
import numpy as np
from config import MODEL_SAVE_PATH
from visdom import Visdom
import time
viz = Visdom()
# rl
if __name__ == "__main__":

    step = 0
    agent = Agent()
    model = DQN()
    LOAD_MODEL=False
    if LOAD_MODEL:
        sd=torch.load(open(MODEL_SAVE_PATH+'1557042372.027585.pt','rb'))
        model.eval_net.load_state_dict(sd)
        model.target_net.load_state_dict(sd)
    winners = []
    win_rate = 0
    max_rate=0
    for episode in range(100000):
        # initial observation
        s = agent.reset()
        done = False
        while (not done):

            # RL choose action based on observation
            actions = agent.get_actions_space()
            print(actions)
            # action to one-hot
            actions_ont_hot = np.zeros(agent.dim_actions)
            for k in range(len(actions)):
                actions_ont_hot[actions[k]] = 1

            action, action_id = model.choose_action(s, actions_ont_hot, actions)

            # RL take action and get next observation and reward
            s_, r, done = agent.step(action_id=action_id)

            model.store_transition(s, action, r, s_)

            if (step > 200) and (step % 5 == 0):
                loss = model.learn()
                if step % 100 == 0:
                    print("episode: ", episode, ", loss: ", loss, ", win_rate: ", win_rate)
                    viz.line([loss], [episode], win='loss', opts=dict(title='loss'),update='append')
                    viz.line([win_rate], [episode], win='winrate', opts=dict(title='winrate'),update='append')

            # swap observation
            s = s_

            step += 1

        if r == 1:
            winners.append(1)
        else:
            winners.append(0)

        win_rate = np.mean(winners)

        # end of game
        if episode % 100 == 0:
            if win_rate>max_rate:
                max_rate=win_rate
                torch.save(model.eval_net.state_dict(), MODEL_SAVE_PATH +'max.pt')
        # print('game over')


"""
#test
#win_rate = 0.36890000000000001
if __name__=="__main__":
    agent = Agent(models=["rl","random","random"])
    winners = []
    win_rate = 0
    for episode in range(10000):
        s = agent.reset()
        done = False
        while(not done):
            actions = agent.get_actions_space() #如果actions为[]，step()
            s_, r, done = agent.step(action_id=0)
            s = s_
        if r == 1:
            winners.append(1)
        else:
            winners.append(0)
            
        win_rate = np.mean(winners)  
"""
