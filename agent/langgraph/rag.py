from langchain_openai import ChatOpenAI
from langchain_ollama import OllamaEmbeddings
from langchain_community.document_loaders import TextLoader
from langchain_text_splitters import RecursiveCharacterTextSplitter
from langchain_core.documents import Document
from langchain_core.vectorstores import InMemoryVectorStore
from langchain_community import retrievers
from langchain_classic.tools.retriever import create_retriever_tool
from langgraph.prebuilt import ToolNode, tools_condition
from langgraph.graph import StateGraph, START, END, MessagesState
from typing import TypedDict
from langchain_core.messages import HumanMessage, ToolMessage, AIMessage

model = ChatOpenAI(
    model="doubao-seed-2.0-pro"
)
embedding = OllamaEmbeddings(
    model="all-minilm"
)

# load texts
documents = ["example.md"]
spliter = RecursiveCharacterTextSplitter(
    chunk_size=100,
    chunk_overlap=20,
    separators=["\n\n", "\n", "。", "，", " ", ""]
)
store = InMemoryVectorStore(
    embedding=embedding
)
for document in documents:
    data = TextLoader(document).load()
    store.add_documents(spliter.split_documents(data))

retriever = store.as_retriever()
retriever_tool = create_retriever_tool(
    retriever=retriever,
    name="文档检索工具",
    description="当用户询问的内容不在你的明确指示储备中，通过查询文档查看用户问题是否是用户自定义内容"
)
tool_node = ToolNode([retriever_tool])
model_with_tool = model.bind_tools([retriever_tool], tool_choice="文档检索工具")

REWRITE_PROMPT = (  
    "查看输⼊并尝试推断潜在的语义意图/含义。\n"  
    "这是最初的问题："  
    "\n ------- \n"  
    "{question}"    "\n ------- \n"  
    "提出⼀个改进后的问题："  
)  
GENERATE_PROMPT = (  
    "你是负责回答问题的助⼿。 "    "使⽤以下检索到的上下⽂⽚段来回答问题。 "    "如果你不知道答案，就说你不知道。 "    "最多只⽤三句话，回答要简明扼要。\n"  
    "Question: {question} \n"  
    "Context: {context}"
)
CHECK_PROMPT = (  
    "你是⼀个评分员，评估检索到的⽂档与⽤⼾问题的相关性。 \n "    "以下是检索到的⽂档： \n\n {context} \n\n"  
    "以下是⽤⼾的问题： {question} \n"  
    "如果⽂档包含与⽤⼾问题相关的关键字或语义，则将其评为相关。 \n"  
    "给出⼀个⼆元分数“yes”或“no”，同时不能有任何多余文字，以表明该⽂档是否与问题相关。"  
) 

class CheckOutput(TypedDict):
    result: str

def answer_or_regenerate(state: MessagesState):
    response = model_with_tool.invoke(state["messages"])
    return {
        "messages": [response]
    }
def regenerate_question(state: MessagesState):
    question = state["messages"][0]
    prompt = REWRITE_PROMPT.format(question=question)
    response = model.invoke(prompt)
    return {
        "messages": [response.content]
    }
def answer_node(state: MessagesState):
    question = state["messages"][0]
    context = state["messages"][-1]
    prompt = GENERATE_PROMPT.format(question=question,context=context)
    response = model.invoke(prompt)
    return {
        "messages": [response.content]
    }

def check(state: MessagesState):
    question = state["messages"][0]
    context = state["messages"][-1]
    model_with_structured_output = model.with_structured_output(CheckOutput)
    response = model_with_structured_output.invoke(CHECK_PROMPT.format(question=question, context=context))
    if response["result"] == "yes":
        return "answer_node"
    else:
        return "regenerate_question"

rag_state = StateGraph(MessagesState)
rag_state.add_node(answer_or_regenerate)
rag_state.add_node(regenerate_question)
rag_state.add_node(answer_node)
rag_state.add_node("tool_node", tool_node)

rag_state.add_edge(START, "answer_or_regenerate")
rag_state.add_conditional_edges(
    "answer_or_regenerate",
    tools_condition, 
    {
        "tools": "tool_node",
        "__end__": "answer_node"
    }
)
rag_state.add_conditional_edges(
    "tool_node",
    check
)
rag_state.add_edge("answer_node", END)
rag_state.add_edge("regenerate_question", "answer_or_regenerate")
compiled_rag = rag_state.compile()
ret = compiled_rag.invoke({
    "messages": ["我自己定义的运算方式 6△7 等于多少"]
})
print(ret["messages"][-1].content)