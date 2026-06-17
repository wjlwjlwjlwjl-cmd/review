from langchain_core.prompts import FewShotChatMessagePromptTemplate
from langchain_core.prompts import ChatPromptTemplate
from langchain_openai import ChatOpenAI
model = ChatOpenAI(
    model="ark-code-latest"
)

chat_template = ChatPromptTemplate(
    [
        ("user", "{expr}"),
        ("ai", "{ret}")
    ]
)
template_values = [
    {"expr": "1a1=?", "ret": "1a1=2"},
    {"expr": "3a2=?", "ret": "3a2=5"},
    {"expr": "2a6=?", "ret": "2a6=8"}
]

few_shot_template = FewShotChatMessagePromptTemplate(
    example_prompt=chat_template,
    examples=template_values
)
chat_prompt = ChatPromptTemplate(
    [
        ("system", "you a good calculator, give the user a right answer based on the examples below"),
        #few_shot_template,
        ("user", "{input}")
    ]
)
model.invoke(chat_prompt.invoke({"input", "3a7=?"})).pretty_print()