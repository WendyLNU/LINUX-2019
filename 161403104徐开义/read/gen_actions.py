from myclass import Card, Cards, Moves
import pickle


def get_all_actions():
    cards = Cards().cards
    moves = Moves()
    moves.get_total_moves(cards)
    moves.get_next_moves('start', 'start')
    all_actions = moves.next_moves
    return all_actions


def get_action_dict(actions):
    action_dict = {}
    for index, cards in enumerate(actions):
        cards_name = []
        for card in cards:
            cards_name.append(int(card.name))
        cards_name.sort()  # 排序 与rl_util的action保持一致排序
        action_dict[str(cards_name)] = index+1

    return action_dict


if __name__ == '__main__':
    all_actions = get_all_actions()
    action_dict = get_action_dict(all_actions)
    print(len(action_dict))
    pickle.dump(action_dict, open('action_dict3.pkl', 'wb'))
