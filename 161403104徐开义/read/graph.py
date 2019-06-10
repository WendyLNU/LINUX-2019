from pycallgraph import PyCallGraph,Config
from pycallgraph.output import GraphvizOutput
from game import agent
Config.trac
with PyCallGraph(output=GraphvizOutput(output_file='graph/agent.png')):
    agent.main()

