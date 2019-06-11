import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
from config import ACTION_SIZE

BATCH_SIZE = 128
LR = 0.01
GAMMA = 0.90
EPISILO = 0.9
MEMORY_CAPACITY = 500
Q_NETWORK_ITERATION = 300

NUM_ACTIONS = ACTION_SIZE + 2  # 原为431
NUM_STATES = 33

device = torch.device('cuda:0')


class Net(nn.Module):
    """docstring for Net"""

    def __init__(self):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(NUM_STATES, 512)
        self.fc1.weight.data.normal_(0, 0.3)
        self.fc2 = nn.Linear(512, 512)
        torch.nn.init.constant_(self.fc2.weight.data,0.1)
        self.out = nn.Linear(512, NUM_ACTIONS)
        self.out.weight.data.normal_(0, 0.1)

    def forward(self, x):
        x = self.fc1(x)
        x = F.relu(x)
        x = self.fc2(x)
        x = F.relu(x)
        action_prob = self.out(x)
        return action_prob


class DQN():
    """docstring for DQN"""

    def __init__(self):
        super(DQN, self).__init__()
        self.eval_net, self.target_net = Net().to(device), Net().to(device)

        self.learn_step_counter = 0
        self.memory_counter = 0
        self.memory = np.zeros((MEMORY_CAPACITY, NUM_STATES * 2 + 2))
        self.optimizer = torch.optim.Adam(self.eval_net.parameters(), lr=LR)
        self.loss_func = nn.MSELoss().to(device)

    def choose_action(self, observation, actions_ont_hot, actions):
        # to have batch dimension when feed into tf placeholder
        observation = observation[np.newaxis, :]

        if np.random.uniform() < EPISILO:
            # forward feed the observation and get q value for every actions
            actions_value = self.eval_net.forward(torch.FloatTensor(observation).to(device)).cpu().data.numpy().flatten()
            action = np.argmax(actions_value * actions_ont_hot)
            if action == 0.0:
                action_id = np.random.randint(0, len(actions))
                action = actions[action_id]
            else:
                action_id = actions.index(action)
        else:
            action_id = np.random.randint(0, len(actions))
            action = actions[action_id]

        return action, action_id

    def store_transition(self, state, action, reward, next_state):
        transition = np.hstack((state, [action, reward], next_state))
        index = self.memory_counter % MEMORY_CAPACITY
        # print(index)
        self.memory[index, :] = transition
        self.memory_counter += 1

    def learn(self):
        # update the parameters
        if self.learn_step_counter % Q_NETWORK_ITERATION == 0:
            self.target_net.load_state_dict(self.eval_net.state_dict())
        self.learn_step_counter += 1

        # sample batch from memory
        sample_index = np.random.choice(MEMORY_CAPACITY, BATCH_SIZE)
        batch_memory = self.memory[sample_index, :]
        batch_state = torch.FloatTensor(batch_memory[:, :NUM_STATES]).to(device)
        batch_action = torch.LongTensor(batch_memory[:, NUM_STATES:NUM_STATES + 1].astype(int)).to(device)
        batch_reward = torch.FloatTensor(batch_memory[:, NUM_STATES + 1:NUM_STATES + 2]).to(device)
        batch_next_state = torch.FloatTensor(batch_memory[:, -NUM_STATES:]).to(device)

        # q_eval
        q_eval = self.eval_net(batch_state).gather(1, batch_action)
        q_next = self.target_net(batch_next_state).detach()
        q_target = batch_reward + GAMMA * q_next.max(1)[0].view(BATCH_SIZE, 1)
        loss = self.loss_func(q_eval, q_target)

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()
        return loss.cpu().data.numpy()
