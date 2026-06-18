from operator import add
from typing import TypedDict
from typing_extensions import Annotated
from langgraph.graph import StateGraph, START, END

class package_state(TypedDict):
    package_id: str
    origin: str
    destination: str
    status: str
    history: Annotated[list[str], add]
    total_distance: int
    priority: int

def receive_node(state: package_state):
    return {
        "history": ["已发货"],
        "status": "delivering",
    }
def transfer_node(state: package_state):
    if state["priority"] == 1:
        return {
            "history": ["加急派送"],
            "total_distance": 100
        }
    else:
        return {
            "history": ["普通派送"],
            "total_distance": 140
        }
def deliever_node(state: package_state):
    return {
        "status": "delivered",
        "history": ["已送达"]
    }

graph = StateGraph(package_state)
graph.add_node(receive_node)
graph.add_node(transfer_node)
graph.add_node(deliever_node)

graph.add_edge(START, "receive_node")
graph.add_edge("receive_node", "transfer_node")
graph.add_edge("transfer_node", "deliever_node")
graph.add_edge("deliever_node", END)
compiled_graph = graph.compile()

print(compiled_graph.invoke({
    "package_id": "id1",
    "origin": "linyi",
    "destination": "shanghai",
    "status": "",
    "history": [],
    "total_distance": 0,
    "priority": 1   
}))