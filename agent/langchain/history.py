from langchain_openai import ChatOpenAI
from langchain_core.chat_history import BaseChatMessageHistory, InMemoryChatMessageHistory
from langchain_core.runnables import RunnableWithMessageHistory

cache = {}
def memory_cache(session_id: str)->BaseChatMessageHistory:
    if session_id not in cache:
        cache[session_id] = InMemoryChatMessageHistory()
    return cache[session_id]

model = ChatOpenAI(
    model="ark-code-latest"
)

model_with_memory = RunnableWithMessageHistory(model, memory_cache);
config = {
    "configurable":{
        "session_id": "session_id1"
    }
}
model_with_memory.invoke("我叫张三", config=config).pretty_print()
model_with_memory.invoke("我叫什么？", config=config).pretty_print()