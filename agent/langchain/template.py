from langchain_openai import ChatOpenAI
from langchain_core.prompts import PromptTemplate
from langchain_core.prompts import ChatPromptTemplate

model = ChatOpenAI(
    model="ark-code-latest"
)
prompt_template = PromptTemplate(
    input_variables=["language"],
    template="translate the following to {language}"
)

chat_prompt_template = ChatPromptTemplate(
    [
        ("system", "you are a translator, translate the given message to {language}"),
        ("user", "{request}")
    ]
)
chain = chat_prompt_template | model
for chunk in chain.stream(
    {
        "language": "english",
        "request": "此曲只应天上有，人间能得几回闻"
    }
):
    print(chunk.content, end="", flush=True)